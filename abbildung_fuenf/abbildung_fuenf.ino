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
}

void loop() {
  // Text "Projekt Uhr" anzeigen
  lcd.clear();
  lcd.setCursor(0, 0); // Setze den Cursor auf die erste Zeile, erste Spalte
  lcd.print("Projekt Uhr");
  delay(2000); // Warte 2 Sekunden

  // Text "mit Wecker" anzeigen
  lcd.clear();
  lcd.setCursor(0, 0); // Setze den Cursor auf die erste Zeile, erste Spalte
  lcd.print("mit Wecker");
  delay(2000); // Warte 2 Sekunden
}
