#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define TEMP_PIN A0
#define MOISTURE_PIN A1

const int buttonPin = 7; 
int buttonState = 0; 

const int DRY_SOIL_VALUE = 1000; // replace with your own calibration values
const int WET_SOIL_VALUE = 400;

int soilMoistureValue = 0;

LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  lcd.init();
  lcd.setBacklight(HIGH);
  Serial.begin(9600);
  Wire.begin();
}

void loop() {
  lcd.clear();
  buttonState = digitalRead(buttonPin);
  if (buttonState == LOW){
    Serial.print("ON");                     
    lcd.setCursor(0,0);
  	lcd.print("Manual          ");
    
    lcd.setCursor(0,1);
  	lcd.print("Watering...     ");
    
    int temperature = 20;
    int soilMoisturePercentage = 0;
    
    Wire.beginTransmission(8);
    Wire.write((int) temperature);
  	Wire.write((int) soilMoisturePercentage);
  	Wire.endTransmission();
    
    delay(4000);
    lcd.clear();
  }
  
  int tempValue = analogRead(TEMP_PIN);
  int temperature = (tempValue / 1024.0) * 5.0 * 100.0 - 449; // convert to temperature in Celsius
  
  
  soilMoistureValue = analogRead(MOISTURE_PIN);
  
  if (soilMoistureValue > DRY_SOIL_VALUE) {
    soilMoistureValue = DRY_SOIL_VALUE;
  } else if (soilMoistureValue < WET_SOIL_VALUE) {
    soilMoistureValue = WET_SOIL_VALUE;
  }
  
  int soilMoisturePercentage = 100 - map(soilMoistureValue, WET_SOIL_VALUE, DRY_SOIL_VALUE, 0, 100);
  
  lcd.setCursor(0,0);
  lcd.print(" Temp:");
  
  lcd.setCursor(6,0);
  lcd.print(temperature);
  
  lcd.setCursor(9,0);
  lcd.print("C");
  
  lcd.setCursor(0,1);
  lcd.print("Moist:");
   
  lcd.setCursor(6,1);
  lcd.print(soilMoisturePercentage);
  
  lcd.setCursor(9,1);
  lcd.print("%");
	
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print("   Moisture: ");
  Serial.println(soilMoisturePercentage);

  Wire.beginTransmission(8);
  Wire.write((int) temperature);
  Wire.write((int) soilMoisturePercentage);
  Wire.endTransmission();
  
  if (temperature > 15 && temperature < 30) {
    if (soilMoisturePercentage < 50) {
	    lcd.setCursor(11,0);
  	  lcd.print("Water");

      lcd.setCursor(11,1);
  	  lcd.print("On...");
    }
  }
  else {
      lcd.setCursor(11,0);
  	  lcd.print("Water");

      lcd.setCursor(11,1);
  	  lcd.print("Off..");
     
  }

  delay(300);
}
