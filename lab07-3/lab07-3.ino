#include <I2Cdev.h>
#include <MPU6050.h>
#include <Wire.h>
MPU6050 accelgyro;

int16_t mx, my, mz;
int16_t ax, ay, az, gx, gy, gz;

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(38400);
  Serial.println("Initializing I2C devices...");

 	accelgyro.initialize();	  // 初始化 I2C devices 
  
  Serial.println("Testing device connections…");
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "failed");
}

void loop() {
  // put your main code here, to run repeatedly:
  	accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    // Serial.print("a/g:\t");
      Serial.print(ax); Serial.print("\t");
      Serial.print(ay); Serial.print("\t");
      Serial.print(az); Serial.print("\t");
      Serial.print(gx); Serial.print("\t");
      Serial.print(gy); Serial.print("\t");
      Serial.println(gz);
}


