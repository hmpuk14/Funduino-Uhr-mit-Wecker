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

  // LCD löschen
  lcd.clear();

  // Text auf dem LCD ausgeben
  lcd.setCursor(0, 0); // Setze den Cursor auf die erste Zeile, erste Spalte
  lcd.print("Projekt Uhr mit");
  lcd.setCursor(0, 1); // Setze den Cursor auf die zweite Zeile, erste Spalte
  lcd.print("Wecker");

  Serial.println("Text auf LCD ausgegeben.");
}

void loop() {
  // Keine weitere Aktion erforderlich
}
