#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include "webpages.h"

// ======== Konfiguration ========
const int STEP_PIN = 19;
const int DIR_PIN = 18;
const int SWITCH_PIN = 5;
const int ENDSTOP_PIN = 17;
// ---------------------------------------------------------------

const char* ssid = "Ayham Salha";
const char* password = "12345678";
// ---------------------------------------------------------------
WebServer server(80);

volatile bool stopFlag = false;
bool running = false;
bool homingDone = false;

void IRAM_ATTR endstopISR() {
  stopFlag = true;
}
// ---------------------------------------------------------------
int stepsPerRevolution = 200;
int roundCount = 0;
int distanceCm = 0;
int speedValue = 5;
int delay_us = 500;
//--------------------------------------------------------------
// Old homing
void doHoming() {
  digitalWrite(DIR_PIN, HIGH);
  while (digitalRead(SWITCH_PIN) == HIGH) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(100); 
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(100);
  }
  homingDone = true;
}
// -----------------------------------------------------------------------------------------------------------------

void moveMotor() {
  int stepsPerCm = 360;
  int stepsPerRun = distanceCm * stepsPerCm;

  int minDelay = 1200, maxDelay = 60;  // Speed slider: 1=slow, 10=fast
  delay_us = minDelay - ((speedValue - 1) * (minDelay - maxDelay) / 9);


  for (int i = 0; i < roundCount; i++) {
    if (stopFlag) break;

    digitalWrite(DIR_PIN, LOW);
    for (int j = 0; j < stepsPerRun; j++) {
      if (stopFlag) break;

      digitalWrite(STEP_PIN, HIGH);
      delayMicroseconds(2);             // Short pulse
      digitalWrite(STEP_PIN, LOW);
      delayMicroseconds(delay_us);      // Controlled speed delay

      server.handleClient();
    }

    if (stopFlag) break;

    digitalWrite(DIR_PIN, HIGH);
    for (int j = 0; j < stepsPerRun; j++) {
      if (stopFlag) break;

      digitalWrite(STEP_PIN, HIGH);
      delayMicroseconds(2);
      digitalWrite(STEP_PIN, LOW);
      delayMicroseconds(delay_us);

      server.handleClient();
    }
  }

  if (!stopFlag) {
    doHoming();
    homingDone = false;
  }
}
// -----------------------------------------------------------------------------------------------------------------

void handleRoot() {
  server.send(200, "text/html", startPage);
}
// -----------------------------------------------------------------------------------------------------------------

void handleInput() {
  if (!homingDone) doHoming();
  server.send(200, "text/html", inputPage);
}
// -----------------------------------------------------------------------------------------------------------------

void handleSubmit() {
  if (server.hasArg("runden")) roundCount = server.arg("runden").toInt(); 
  if (server.hasArg("distance")) distanceCm = server.arg("distance").toInt();
  if (server.hasArg("speed")) speedValue = server.arg("speed").toInt();

  stopFlag = false;
  running = true;
  server.send(200, "text/html", stopPage);
}
// -----------------------------------------------------------------------------------------------------------------

void handleWebStop() {
  stopFlag = true;
  running = false;
  roundCount = 0; // Runden zurücksetzen
  distanceCm = 0; // Strecke zurücksetzen
  homingDone = false; // Homing zurücksetzen

  server.send(200, "text/html", startPage);
}
// -----------------------------------------------------------------------------------------------------------------

void setup() {
  Serial.begin(115200);
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(SWITCH_PIN, INPUT_PULLUP);
  pinMode(ENDSTOP_PIN, INPUT_PULLUP);

  WiFi.softAP(ssid, password);
  Serial.print("Access Point IP: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", handleRoot);
  server.on("/input", handleInput);
  server.on("/submit", handleSubmit);
  server.on("/stop", handleWebStop);
  server.begin();

  attachInterrupt(digitalPinToInterrupt(ENDSTOP_PIN), endstopISR, FALLING);
}
// -----------------------------------------------------------------------------------------------------------------

void loop() {
  server.handleClient();
  if (running) {
    stopFlag = false;
    moveMotor();
    running = false;
  }
}
// -----------------------------------------------------------------------------------------------------------------
// Ende von main.cpp
// Das Programm ist ein einfacher Webserver, der es ermöglicht, einen Schrittmotor über eine Webschnittstelle zu steuern.
// Es gibt eine Startseite, eine Eingabeseite für die Anzahl der Schritte und die Strecke, und eine Sicherheitsseite, wenn der Motor läuft.