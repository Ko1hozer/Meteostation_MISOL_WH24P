#include "weather.h"

// Функция для разбора направления ветра (Function to parse wind direction)
int parseWindDirection(String data) {
    int dirM = strtol(data.substring(4, 5).c_str(), NULL, 16); // DIR_M (4-й байт) (DIR_M (4th byte))
    int dirL = strtol(data.substring(5, 6).c_str(), NULL, 16); // DIR_L (5-й байт) (DIR_L (5th byte))
    int dirH = strtol(data.substring(6, 7).c_str(), NULL, 16); // DIR_H (6-й байт) (DIR_H (6th byte))

    int dir7_4 = dirM & 0x0F;      // Биты DIR_7-DIR_4 из DIR_M (младшие 4 бита) (Bits DIR_7-DIR_4 from DIR_M (lower 4 bits))
    int dir3_0 = dirL & 0x0F;      // Биты DIR_3-DIR_0 из DIR_L (младшие 4 бита) (Bits DIR_3-DIR_0 from DIR_L (lower 4 bits))
    int dir8 = (dirH >> 3) & 0x01; // Бит DIR_8 из DIR_H (3-й бит) (Bit DIR_8 from DIR_H (3rd bit))

    int windDir = (dir8 << 8) | (dir7_4 << 4) | dir3_0; // Комбинируем все 9 бит (Combine all 9 bits)

    if (windDir == 0x1FF) {
        return -1; // Недействительное значение (Invalid value)
    }

    return windDir;
}

// Функция для оценки по шкале Бофорта (Function to evaluate Beaufort scale)
String evaluateBeaufortScale(float windSpeed, float gustSpeed) {
    float maxSpeed = max(windSpeed, gustSpeed);  // Выбираем максимальную скорость для оценки (Choose the maximum speed for evaluation)

    if (maxSpeed < 0.5) return "0";    // "Штиль" ("Calm")
    if (maxSpeed < 1.6) return "1";    // "Тихий ветер" ("Light air")
    if (maxSpeed < 3.4) return "2";    // "Легкий ветер" ("Light breeze")
    if (maxSpeed < 5.5) return "3";    // "Умеренный ветер" ("Gentle breeze")
    if (maxSpeed < 8.0) return "4";    // "Свежий ветер" ("Moderate breeze")
    if (maxSpeed < 10.8) return "5";   // "Сильный ветер" ("Fresh breeze")
    if (maxSpeed < 13.9) return "6";   // "Очень сильный ветер" ("Strong breeze")
    if (maxSpeed < 17.2) return "7";   // "Штормовой ветер" ("Gale")
    if (maxSpeed < 20.7) return "8";   // "Сильный шторм" ("Strong gale")
    if (maxSpeed < 24.5) return "9";   // "Очень сильный шторм" ("Storm")
    if (maxSpeed < 28.4) return "10";  // "Ураганный ветер" ("Violent storm")
    if (maxSpeed < 32.6) return "11";  // "Сильный ураган" ("Hurricane")
    return "12";                       // "Очень сильный ураган" ("Hurricane force")
}

// Функция для оценки уровня освещенности (Function to evaluate light level)
String evaluateLight(float light) {
    if (light < 50) return "0";        //"Очень темно" ("Very dark")
    if (light < 200) return "1";       //"Темно" ("Dark")
    if (light < 500) return "2";       //"Слабый свет" ("Dim")
    if (light < 1000) return "3";      //"Яркий свет" ("Bright")
    if (light < 5000) return "4";      //"Очень яркий свет" ("Very bright")
    return "5";                        //"Экстремально яркий свет" ("Extremely bright")
}

// Функция для оценки UV-индекса (Function to evaluate UV index)
String evaluateUVI(int uv) {
    if (uv < 433) return "0";         // "Очень низкий" ("Very low")
    if (uv < 852) return "1";         // "Низкий" ("Low")
    if (uv < 1211) return "2";        // "Умеренный" ("Moderate")
    if (uv < 1571) return "3";        // "Средний" ("High")
    if (uv < 2018) return "4";        // "Высокий" ("Very high")
    if (uv < 2451) return "5";        // "Очень высокий" ("Extreme")
    if (uv < 2762) return "6";        // "Опасный" ("Dangerous")
    if (uv < 3101) return "7";        // "Очень опасный" ("Very dangerous")
    if (uv < 3513) return "8";        // "Экстремально опасный" ("Extremely dangerous")
    if (uv < 3919) return "9";        // "Крайне опасный" ("Extremely dangerous")
    if (uv < 4278) return "10";       // "Экстремально высокий" ("Extreme")
    if (uv < 4651) return "11";       // "Очень экстремально высокий" ("Very extreme")
    if (uv < 5029) return "12";       // "КОНЕЦ СВЕТА" ("THE END OF THE WORLD")
    return "13";                      // "АРМАГЕДОН" ("ARMAGEDDON")
}

