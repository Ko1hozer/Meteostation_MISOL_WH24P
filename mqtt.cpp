#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "mqtt.h"

// Инициализация MQTT клиента (Initialize MQTT client)
WiFiClient espClient;
PubSubClient client(espClient);

// Настройки для подключения к MQTT серверу (Settings for MQTT server connection)
const char* mqtt_server = "IP YOUR MQTT";
const int mqtt_port = 1883;
const char* mqtt_user = "YOUR LOGIN";
const char* mqtt_password = "YOUR PASS";
const char* mqtt_topic_data = "weather_station/data";   // Тема для отправки данных (Data topic)
const char* mqtt_topic_command = "weather_station/command";   // Тема для отправки команд (Сommand topic)
const char* mqtt_topic_debug = "weather_station/debug"; // Тема для отладки (Debug topic)

// Функция обратного вызова для обработки входящих сообщений MQTT (Callback function to handle incoming MQTT messages)
void callback(char* topic, byte* payload, unsigned int length) {
  String message;
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  Serial.println(message);

  // Обработка команд (Handling commands)
  if (String(topic) == mqtt_topic_command) {
    if (message == "RESTART") {
      client.publish(mqtt_topic_debug, "Restarting ESP...");
      ESP.restart(); // Перезагрузка устройства (Restart the device)
    } else if (message == "STATUS") {
      String status = "Free Heap: " + String(ESP.getFreeHeap()) + " bytes";
      client.publish(mqtt_topic_debug, status.c_str()); // Публикация статуса устройства (Publish device status)
    }
  }
}

// Функция для подключения к MQTT серверу (Function to reconnect to the MQTT server)
void reconnect() {
  unsigned long startTime = millis();
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP8266Client", mqtt_user, mqtt_password)) {
      Serial.println("connected");
      client.publish(mqtt_topic_debug, "ESP connected to MQTT broker");
      // Отправляем сообщение о подключении к сети через MQTT (Send a connection message via MQTT)
      client.publish(mqtt_topic_debug, ("Connected to WiFi with IP: " + WiFi.localIP().toString()).c_str());

      client.subscribe(mqtt_topic_command); // Подписка на тему команд (Subscribe to command topic)
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000); // Задержка перед повторной попыткой (Delay before retrying)

      // Тайм-аут в 60 секунд для подключения (60-second timeout for connection)
      if (millis() - startTime > 60000) {
        Serial.println("Failed to connect to MQTT. Restarting...");
        ESP.restart(); // Перезагрузка, если подключение не удалось (Restart if connection fails)
      }
    }
  }
}

