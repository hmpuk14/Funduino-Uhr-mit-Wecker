#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Bounce2.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pin-Definitionen für die Taster
const int tasterPins[] = {4, 2, 3}; // Umschalten, Stunden einstellen, Minuten einstellen
Bounce debouncers[3]; // Array für die Bounce-Objekte

bool showingTime = true;  // true = Uhrzeit anzeigen, false = Weckzeit anzeigen

int currentHour = 11;
int currentMinute = 21;
int alarmHour = 6;
int alarmMinute = 0;

void setup() {
  lcd.init();
  lcd.backlight();

  // Pin-Modi und Bounce-Initialisierung
  for (int i = 0; i < 3; i++) {
    pinMode(tasterPins[i], INPUT_PULLUP);
    debouncers[i].attach(tasterPins[i]);
    debouncers[i].interval(20);
  }

  lcd.clear();
  displayTime();
}

void loop() {
  // Taster entprellen
  for (int i = 0; i < 3; i++) {
    debouncers[i].update();
  }

  // Umschalten zwischen Uhrzeit und Weckzeit
  if (debouncers[0].fell()) {
    showingTime = !showingTime;
    displayTime();
  }

  // Stunden einstellen
  if (debouncers[1].fell()) {
    if (showingTime) {
      currentHour++;
      if (currentHour >= 24) {
        currentHour = 0;
      }
    } else {
      alarmHour++;
      if (alarmHour >= 24) {
        alarmHour = 0;
      }
    }
    displayTime();
  }

  // Minuten einstellen
  if (debouncers[2].fell()) {
    if (showingTime) {
      currentMinute++;
      if (currentMinute >= 60) {
        currentMinute = 0;
      }
    } else {
      alarmMinute++;
      if (alarmMinute >= 60) {
        alarmMinute = 0;
      }
    }
    displayTime();
  }
}

void displayTime() {
  lcd.clear();
  if (showingTime) {
    lcd.setCursor(0, 0);
    lcd.print("Uhrzeit:");
    lcd.setCursor(0, 1);
    lcd.print(currentHour < 10 ? "0" : "");
    lcd.print(currentHour);
    lcd.print(":");
    lcd.print(currentMinute < 10 ? "0" : "");
    lcd.print(currentMinute);
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Weckzeit:");
    lcd.setCursor(0, 1);
    lcd.print(alarmHour < 10 ? "0" : "");
    lcd.print(alarmHour);
    lcd.print(":");
    lcd.print(alarmMinute < 10 ? "0" : "");
    lcd.print(alarmMinute);
  }
}
