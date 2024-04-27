#include <Wire.h>
#include <Servo.h>

#define TEMP_LED 4
#define MOISTURE_LED 5
#define SERVO_PIN 9

Servo myservo;

void setup() {
  Wire.begin(8);
  pinMode(TEMP_LED, OUTPUT);
  pinMode(MOISTURE_LED, OUTPUT);
  myservo.attach(SERVO_PIN);
  Serial.begin(9600);
  Wire.onReceive(receiveData);
}

void loop() {
  
}

void receiveData(int byteCount) {
  int temperature = Wire.read();
  int moisture = Wire.read();
//  Serial.print("Temperature: ");
  Serial.print(temperature);
//  Serial.print(", Moisture: ");
  Serial.print(",");
  Serial.print(moisture);

  if (temperature > 15 && temperature < 30) {
    digitalWrite(TEMP_LED, HIGH);
    Serial.print(",ON");
    if (moisture < 50) {
      digitalWrite(MOISTURE_LED, HIGH);
      Serial.print(",ON");
      myservo.write(90);
      Serial.println(",90");
    } else {
      digitalWrite(MOISTURE_LED, LOW);
      Serial.print(",OFF");
      myservo.write(0);
      Serial.println(",0");
    }
  } else if (moisture < 50) {
    digitalWrite(MOISTURE_LED, HIGH);
    Serial.print(",OFF");
    Serial.print(",ON");
    myservo.write(0);
    Serial.println(",0");
  } else {
    digitalWrite(TEMP_LED, LOW);
    digitalWrite(MOISTURE_LED, LOW);
    Serial.print(",OFF");
    Serial.print(",OFF");
    myservo.write(0);
    Serial.println(",0");
  }
}
