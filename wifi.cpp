#include "wifi.h"

// Определяем SSID и пароль для подключения к Wi-Fi
const char* ssid = "SSID of your Wi-Fi";          // SSID вашей Wi-Fi сети (SSID of your Wi-Fi network)
const char* password = "Password of your Wi-Fi";   // Пароль вашей Wi-Fi сети (Password of your Wi-Fi network)

// Определяем статический IP-адрес и параметры сети
IPAddress staticIP(192, 168, 0, 11); // Ваш статический IP-адрес (Static IP address for the device)
IPAddress gateway(192, 168, 0, 1);   // Ваш шлюз (Gateway IP address, usually your router's IP)
IPAddress subnet(255, 255, 255, 0);  // Ваша маска подсети (Subnet mask)

// Функция для настройки Wi-Fi
void setup_wifi() {
  delay(10); // Небольшая задержка для стабилизации (Small delay for stabilization)

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid); // Вывод SSID для подключения (Output SSID for connection)

  WiFi.mode(WIFI_STA); // Устанавливаем режим Wi-Fi как Station (Set Wi-Fi mode to Station)
  WiFi.config(staticIP, gateway, subnet); // Устанавливаем статический IP-адрес (Set static IP address)
  WiFi.begin(ssid, password); // Начало подключения к Wi-Fi (Begin Wi-Fi connection)

  unsigned long startTime = millis(); // Запоминаем время начала попытки подключения (Record start time of connection attempt)
  while (WiFi.status() != WL_CONNECTED) { // Ожидание подключения к Wi-Fi (Waiting for Wi-Fi connection)
    if (millis() - startTime > 30000) { // Тайм-аут в 30 секунд (30-second timeout)
      Serial.println("Failed to connect to WiFi. Restarting...");
      ESP.restart(); // Перезагрузка, если подключение не удалось (Restart if connection fails)
    }
    delay(500); // Задержка перед следующей попыткой подключения (Delay before next connection attempt)
    Serial.print("."); // Индикация процесса подключения (Indicate connection process)
  }

  Serial.println("");
  Serial.println("WiFi connected"); // Сообщение об успешном подключении (Message about successful connection)
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP()); // Вывод локального IP-адреса устройства (Output local IP address of the device)
}

