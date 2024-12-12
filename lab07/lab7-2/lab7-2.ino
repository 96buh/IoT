#include "Wire.h"
#include "I2Cdev.h"
#include "BMP085.h"

BMP085 barometer;
float temperature;
float pressure;
float seaLevelPressure = 101325;
float altitude;
int32_t lastMicros;
#define buttonPin 8
#define floor1LED 10
#define floor2LED 11
#define floor3LED 12

int buttonState = 0;
bool blinkState = false;


float floor1 = 0;
float floor2 = 0;
int counter = 0;
float floorCount = 0;

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(38400);

  Serial.println("Initializing I2C devices...");
  barometer.initialize();

  Serial.println("Testing device connections...");
  Serial.println(barometer.testConnection() ? "BMP085 connection successful" : "BMP085 connection failed");

  pinMode(floor1LED, OUTPUT);
  pinMode(floor2LED, OUTPUT);
  pinMode(floor3LED, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  barometer.setControl(BMP085_MODE_TEMPERATURE);

  lastMicros = micros();
  while(micros() - lastMicros < barometer.getMeasureDelayMicroseconds());
  temperature = barometer.getTemperatureC();

  barometer.setControl(BMP085_MODE_PRESSURE_3);

  while (micros() - lastMicros < barometer.getMeasureDelayMicroseconds());
  pressure = barometer.getPressure();
  altitude = barometer.getAltitude(pressure, seaLevelPressure);

    // Serial.print("T/P/A\t");
    // Serial.print(temperature); Serial.print("\t");
    // Serial.print(pressure); Serial.print("\t");
    // Serial.print(altitude); Serial.println("");
  buttonState = digitalRead(buttonPin);
  if (buttonState == LOW && counter < 3) {
    counter += 1;
    if (counter == 1) {
      altitude = barometer.getAltitude(pressure, seaLevelPressure);
      floor1 = altitude;
      digitalWrite(floor1LED, HIGH);
    }
    else if (counter == 2) {
      altitude = barometer.getAltitude(pressure, seaLevelPressure);
      floor2 = altitude;
      digitalWrite(floor2LED, HIGH);
    }
    else if (counter == 3) {
      altitude = barometer.getAltitude(pressure, seaLevelPressure);
      float floorDiff = abs(floor1 - floor2);
      digitalWrite(floor3LED, HIGH);
      Serial.print("高度差: ");
      Serial.println(floorDiff);
      Serial.print("樓層: ");
      Serial.println((altitude - floor1) / floorDiff + 1);

      delay(500);
    }
  } 
  // float floorDiff = abs(floor1 - floor2);
  // Serial.println(counter);
  
  
  

  if (counter >= 3) {
    counter = 0;
    floor1 = 0;
    floor2 = 0;
    digitalWrite(floor1LED, LOW);
    digitalWrite(floor2LED, LOW);
    digitalWrite(floor3LED, LOW);
  }
  delay(100);
}



