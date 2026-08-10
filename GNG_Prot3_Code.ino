#include "DFRobotDFPlayerMini.h"
#include "SoftwareSerial.h"

// -----------------------------
// Button Inputs (Analog Pins)
// -----------------------------
const int SW_L = A0;
const int SW_F = A1;
const int SW_R = A2;
const int SW_B = A3;
const int SW_HORN = A4;

// -----------------------------
// HC-SR04 Pin Assignments
// -----------------------------
const int TRIG_FL = 4;
const int ECHO_FL = 5;
const int TRIG_FR = 6;
const int ECHO_FR = 7;

const int TRIG_BL = 8;
const int ECHO_BL = 9;
const int TRIG_BC = 10;
const int ECHO_BC = 11;
const int TRIG_BR = 12;
const int ECHO_BR = 13;

// Consecutive detection counters
int flCount = 0;
int frCount = 0;
int blCount = 0;
int bcCount = 0;
int brCount = 0;

const int DETECTION_COUNT = 2;

// Horn (active LOW)
bool hornWasPressed = false;

// -----------------------------
// Audio Keep-Alive
// -----------------------------
const byte NORMAL_VOLUME = 30;
const byte KEEPALIVE_VOLUME = 0;

unsigned long lastSoundTime = 0;
const unsigned long KEEPALIVE_INTERVAL = 30000UL;  // 30 seconds

// -----------------------------
// Sensor Read Function
// -----------------------------
long readSensor(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);

  if (duration == 0) return -1;

  return duration * 0.0343 / 2;
}

// -----------------------------
// Returns alert volume based on distance
// 0 = no alert
// -----------------------------
int getAlertVolume(long distance) {
  if (distance <= 0) return 0;

  if (distance < 30)  // 30
    return 0;         // Ignore 0-30 cm

  if (distance < 50)  // 50
    return 30;        // High

  if (distance <= 80)  // 80
    return 20;         // Medium

  return 0;  // Beyond 80 cm
}

// -----------------------------
// Initializing DFPlayer
// -----------------------------

// Use pins 2 and 3 to communicate with DFPlayer Mini
static const uint8_t PIN_MP3_TX = 2;  // Connects to module's RX
static const uint8_t PIN_MP3_RX = 3;  // Connects to module's TX
SoftwareSerial softwareSerial(PIN_MP3_RX, PIN_MP3_TX);

// Create the Player object
DFRobotDFPlayerMini player;

// -----------------------------
// Setup
// -----------------------------
void setup() {
  // Speaker Code
  // Init USB serial port for debugging
  Serial.begin(9600);
  // Init serial port for DFPlayer Mini
  softwareSerial.begin(9600);

  delay(1000);

  if (!player.begin(softwareSerial)) {
    Serial.println("DFPlayer failed");
  } else {
    Serial.println("DFPlayer OK");
    player.volume(NORMAL_VOLUME);
    player.playMp3Folder(1);

    lastSoundTime = millis();
  }

  pinMode(SW_L, INPUT_PULLUP);
  pinMode(SW_F, INPUT_PULLUP);
  pinMode(SW_R, INPUT_PULLUP);
  pinMode(SW_B, INPUT_PULLUP);

  pinMode(SW_HORN, INPUT_PULLUP);

  pinMode(TRIG_FL, OUTPUT);
  pinMode(ECHO_FL, INPUT);

  pinMode(TRIG_FR, OUTPUT);
  pinMode(ECHO_FR, INPUT);

  pinMode(TRIG_BL, OUTPUT);
  pinMode(ECHO_BL, INPUT);

  pinMode(TRIG_BC, OUTPUT);
  pinMode(ECHO_BC, INPUT);

  pinMode(TRIG_BR, OUTPUT);
  pinMode(ECHO_BR, INPUT);
}

