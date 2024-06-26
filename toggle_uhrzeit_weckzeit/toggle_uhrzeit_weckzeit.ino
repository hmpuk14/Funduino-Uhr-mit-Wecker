#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Bounce2.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int tasterEins = 4; // Taster-Pin
bool showingTime = true;  // true = Uhrzeit anzeigen, false = Weckzeit anzeigen

int currentHour = 11;
int currentMinute = 21;
int alarmHour = 6;
int alarmMinute = 0;

// Bounce-Objekt für den Taster
Bounce debouncer1 = Bounce();

void setup() {
  lcd.init();
  lcd.backlight();

  pinMode(tasterEins, INPUT_PULLUP); // INPUT_PULLUP für internen Pull-Up-Widerstand
  debouncer1.attach(tasterEins);
  debouncer1.interval(20);

  lcd.clear();
  displayTime();
}

void loop() {
  debouncer1.update();

  if (debouncer1.fell()) {  // Wenn der Taster gedrückt wird
    showingTime = !showingTime;  // Zustand umschalten
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
