#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Bounce2.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pin-Definitionen für die Taster
const int tasterPins[] = {4, 2, 3}; // Umschalten, Stunden einstellen, Minuten einstellen
Bounce debouncers[3]; // Array für die Bounce-Objekte

bool showingTime = true;  // true = Uhrzeit anzeigen, false = Weckzeit anzeigen

int currentHour = 0;
int currentMinute = 0;
int alarmHour = 0;
int alarmMinute = 0;

unsigned long previousMillis = 0;  // Zur Zeitmessung
unsigned long scrollPreviousMillis = 0;  // Zur Steuerung der Laufschrift
const long scrollInterval = 500;  // Scroll-Intervall in Millisekunden
int scrollPosition = 0;

const int ledPin = 7; // LED-Pin
const int piezoPin = 6; // Piezo-Pin

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();

  // Pin-Modi und Bounce-Initialisierung
  for (int i = 0; i < 3; i++) {
    pinMode(tasterPins[i], INPUT_PULLUP);
    debouncers[i].attach(tasterPins[i]);
    debouncers[i].interval(20);
  }

  pinMode(ledPin, OUTPUT); // LED-Pin als Ausgang festlegen
  pinMode(piezoPin, OUTPUT); // Piezo-Pin als Ausgang festlegen

  lcd.clear();
  displayTime();
  Serial.println("Bitte geben Sie die aktuelle Uhrzeit im Format HH:MM ein:");
}

void loop() {
  checkSerialInput();
  updateTime();
  updateButtons();
  updateScrollText();
  checkAlarm();  // Funktion zum Überprüfen des Alarms aufrufen
}

void checkSerialInput() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    int separator = input.indexOf(':');
    if (separator != -1) {
      currentHour = input.substring(0, separator).toInt();
      currentMinute = input.substring(separator + 1).toInt();
      previousMillis = millis();
      scrollPreviousMillis = millis();
      scrollPosition = 0;
      displayTime();
    }
  }
}

void updateTime() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 60000) {  // Eine Minute vergangen
    previousMillis = currentMillis;
    currentMinute++;
    if (currentMinute >= 60) {
      currentMinute = 0;
      currentHour++;
      if (currentHour >= 24) {
        currentHour = 0;
      }
    }
    scrollPosition = 0;  // Zurücksetzen der Scroll-Position
    displayTime();
  }
}

void updateButtons() {
  for (int i = 0; i < 3; i++) {
    debouncers[i].update();
  }

  if (debouncers[0].fell()) {
    showingTime = !showingTime;
    scrollPosition = 0;  // Zurücksetzen der Scroll-Position
    displayTime();
  }

  if (debouncers[1].fell() && !showingTime) {
    alarmHour = (alarmHour + 1) % 24;
    displayTime();
  }

  if (debouncers[2].fell() && !showingTime) {
    alarmMinute = (alarmMinute + 1) % 60;
    displayTime();
  }
}

void updateScrollText() {
  unsigned long currentMillis = millis();
  if (showingTime && currentMillis - scrollPreviousMillis >= scrollInterval) {
    scrollPreviousMillis = currentMillis;
    scrollPosition++;
    displayScrollText();
  }
}

void checkAlarm() {
  if (currentHour == alarmHour && currentMinute == alarmMinute) {
    static unsigned long ledPreviousMillis = 0;
    const long ledInterval = 1000;  // Intervall für das Blinken der LED und Piezo (1 Sekunde)
    
    unsigned long currentMillis = millis();
    if (currentMillis - ledPreviousMillis >= ledInterval) {
      ledPreviousMillis = currentMillis;
      bool ledState = digitalRead(ledPin);  // Aktuellen Zustand der LED lesen
      digitalWrite(ledPin, !ledState);  // LED umschalten
      if (!ledState) {
        tone(piezoPin, 1000);  // Ton einschalten
      } else {
        noTone(piezoPin);  // Ton ausschalten
      }
    }
  } else {
    digitalWrite(ledPin, LOW);  // LED ausschalten, wenn keine Alarmzeit ist
    noTone(piezoPin);  // Piezo ausschalten, wenn keine Alarmzeit ist
  }
}

void displayScrollText() {
  String timeText = getTimeText(currentHour, currentMinute);
  int textLength = timeText.length();
  int displayWidth = 16;

  String displayText = "";
  for (int i = 0; i < displayWidth; i++) {
    int charIndex = (scrollPosition + i) % textLength;
    displayText += timeText[charIndex];
  }

  lcd.setCursor(0, 1);
  lcd.print(displayText);
}

void displayTime() {
  lcd.clear();
  if (showingTime) {
    lcd.setCursor(0, 0);
    lcd.print("Es ist:");
    displayScrollText();
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

String getTimeText(int hour, int minute) {
  String hourText = String(hour) + " Uhr ";
  String minuteText = String(minute) + " Minuten ";
  return hourText + minuteText + "   "; // Ein paar Leerzeichen am Ende für die Laufschrift
}
