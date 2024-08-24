<div align="center">
<h2><a href="https://github.com/Ko1hozer/Meteostation_MISOL_WH24P/blob/main/README_EN.md">README IN ENGLISH</a></h2>
 
  <h1>☁️ Интеграция MeteoStation MISOL WH24P RS485 ☁️</h1>
  <p>Интеграция метеостанции MISOL WH24P UART с ESP8266 и MQTT</p>
</div>

<h2>🚀 Особенности</h2>

<table>
  <tr>
    <th>Функция</th>
    <th></th>
  </tr>
  <tr>
    <td><em>Подключение к Wi-Fi</em> — Автоматическое подключение к Wi-Fi с возможностью установки статического IP-адреса. Устройство перезагружается автоматически, если не удается подключиться.</td>
    <p><td>✅</td></p>
  </tr>
  <tr>
    <td><em>Интеграция MISOL WH24P UART</em> — Бесшовная поддержка подключения и сбора данных о погоде с метеостанции MISOL WH24P UART.</td>
     <p><td>✅</td></p>
  </tr>
  <tr>
    <td><em>Протокол MQTT</em> — Передача собранных данных о погоде (температура, влажность, давление, скорость ветра и т.д.) на MQTT брокер.</td>
     <p><td>✅</td></p>
  </tr>
  <tr>
    <td><em>Обработка команд</em> — Управление устройством через команды MQTT, включая сброс и запрос обновлений статуса.</td>
     <p><td>✅</td></p>
  </tr>
  <tr>
    <td><em>Обновления по воздуху (OTA)</em> — Прошивка может быть обновлена через Wi-Fi без физического доступа к устройству.</td>
     <p><td>✅</td></p>
  </tr>
  <tr>
    <td><em>Логирование</em> — Информация для отладки и статус устройства записывается в журнал и отправляется на MQTT для легкого мониторинга.</td>
     <p><td>✅</td></p>
  </tr>
</table>

<h2>📦 Установка</h2>

<h3>Клонирование репозитория</h3>

```sh
git clone https://github.com/yourusername/MeteoStation.git
cd MeteoStation
```

<h3>Установка необходимых библиотек</h3> <ul> 
<li><code>ESP8266WiFi</code></li> 
<li><code>PubSubClient</code></li> 
<li><code>ArduinoOTA</code></li> 
<li><code>ArduinoJson</code></li> 
</ul> <p>Установите библиотеки с помощью менеджера библиотек в Arduino IDE.</p> 

<h3>Настройка параметров</h3> <ul> 
<li><strong>Настройка Wi-Fi:</strong> Установите ваш SSID и пароль в <code>wifi.h</code>.</li> 
<li><strong>MQTT брокер:</strong> Настройте параметры MQTT брокера в <code>mqtt.h</code>.</li> 
<li><strong>Метеостанция:</strong> Настройте параметры для MISOL WH24P UART в <code>sensors.h</code>.</li>

 </ul> <h3>Загрузка прошивки</h3> 
 <p>Загрузите прошивку в микроконтроллер ESP8266 и убедитесь, что устройство подключено к Wi-Fi и вашему MQTT брокеру.</p>
 
 <h2>📊 Пример передачи данных</h2> 
 <p>Данные о погоде передаются в формате JSON:</p>
 
 ```sh
 {
  "Temp": 23.5,
  "Hum": 65,
  "Press": 755.5,
  "WindDir": 180,
  "WindSpeed": 3.4,
  "RainAccum": 0.0,
  "UVIndex": 2,
  "Light": 850.0
}
```

<h2>🛠️ Структура проекта</h2> <ul> 
<li><code>MeteoStation.ino</code> — Основной файл проекта.</li> 
<li><code>wifi.h / wifi.cpp</code> — Обрабатывает подключение и управление Wi-Fi.</li> 
<li><code>mqtt.h / mqtt.cpp</code> — Управляет подключением MQTT и передачей данных.</li>
<li><code>ota.h / ota.cpp</code> — Обрабатывает обновления прошивки по воздуху (OTA).</li> 
<li><code>sensors.h / sensors.cpp</code> — Обрабатывает данные с метеостанции MISOL WH24P UART.</li>

--------------------------------------------------------------------------------------------------------------------
 </ul> <h2>📄 Лицензия</h2> 
 <p>Этот проект лицензирован под MIT лицензией. Подробнее смотрите в файле <a href="LICENSE">LICENSE</a>.</p> 
