void setup() {
  Serial.begin(9600);
  Serial.println("Bienvenido al problema del Beep");
  pinMode(LED_BUILTIN, OUTPUT);
}

long timeInit = millis();
void loop() {
  int segundos =  (millis() - timeInit) / 1000;
  printSeconds(segundos);
  
  if (segundos > 0 && segundos % 10 == 0) {
    beep(250, 250, 4);
  }
}

void printSeconds(int segundos){
  Serial.print("Segundos: ");
  Serial.println(segundos);
}

void beep(int tiempoDeSonido, int tiempoDePausa, int veces) {
  for (int i = 0; i < veces; i++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(tiempoDeSonido);
    digitalWrite(LED_BUILTIN, LOW);
    delay(tiempoDePausa);
  }
}
