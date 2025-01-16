#define Triezvy 1950   // Definuj max hodnotu, ktorú považuješ, za triezvu
#define Opity 2070   // Definuj min hodnotu, ktorú považuješ, za opitú
#define MQ3 34       // Definuj analógový vstup pre snímač MQ3
#define ledPin 33    // Zmena na pin s podporou PWM, pin 33(použij, akýkoľvek pin podporujúci PWM)

float sensorValue;  // Variabilná hodnota snímača na uloženie

void setup() {
  Serial.begin(115200); // nastavenie sériového portu na 115200
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.println("MQ3 Heating Up!");
  delay(20000); // Nechať snímač MQ3 zahriať
}

void loop() {
  sensorValue = analogRead(MQ3); // Čítanie analógového vstupného pinu 0
  Serial.print("Sensor Value: ");
  Serial.print(sensorValue);

  // Určiť stav na základe hodnoty snímača
  if (sensorValue < Triezvy) {
    Serial.println("  |  Status: Triezvy");
  } else if (sensorValue >= Triezvy && sensorValue < Opity) {
    Serial.println("  |  Status: Pitie, ale v zakonnom limite");
  } else {
    Serial.println("  |  Status: Opity");
  }

  // Namapovať hodnotu snímača na rozsah PWM (0-255)
  unsigned int outputValue = map(sensorValue, 0, 1023, 0, 255);

  // Ovládať LED na základe hodnoty snímača
  if (sensorValue > Opity) {
    digitalWrite(ledPin, HIGH); // Zapni LED, ak je hodnota vysoká
    //analogWrite(ledPin, outputValue); // Generuj signal PWM na úpravu jasu LED
  } else {
    digitalWrite(ledPin, LOW); // Ak je hodnota nízka, vypni LED diódu
  }

  delay(2000); // Počkaj 2 sekundy na ďalšie čítanie
}