#include <ESP32Servo.h>

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
}

void loop() {
  float jarak = bacaJarak();
  Serial.print("Jarak: ");
  Serial.print(jarak);
  Serial.println(" cm");

  if (jarak > 20){
  int posDegrees1 = 0;
  myServo.write(posDegrees1);
  Serial.println("Tutup");
  delay(1000);
  }else{
  int posDegrees2 = 70;
  myServo.write(posDegrees2);
  Serial.println("Buka");
  delay(5000);
  }
}
float bacaJarak() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long durasi = pulseIn(echoPin, HIGH, 30000); // Timeout 30ms (30.000 µs)
  float jarak = (durasi * 0.0343) / 2;

  return jarak;
}