// -----------------------------
// Main Loop
// -----------------------------
void loop() {
  // Read switch states
  bool L = (digitalRead(SW_L) == LOW);
  bool F = (digitalRead(SW_F) == LOW);
  bool R = (digitalRead(SW_R) == LOW);
  bool B = (digitalRead(SW_B) == LOW);

  bool hornPressed = (digitalRead(SW_HORN) == LOW);

  if (hornPressed && !hornWasPressed) {
    player.volume(NORMAL_VOLUME);
    player.playMp3Folder(7);
    lastSoundTime = millis();
  }

  hornWasPressed = hornPressed;

  // -----------------------------
  // Determine active sensors
  // -----------------------------

  bool FL = F && L;
  bool FR = F && R;

  bool BL = B && L;
  bool BC = B;
  bool BR = B && R;

  // -----------------------------
  // Read enabled sensors
  // -----------------------------

  long dFL = FL ? readSensor(TRIG_FL, ECHO_FL) : -1;
  long dFR = FR ? readSensor(TRIG_FR, ECHO_FR) : -1;

  long dBL = BL ? readSensor(TRIG_BL, ECHO_BL) : -1;
  long dBC = BC ? readSensor(TRIG_BC, ECHO_BC) : -1;
  long dBR = BR ? readSensor(TRIG_BR, ECHO_BR) : -1;

  // -----------------------------
  // Update detection filters
  // -----------------------------

  flCount = (getAlertVolume(dFL) > 0) ? min(flCount + 1, DETECTION_COUNT) : 0;
  frCount = (getAlertVolume(dFR) > 0) ? min(frCount + 1, DETECTION_COUNT) : 0;
  blCount = (getAlertVolume(dBL) > 0) ? min(blCount + 1, DETECTION_COUNT) : 0;
  bcCount = (getAlertVolume(dBC) > 0) ? min(bcCount + 1, DETECTION_COUNT) : 0;
  brCount = (getAlertVolume(dBR) > 0) ? min(brCount + 1, DETECTION_COUNT) : 0;

  // -----------------------------
  // Play all active directions
  // -----------------------------

  static unsigned long lastPlayTime = 0;
  static int nextSound = 1;

  if (millis() - lastPlayTime > 1000) {
    bool played = false;

    for (int i = 0; i < 5 && !played; i++) {
      int sound = ((nextSound + i - 1) % 5) + 1;

      int volumeFL = getAlertVolume(dFL);
      int volumeFR = getAlertVolume(dFR);
      int volumeBL = getAlertVolume(dBL);
      int volumeBC = getAlertVolume(dBC);
      int volumeBR = getAlertVolume(dBR);

      switch (sound) {
        case 1:
          if (flCount >= DETECTION_COUNT && volumeFL > 0) {
            player.volume(volumeFL);
            player.playMp3Folder(2);

            if (volumeFL == 30)
              Serial.println("FRONT LEFT HIGH");
            else if (volumeFL == 20)
              Serial.println("FRONT LEFT MEDIUM");

            played = true;
          }
          break;

        case 2:
          if (frCount >= DETECTION_COUNT && volumeFR > 0) {
            player.volume(volumeFR);
            player.playMp3Folder(3);

            if (volumeFR == 30)
              Serial.println("FRONT RIGHT HIGH");
            else if (volumeFR == 20)
              Serial.println("FRONT RIGHT MEDIUM");

            played = true;
          }
          break;

        case 3:
          if (blCount >= DETECTION_COUNT && volumeBL > 0) {
            player.volume(volumeBL);
            player.playMp3Folder(4);

            if (volumeBL == 30)
              Serial.println("BACK LEFT HIGH");
            else if (volumeBL == 20)
              Serial.println("BACK LEFT MEDIUM");

            played = true;
          }
          break;

        case 4:
          if (bcCount >= DETECTION_COUNT && volumeBC > 0) {
            player.volume(volumeBC);
            player.playMp3Folder(5);

            if (volumeBC == 30)
              Serial.println("BACK CENTER HIGH");
            else if (volumeBC == 20)
              Serial.println("BACK CENTER MEDIUM");

            played = true;
          }
          break;

        case 5:
          if (brCount >= DETECTION_COUNT && volumeBR > 0) {
            player.volume(volumeBR);
            player.playMp3Folder(6);

            if (volumeBR == 30)
              Serial.println("BACK RIGHT HIGH");
            else if (volumeBR == 20)
              Serial.println("BACK RIGHT MEDIUM");

            played = true;
          }
          break;
      }

      if (played) {
        nextSound = sound + 1;
        if (nextSound > 5) nextSound = 1;

        lastPlayTime = millis();
        lastSoundTime = millis();
      }
    }
  }

  // -----------------------------
  // Keep Power Bank Awake
  // -----------------------------
  if (millis() - lastSoundTime >= KEEPALIVE_INTERVAL) {
    Serial.println("Keep Alive");

    player.volume(KEEPALIVE_VOLUME);
    player.playMp3Folder(7);

    delay(1500);  // Give DFPlayer time to accept command

    player.volume(NORMAL_VOLUME);

    lastSoundTime = millis();
  }

  // -----------------------------
  // Print states
  // -----------------------------

  Serial.print("L:");
  Serial.print(L);

  Serial.print(" F:");
  Serial.print(F);

  Serial.print(" R:");
  Serial.print(R);

  Serial.print(" B:");
  Serial.print(B);

  Serial.print(" | FL:");
  Serial.print(dFL);

  Serial.print(" FR:");
  Serial.print(dFR);

  Serial.print(" BL:");
  Serial.print(dBL);

  Serial.print(" BC:");
  Serial.print(dBC);

  Serial.print(" BR:");
  Serial.println(dBR);

  delay(60);
}