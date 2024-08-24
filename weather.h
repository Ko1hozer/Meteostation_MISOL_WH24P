#ifndef WEATHER_H
#define WEATHER_H

#include <ArduinoJson.h>

String parseWeatherData(String data);
String createJsonMessage(float temperature, float heatIndex, int humidity, float pressureMmhg, int windDirection,
                         float windSpeed, float gustSpeed, float rainAccum, int uv,
                         float light, String windForce, String lightCondition, String uviCondition);

#endif

