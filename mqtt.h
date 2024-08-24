#ifndef MQTT_H
#define MQTT_H

#include <PubSubClient.h>

// Объявление MQTT клиента (Declaration of the MQTT client)
extern PubSubClient client; // MQTT клиент (MQTT client)
extern const char* mqtt_server; // Адрес MQTT сервера (MQTT server address)
extern const int mqtt_port; // Порт MQTT сервера (MQTT server port)
extern const char* mqtt_user; // Имя пользователя MQTT (MQTT username)
extern const char* mqtt_password; // Пароль MQTT (MQTT password)
extern const char* mqtt_topic_data; // Тема для данных погоды (Weather data topic)
extern const char* mqtt_topic_command; // Тема для команд (Command topic)
extern const char* mqtt_topic_debug; // Тема для отладки (Debug topic)

// Функция обратного вызова для MQTT сообщений (Callback function for MQTT messages)
void callback(char* topic, byte* payload, unsigned int length);
// Функция для подключения к MQTT серверу (Function to reconnect to the MQTT server)
void reconnect();

#endif

