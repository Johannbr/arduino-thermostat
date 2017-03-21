#include <Time.h>

float tempC;
int reading;
int tempPin = A0;

#define DIVTEMP 9.31
#define CYCLE 50
const int relaySignalPin = 2;
int incr = 0;

void setup() {
  analogReference(INTERNAL);
  Serial.begin(9600);
  pinMode(relaySignalPin, OUTPUT);
}

void loop() {
  reading = analogRead(tempPin);
  float tempRead = convertToTemp(reading);
  // Serial.println(convertToTemp(reading));
  int tempTarget = 20;
  if (incr >= CYCLE){
    incr = 0;

    if (tempRead < tempTarget) {
      startHeating();
    } else {
      stopHeating();
    }
    Serial.println(convertToTemp(reading));
  }
  incr++;
  delay(100);
}

float convertToTemp(float reading) { return reading / DIVTEMP; }

void startHeating() {
  Serial.print(" Heating... ");
  digitalWrite(relaySignalPin, LOW);
}
void stopHeating() {
  Serial.print(" Cooling... ");
  digitalWrite(relaySignalPin, HIGH);
}
