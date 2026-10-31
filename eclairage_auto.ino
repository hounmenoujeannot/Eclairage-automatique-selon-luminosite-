/*
  Projet 4 : Éclairage automatique selon la luminosité
  Matériel : Arduino Uno, photorésistance (LDR) + résistance 10 kΩ,
             module relais 5 V (IN sur D7), lampe ou LED.
  Affichage : moniteur série (9600 bauds).
*/

const int PIN_LDR = A0;      // point milieu du pont LDR + 10 kΩ
const int PIN_RELAIS = 7;    // entrée IN du module relais

// Valeurs à ajuster selon le capteur et l'éclairage de la pièce
const int SEUIL_ALLUMER = 300;   // en dessous : il fait sombre
const int SEUIL_ETEINDRE = 400;  // au dessus : il fait clair

bool lampeAllumee = false;

void setup() {
  pinMode(PIN_RELAIS, OUTPUT);
  digitalWrite(PIN_RELAIS, LOW);
  Serial.begin(9600);
}

void loop() {
  int lumiere = analogRead(PIN_LDR);  // 0 à 1023

  // Hystérésis : deux seuils pour éviter le clignotement
  if (!lampeAllumee && lumiere < SEUIL_ALLUMER) {
    lampeAllumee = true;
  } else if (lampeAllumee && lumiere > SEUIL_ETEINDRE) {
    lampeAllumee = false;
  }

  digitalWrite(PIN_RELAIS, lampeAllumee ? HIGH : LOW);

  Serial.print("Lumiere = ");
  Serial.print(lumiere);
  Serial.print(" | Lampe = ");
  Serial.println(lampeAllumee ? "ON" : "OFF");

  delay(500);
}
