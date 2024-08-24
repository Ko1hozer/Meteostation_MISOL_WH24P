<div align="center">
  <h1>☁️ MeteoStation Integration Project ☁️</h1>
  <p>Integrating MISOL WH24P UART Weather Station with ESP8266 and MQTT</p>
</div>

<h2>🚀 Features</h2>

<table>
  <tr>
    <th>Feature</th>
    <th>Supported</th>
  </tr>
  <tr>
    <td><em>Wi-Fi Connectivity</em> — Automatic connection to Wi-Fi with the option to set a static IP address. The device restarts automatically if it fails to connect.</td>
    <td>✅</td>
  </tr>
  <tr>
    <td><em>MISOL WH24P UART Integration</em> — Seamless support for connecting and gathering weather data from the MISOL WH24P UART weather station.</td>
    <td>✅</td>
  </tr>
  <tr>
    <td><em>MQTT Protocol</em> — Transmits collected weather data (temperature, humidity, pressure, wind speed, etc.) to an MQTT broker.</td>
    <td>✅</td>
  </tr>
  <tr>
    <td><em>Command Handling</em> — Allows control of the device through MQTT commands, including resetting and requesting status updates.</td>
    <td>✅</td>
  </tr>
  <tr>
    <td><em>Over-The-Air (OTA) Updates</em> — Firmware can be updated over Wi-Fi without physical access to the device.</td>
    <td>✅</td>
  </tr>
  <tr>
    <td><em>Detailed Logging</em> — Debug and device status information is logged and sent to MQTT for easy monitoring.</td>
    <td>✅</td>
  </tr>
</table>

<h2>📦 Installation</h2>

<h3>Clone the Repository</h3>

```sh
git clone https://github.com/yourusername/MeteoStation.git
cd MeteoStation
```
<h3>Install Required Libraries</h3> <ul> 
	<li><code>ESP8266WiFi</code></li> <li><code>PubSubClient</code></li> 
	<li><code>ArduinoOTA</code></li> <li><code>ArduinoJson</code></li> 
</ul> <p>Install the libraries using the Arduino IDE Library Manager.</p> 

<h3>Configure Settings</h3> <ul> 
	<li><strong>Wi-Fi Configuration:</strong> Set your SSID and password in <code>wifi.h</code>.</li> 
	<li><strong>MQTT Broker:</strong> Configure MQTT broker settings in <code>mqtt.h</code>.</li> 
	<li><strong>Weather Station:</strong> Configure settings for the MISOL WH24P UART in <code>sensors.h</code>.</li> </ul> 
 
 <h3>Upload the Firmware</h3> 
 <p>Upload the firmware to the ESP8266 microcontroller and ensure the device is connected to Wi-Fi and your MQTT broker.</p> 
 <h2>📊 Data Transmission Example</h2> 
 <p>The weather data is transmitted in JSON format:</p>
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

<h2>🛠️ Project Structure</h2> <ul> 
	<li><code>MeteoStation.ino</code> — Main project file.
	</li> <li><code>wifi.h / wifi.cpp</code> — Handles Wi-Fi connection and management.</li> 
	<li><code>mqtt.h / mqtt.cpp</code> — Manages MQTT connection and data transmission.</li> 
	<li><code>ota.h / ota.cpp</code> — Handles OTA firmware updates.</li> 
	<li><code>sensors.h / sensors.cpp</code> — Processes data from the MISOL WH24P UART weather station.</li> </ul> 

 ----------------------------------------------------------------------------------------------------------------
 <h2>📄 License</h2> 
 <p>This project is licensed under the MIT License. See the <a href="LICENSE">LICENSE</a> file for more details.</p> 
