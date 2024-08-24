// MIT License

// Copyright (c) 2024 Artur Gor (https://t.me/gorozinskiy)

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//--------------------------------------------------------------------------------//
// Подключение Wemos D1 - MISOL WH24P:

// Черный:    GND   (GND)
// Красный:   (D )  (GPIO1 (RX))
// Желтый:    (D-)  (GPIO3 (TX))
// Зеленый:   VDD   (5V)

//--------------------------------------------------------------------------------//

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoOTA.h>
#include <ArduinoJson.h>

// Включаем файлы с функциями (Include function files)
#include "wifi.h"
#include "mqtt.h"
#include "ota.h"
#include "weather.h"

void setup() {
  Serial.begin(9600); // Настройка UART: 9600 бод (UART setup: 9600 baud)
  Serial.println("Starting...");

  setup_wifi(); // Настройка Wi-Fi (Wi-Fi setup)
  client.setServer(mqtt_server, mqtt_port); // Настройка MQTT сервера (MQTT server setup)
  client.setCallback(callback); // Установка функции обратного вызова для MQTT (Setting MQTT callback function)

  setupOTA(); // Настройка OTA (OTA setup)
}

void loop() {
    if (!client.connected()) {
        reconnect(); // Подключение к MQTT, если не подключено (Reconnect to MQTT if not connected)
    }
    client.loop(); // Обработка сообщений MQTT (Process MQTT messages)
    ArduinoOTA.handle(); // Обработка OTA обновлений (Handle OTA updates)

    if (Serial.available() >= 21) { // Проверка наличия достаточного количества данных в порту (Check if sufficient data is available in the port)
        byte data[21];
        Serial.readBytes(data, 21); // Чтение данных (Read data)

        if (data[0] == 0x24) { // Проверка, что первый байт — это маркер начала данных (Check if the first byte is the data start marker)
            String dataStr = "";
            for (int i = 0; i < 21; i++) {
                dataStr += String(data[i] < 16 ? "0" : "") + String(data[i], HEX);
            }

            Serial.println("Received data: " + dataStr); // Вывод полученных данных (Output received data)

            String jsonData = parseWeatherData(dataStr); // Парсинг данных погоды (Parse weather data)
            if (jsonData != "Invalid data packet" && jsonData != "Invalid wind direction data") {
                bool result = client.publish(mqtt_topic_data, jsonData.c_str()); // Отправка данных в MQTT (Publish data to MQTT)
                if (!result) {
                    Serial.println("Failed to publish data: " + jsonData); // Сообщение о неудачной публикации (Message about failed data publication)
                } else {
                    Serial.println("Data published successfully: " + jsonData); // Сообщение об успешной публикации (Message about successful data publication)
                }
                client.publish(mqtt_topic_debug, ("Parsed Data: " + jsonData).c_str()); // Публикация отладочных данных (Publish debug data)
            } else {
                Serial.println("Failed to parse data: " + jsonData); // Сообщение о неудачном парсинге данных (Message about failed data parsing)
                client.publish(mqtt_topic_debug, ("Failed to parse data: " + jsonData).c_str()); // Публикация отладочных данных (Publish debug data)
            }
        }
    }
    
    delay(1000); // Задержка перед следующей итерацией (Delay before the next iteration)
}

