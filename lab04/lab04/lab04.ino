const int sensorPin = A0;
const int ledPin = 9;
const int numReading = 10;

int readings[numReading];
int readIndex = 0;
int total = 0;
int average = 0;



int sensorValue = 0;
int sensorMin = 1023;
int sensorMax = 0;


void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  // 初始化
  for (int i = 0; i < numReading; i++) {
    readings[i] = 0;
  }
  Calibration();
}

void loop() {
  sensorValue = analogRead(sensorPin);
  sensorValue = map(sensorValue, sensorMin, sensorMax, 0, 255);

  sensorValue = constrain(sensorValue, 0, 255);
  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);
  if (sensorValue < average) {
    analogWrite(ledPin, 255);
  }
  if (sensorValue > average) {
    analogWrite(ledPin, 0);
  }
}


void Smoothing() {
  total -= readings[readIndex];
  readings[readIndex] = analogRead(sensorPin);
  total += readings[readIndex];
  readIndex += 1;
  if (readIndex >= numReading) {
    readIndex = 0;
  }
  average = total / numReading;
  Serial.print("average: ");
  Serial.println(average);
  delay(1);
}


void Calibration() {
  Serial.println("開始校準");
  digitalWrite(ledPin, HIGH);
  while (millis() < 5000) {
    // sensorValue = analogRead(sensorPin);
    Smoothing();
    if (average > sensorMax) {
      sensorMax = average;
    }
    if (average < sensorMin) {
      sensorMin = average;
    }
  }
  digitalWrite(ledPin, LOW);
  Serial.println("停止校準");
}


