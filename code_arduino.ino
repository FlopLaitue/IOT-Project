float t = 0.0;
int mode = 0;

void setup() {
  Serial.begin(115200);
  randomSeed(analogRead(A1));
}

void loop() {
  const char* materiau;
  float f, d, amp;

  // Choix du matériau simulé
  if (mode == 0) {
    materiau = "metal";
    f = 20.0;
    d = 0.8;
    amp = 1.0;
  } 
  else if (mode == 1) {
    materiau = "bois";
    f = 10.0;
    d = 1.8;
    amp = 0.8;
  } 
  else if (mode == 2) {
    materiau = "pierre";
    f = 15.0;
    d = 1.2;
    amp = 1.2;
  } 
  else {
    materiau = "terre";
    f = 6.0;
    d = 3.0;
    amp = 0.5;
  }

  // Signal vibratoire amorti + bruit
  float signal = amp * sin(2.0 * 3.14159 * f * t) * exp(-d * t);
  signal += random(-10, 10) / 200.0;

  // Envoi au PC
  Serial.print(materiau);
  Serial.print(",");
  Serial.println(signal, 4);

  t += 0.01;

  // Au bout de 1 seconde de signal, on change de matériau
  if (t > 1.0) {
    t = 0.0;
    mode = (mode + 1) % 4;
    delay(500); 
  }

  delay(10);
}