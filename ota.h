#ifndef OTA_H
#define OTA_H

#include <ArduinoOTA.h>

extern const char* ota_hostname;
extern const char* ota_pwd;

// Функция для настройки OTA (OTA settings)
void setupOTA();

#endif

