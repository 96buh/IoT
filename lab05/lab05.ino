const int photocellPin = A0;
const int buttonPin = 8;
const int ledPin = 9;

int buttonState = 0;
int sensorValue = 0;
int password = 1;
int userInput = 0;

void setup() {
    Serial.begin(9600);
    pinMode(ledPin, OUTPUT);
    pinMode(buttonPin, INPUT);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  sensorValue = analogRead(photocellPin);
  if (buttonState == HIGH) {
    password = sensorValue;
  }

  if (Serial.available()) {
    userInput = Serial.parseInt();
  }
  Serial.print("Password: ");
  Serial.println(password);
  Serial.print("User type: ");
  Serial.println(userInput);
  if (userInput > password) {
    Serial.println("Too Large");
    digitalWrite(ledPin, LOW);
  }
  if (userInput < password) {
    Serial.println("Too Small");
    digitalWrite(ledPin, LOW);
  }
  if (userInput == password) {
    Serial.println("正確");
    digitalWrite(ledPin, HIGH);
  }
}