// Функция для расчета индекса жары (Function to calculate heat index)
float calculateHeatIndex(float temperature, int humidity) {
    float hi;
    if (temperature >= 27.0) {
        hi = -8.78469475556 + 1.61139411 * temperature + 2.33854883889 * humidity 
            - 0.14611605 * temperature * humidity - 0.012308094 * temperature * temperature 
            - 0.0164248277778 * humidity * humidity + 0.002211732 * temperature * temperature * humidity 
            + 0.00072546 * temperature * humidity * humidity 
            - 0.000003582 * temperature * temperature * humidity * humidity;
    } else {
        hi = temperature;
    }
    return hi;
}

// Функция для разбора данных погоды (Function to parse weather data)
String parseWeatherData(String data) {
    String debugRawData = "Raw data: " + data; // Отладочное сообщение с сырыми данными (Debug message with raw data)
    Serial.println(debugRawData);

    // Проверка идентификатора данных (Check data identifier)
    if (data.substring(0, 2) != "24") {
        return "Invalid data packet"; // Некорректный пакет данных (Invalid data packet)
    }

    // Разбор температуры (Parse temperature)
    String tempHex = data.substring(7, 10); // "282"
    int tempRaw = strtol(tempHex.c_str(), NULL, 16);
    float temperature = (tempRaw - 400) / 10.0;

    // Разбор влажности (Parse humidity)
    String humidityHex = data.substring(10, 12); // "36"
    int humidity = strtol(humidityHex.c_str(), NULL, 16);

    // Разбор направления ветра (Parse wind direction)
    int windDirection = parseWindDirection(data);

    // Разбор скорости ветра (Parse wind speed)
    String windSpeedHex = data.substring(12, 14); // "00"
    int windSpeedRaw = strtol(windSpeedHex.c_str(), NULL, 16);
    float windSpeed = (windSpeedRaw / 8.0) * 1.12;

    // Разбор скорости порывов (Parse gust speed)
    String gustSpeedHex = data.substring(14, 16); // "02"
    int gustSpeedRaw = strtol(gustSpeedHex.c_str(), NULL, 16);
    float gustSpeed = gustSpeedRaw * 1.12;

    // Разбор осадков (Parse rain accumulation)
    String rainAccumHex = data.substring(16, 20); // "002d"
    int rainAccumRaw = strtol(rainAccumHex.c_str(), NULL, 16);
    float rainAccum = rainAccumRaw * 0.3;

    // Разбор UV-индекса (Parse UV index)
    String uvHex = data.substring(20, 24); // "0000"
    int uv = strtol(uvHex.c_str(), NULL, 16);

    // Разбор освещенности (Parse light level)
    String lightHex = data.substring(24, 30); // "005F42"
    int lightRaw = strtol(lightHex.c_str(), NULL, 16);
    float light = lightRaw / 10.0;

    // Разбор давления (Parse pressure)
    String pressureHex = data.substring(34, 40); // "018F6A"
    int pressureRaw = strtol(pressureHex.c_str(), NULL, 16);
    float pressureHpa = pressureRaw / 100.0;
    float pressureMmhg = pressureHpa * 0.75006;  // Перевод в мм рт. ст. (Convert to mmHg)

    float heatIndex = calculateHeatIndex(temperature, humidity); // Расчет индекса жары (Calculate heat index)
    String windForce = evaluateBeaufortScale(windSpeed, gustSpeed); // Оценка силы ветра (Evaluate wind force)
    String lightCondition = evaluateLight(light); // Оценка уровня освещенности (Evaluate light condition)
    String uviCondition = evaluateUVI(uv); // Оценка UV-индекса (Evaluate UV index)

    // Формирование строки JSON (Create JSON string)
    String jsonData = createJsonMessage(temperature, heatIndex, humidity, pressureMmhg, windDirection, 
                         windSpeed, gustSpeed, rainAccum, uv, 
                         light, windForce, lightCondition, uviCondition);

    return jsonData;
}

// Функция для создания JSON сообщения (Function to create JSON message)
String createJsonMessage(float temperature, float heatIndex, int humidity, float pressureMmhg, int windDirection, 
                         float windSpeed, float gustSpeed, float rainAccum, int uv, 
                         float light, String windForce, String lightCondition, String uviCondition) {
    DynamicJsonDocument doc(4024); // Увеличьте размер документа, если необходимо (Increase document size if needed)
    doc["temperature"] = temperature;
    doc["heat_index"] = heatIndex;
    doc["humidity"] = humidity;
    doc["pressure_mmhg"] = pressureMmhg;
    doc["wind_direction"] = windDirection;
    doc["wind_speed"] = windSpeed;
    doc["gust_speed"] = gustSpeed;
    doc["rain_accum"] = rainAccum;
    doc["uv_index"] = uv;
    doc["light"] = light;
    doc["wind_force"] = windForce;
    doc["light_condition"] = lightCondition;
    doc["uvi_condition"] = uviCondition;
    
    String jsonString;
    serializeJson(doc, jsonString); // Сериализация JSON документа (Serialize JSON document)
    return jsonString;
}

