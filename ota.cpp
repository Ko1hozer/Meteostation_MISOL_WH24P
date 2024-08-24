#include "ota.h"
#include "mqtt.h"

// Настройки для OTA (OTA settings)
const char* ota_hostname = "NAME METEO"; // Имя хоста для OTA (OTA hostname)
const char* ota_pwd = "YOUR PASS"; // Пароль для OTA (OTA password)

// Функция для настройки OTA (Function to setup OTA)
void setupOTA() {
  ArduinoOTA.setHostname(ota_hostname); // Установка имени хоста для OTA (Set OTA hostname)
  ArduinoOTA.setPassword(ota_pwd);      // Установка пароля для OTA (Set OTA password)

  // Обработчик начала обновления (Handler for the start of the update)
  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch"; // Тип обновления: скетч (Update type: sketch)
    } else { // U_SPIFFS
      type = "filesystem"; // Тип обновления: файловая система (Update type: filesystem)
    }
    client.publish(mqtt_topic_debug, ("Start updating " + type).c_str()); // Публикация сообщения о начале обновления (Publish message about the start of the update)
  });

  // Обработчик завершения обновления (Handler for the end of the update)
  ArduinoOTA.onEnd([]() {
    client.publish(mqtt_topic_debug, "Update finished"); // Публикация сообщения о завершении обновления (Publish message about the end of the update)
  });

  // Обработчик прогресса обновления (Handler for update progress)
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    char buffer[80];
    sprintf(buffer, "Progress: %u%%", (progress / (total / 100))); // Формирование строки с прогрессом (Format progress string)
    client.publish(mqtt_topic_debug, buffer); // Публикация сообщения о прогрессе обновления (Publish progress message)
  });

  // Обработчик ошибок OTA (Handler for OTA errors)
  ArduinoOTA.onError([](ota_error_t error) {
    String errorMsg;
    switch (error) {
      case OTA_AUTH_ERROR: errorMsg = "Auth Failed"; break; // Ошибка аутентификации (Authentication Error)
      case OTA_BEGIN_ERROR: errorMsg = "Begin Failed"; break; // Ошибка начала (Begin Error)
      case OTA_CONNECT_ERROR: errorMsg = "Connect Failed"; break; // Ошибка подключения (Connection Error)
      case OTA_RECEIVE_ERROR: errorMsg = "Receive Failed"; break; // Ошибка приема (Receive Error)
      case OTA_END_ERROR: errorMsg = "End Failed"; break; // Ошибка завершения (End Error)
    }
    client.publish(mqtt_topic_debug, ("Error: " + errorMsg).c_str()); // Публикация сообщения об ошибке (Publish error message)
  });

  ArduinoOTA.begin(); // Начало OTA (Begin OTA)
}

