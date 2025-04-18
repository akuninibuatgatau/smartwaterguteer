#include <WiFi.h>
#include <HTTPClient.h>
#include <ESP32Servo.h>

// WiFi
const char* ssid = "RK";
const char* password = "triomemberstres(TMS)";

// Ubidots
const char* token = "BBUS-dC72KMsMoMRCqbjAFvd4lQlLKOG6HS"; // Ganti sama token lu
const char* deviceLabel = "smart-waste-gutter-manager"; // sesuai API label di Ubidots

// Ultrasonic & Servo
const int trigPin = 5;
const int echoPin = 18;
int servoPin = 13;
Servo myServo;

void setup() {
  myServo.attach(servoPin);
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  myServo.write(0);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");
}

void loop() {
  float jarak = bacaJarak();
  Serial.print("Jarak: ");
  Serial.print(jarak);
  Serial.println(" cm");

  if (jarak > 20){
    myServo.write(0);
    Serial.println("Tutup");
    delay(1000);
  } else {
    myServo.write(70);
    Serial.println("Buka");
    delay(5000);
  }

  kirimKeUbidots(jarak);
  delay(2000); // jeda biar gak terlalu spam ke Ubidots
}

float bacaJarak() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long durasi = pulseIn(echoPin, HIGH, 30000);
  float jarak = (durasi * 0.0343) / 2;

  return jarak;
}

void kirimKeUbidots(float value){
  if(WiFi.status()== WL_CONNECTED){
    HTTPClient http;
    String url = "http://industrial.api.ubidots.com/api/v1.6/devices/";
    url += deviceLabel;
    String payload = "{\"jarak\":" + String(value) + "}";

    http.begin(url);
    http.addHeader("Content-Type", "application/json");
    http.addHeader("X-Auth-Token", token);

    int httpResponseCode = http.POST(payload);

    if (httpResponseCode > 0){
      Serial.print("Data terkirim ke Ubidots! Code: ");
      Serial.println(httpResponseCode);
    } else {
      Serial.print("Error kirim data, code: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  } else {
    Serial.println("WiFi belum konek bro!");
  }
}
