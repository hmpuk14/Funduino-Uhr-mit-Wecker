#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD I2C Adresse und Dimensionen
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600); // Serielle Kommunikation beginnen
  Serial.println("LCD Initialisierung startet...");

  // Initialisierung des LCD
  lcd.init();  // Initialisiere das LCD
  lcd.backlight();

  // LCD löschen und initialen Text ausgeben
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Projekt Uhr mit Wecker");
}

void loop() {
  // Text scrollen lassen
  for (int positionCounter = 0; positionCounter < 20; positionCounter++) {
    lcd.scrollDisplayLeft();
    delay(300); // Warte 300 Millisekunden für langsameres Scrollen
  }

  // Text zurücksetzen
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Projekt Uhr mit Wecker");
}
