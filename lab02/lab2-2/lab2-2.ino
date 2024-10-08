const int buttonPin = 5;
const int ledPin = 6;
const int potenPin = A0;

int buttonState = 0;
int potenValue = 0;
float brightness = 0;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

// the loop function runs over and over again forever
void loop() {
  buttonState = digitalRead(buttonPin);
  potenValue = analogRead(potenPin);
  Serial.println(potenValue);
  delay(1);
  brightness = potenValue * (255.0 / 1023.0);
  Serial.println(brightness);
  delay(1);

  if (buttonState == HIGH) {
    SOS();
  }
}

void SOS() {
  // S
  analogWrite(ledPin, brightness);
  delay(200);
  analogWrite(ledPin, 0);
  delay(200);

  analogWrite(ledPin, brightness);
  delay(200);
  analogWrite(ledPin, 0);
  delay(200);

  analogWrite(ledPin, brightness);
  delay(200);
  analogWrite(ledPin, 0);
  delay(200);

  // O
  analogWrite(ledPin, brightness);
  delay(500);
  analogWrite(ledPin, 0);
  delay(500);

  analogWrite(ledPin, brightness);
  delay(500);
  analogWrite(ledPin, 0);
  delay(500);

  analogWrite(ledPin, brightness);
  delay(500);
  analogWrite(ledPin, 0);
  delay(500);

  // S
  analogWrite(ledPin, brightness);
  delay(200);
  analogWrite(ledPin, 0);
  delay(200);

  analogWrite(ledPin, brightness);
  delay(200);
  analogWrite(ledPin, 0);
  delay(200);

  analogWrite(ledPin, brightness);
  delay(200);
  analogWrite(ledPin, 0);
  delay(200);

}