#include <Time.h>

float tempC;
int reading;
int tempPin = A0;

#define DIVTEMP 9.31
#define DELAY 5000
#define THRESHOLD 1

const int relaySignalPin = 2;
enum heatingStates { Heating, Cooling };
enum heatingStates state;
long unsigned timer;

void setup() {
  analogReference(INTERNAL);
  Serial.begin(9600);
  pinMode(relaySignalPin, OUTPUT);
  state = Heating;
  timer = millis();
}

void loop() {
  reading = analogRead(tempPin);
  float tempRead = convertToTemp(reading);
  // Serial.println(convertToTemp(reading));
  int tempTarget = 21;
  if(millis() > timer + DELAY){
    timer = millis();
    if (state == Heating && tempRead < tempTarget + THRESHOLD) {
      startHeating();
    } else if (state == Heating && tempRead > tempTarget + THRESHOLD) {
      stopHeating();
    } else if (state == Cooling && tempRead > tempTarget - THRESHOLD) {
      stopHeating();
    } else {
      startHeating();
    }
    Serial.println(convertToTemp(reading));
  }
  delay(100);
}

float convertToTemp(float reading) { return reading / DIVTEMP; }

void startHeating() {
  Serial.print(" Heating... ");
  state = Heating;
  digitalWrite(relaySignalPin, LOW);
}
void stopHeating() {
  Serial.print(" Cooling... ");
  state = Cooling;
  digitalWrite(relaySignalPin, HIGH);
}
