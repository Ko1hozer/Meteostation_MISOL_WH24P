#ifndef WIFI_H
#define WIFI_H

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Объявление глобальных объектов
extern WiFiClient espClient;  // Объект клиента Wi-Fi (Wi-Fi client object)
extern PubSubClient client;  // Объект MQTT клиента (MQTT client object)

// Функция для настройки Wi-Fi
void setup_wifi();  // Функция для подключения к Wi-Fi (Function to set up Wi-Fi connection)

#endif

