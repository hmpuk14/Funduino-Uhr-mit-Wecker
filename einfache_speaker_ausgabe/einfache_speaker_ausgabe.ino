const int piezoPin = 6;  // Piezo-Pin

void setup() {
  pinMode(piezoPin, OUTPUT);  // Piezo-Pin als Ausgang festlegen
}

void loop() {
  tone(piezoPin, 1000);  // Ton mit 1000 Hz erzeugen
  delay(1000);           // Eine Sekunde warten
  noTone(piezoPin);      // Ton ausschalten
  delay(1000);           // Eine Sekunde warten
}
