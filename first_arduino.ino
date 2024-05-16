#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

const int rowPins[5] = {2, 3, 4, 5, 6}; // Pin untuk baris
const int colPins[5] = {7, 8, 9, 12, 13}; // Pin untuk kolom

void setup() {
  // Set up serial untuk debugging
  Serial.begin(9600);
  mySerial.begin(9600); // Serial untuk DFPlayer Mini

  // Set up DFPlayer Mini
  if (!myDFPlayer.begin(mySerial)) {
    Serial.println("DFPlayer Mini tidak terdeteksi");
    while (true);
  }
  myDFPlayer.volume(10); // Set volume (0-30)

  // Set baris sebagai output dan set ke HIGH
  for (int i = 0; i < 5; i++) {
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(rowPins[i], HIGH);
  }
  // Set kolom sebagai input dengan pull-up internal
  for (int i = 0; i < 5; i++) {
    pinMode(colPins[i], INPUT_PULLUP);
  }
}

void loop() {
  for (int row = 0; row < 5; row++) {
    // Aktifkan satu baris (LOW)
    digitalWrite(rowPins[row], LOW);
    // Baca semua kolom
    for (int col = 0; col < 5; col++) {
      if (digitalRead(colPins[col]) == LOW) {
        // Hitung nomor track berdasarkan posisi tombol
        int trackNumber = row * 5 + col + 1;
        
        // Modifikasi untuk mapping tombol
        // Misalkan tombol pada baris 1, kolom 1 dipetakan ke track 10
        // Ganti kondisi if dengan mapping yang sesuai untuk semua tombol
        if (row == 0 && col == 0) {
          trackNumber = 10;
        } else if (row == 0 && col == 1) {
          trackNumber = 11;
        } else if (row == 0 && col == 2) {
          trackNumber = 12;
        } else if (row == 0 && col == 3) {
          trackNumber = 13;
        } else if (row == 0 && col == 4) {
          trackNumber = 14;
        }

        // ... (lanjutkan mapping untuk semua tombol)

        Serial.print("Tombol pada baris ");
        Serial.print(row);
        Serial.print(" dan kolom ");
        Serial.print(col);
        Serial.print(" ditekan. Memainkan track ");
        Serial.println(trackNumber);
        myDFPlayer.play(trackNumber); // Mainkan track yang sesuai
        delay(500); // Debounce delay
      }
    }
    // Matikan kembali baris (HIGH)
    digitalWrite(rowPins[row], HIGH);
  }
}