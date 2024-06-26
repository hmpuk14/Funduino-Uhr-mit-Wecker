int ledPin = 7; // Variable mit Pin 7 deklarieren + initialisieren
void setup() {
pinMode(ledPin, OUTPUT); // Digitaler Pin 7 als Ausgang
}
void loop() {
digitalWrite(ledPin, HIGH); // LED auf High-Pegel (5V)
delay(1000); // Eine Sekunde warten
digitalWrite(ledPin, LOW); // LED auf LOW-Pegel (0V)
delay(1000); // Eine Sekunde warten
}
