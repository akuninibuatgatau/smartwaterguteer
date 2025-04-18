#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

const char* ssid = "RK";
const char* password = "triomemberstres(TMS)";

const char* botToken = "7283164583:AAFS84RA31ErZ9OptUFh-UB101IV3FKVYpk";  // Ganti token bot kamu
const int64_t chatId = 7512095666;   // Ganti chat ID kamu

WiFiClientSecure client;
UniversalTelegramBot bot(botToken, client);

const int trigPin = 5;
const int echoPin = 18;

void setup() {
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  client.setInsecure(); // Bypass SSL check

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi Connected!");
}

void loop() {
  float jarak = bacaJarak();
  Serial.print("Jarak: ");
  Serial.print(jarak);
  Serial.println(" cm");

  if (jarak < 7) {
    String pesan = "🚨 Wadah Sampah Telah Penuh!";
    bot.sendMessage(String(chatId), pesan, "");
    delay(10000);  // Biar nggak spam
  }
  delay(1000);
}

float bacaJarak() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);
  float distance = (duration * 0.0343) / 2;

  return distance;
}
