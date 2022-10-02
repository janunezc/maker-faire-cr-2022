void setup() {
  Serial.begin(9600);
  Serial.println("Bienvenido al problema del Beep");
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
}

bool bcSetup = false;
long timeInit = millis();
void loop() {
  int segundos =  (millis() - timeInit) / 1000;
  printSeconds(segundos);  

  if (segundos > 0 && segundos % 10 == 0 && bcSetup == false) {
    beepCompartido_Setup(300/*ms ON*/,250/*ms OFF*/,3 /*VECES*/);
    bcSetup = true;
  }
  
  beepCompartido();
}

void printSeconds(int segundos){
  Serial.print("Segundos: ");
  Serial.print(segundos);
  Serial.print(" - ");
  Serial.println(millis());
}

int bc_tiempo_ON = 0;
int bc_tiempo_OFF = 0;
long bc_maxCuenta = 0;

long bc_sigMomento_ON = 0;
long bc_sigMomento_OFF = 0;
long bc_cuenta = 0;

void beepCompartido_Setup(int tiempoONms, int tiempoOFFms, int veces){
  bc_tiempo_ON = tiempoONms;
  bc_tiempo_OFF = tiempoOFFms;
  bc_maxCuenta = veces;

  bc_cuenta = 0;
  bc_sigMomento_ON = 0;
  bc_sigMomento_OFF = 0;
}

void beepCompartido(){
  if( bcSetup == false ) return;
  Serial.print("beepCompartido() ENTERED");

  Serial.print("|");
  Serial.print("bc_sigMomento_ON: ");
  Serial.print(bc_sigMomento_ON);

  Serial.print("|");
  Serial.print("bc_sigMomento_OFF: ");
  Serial.print(bc_sigMomento_OFF);

  Serial.print("|");
  Serial.print("bc_cuenta: ");
  Serial.print(bc_cuenta);

  Serial.println("|");  

  if(bc_cuenta < bc_maxCuenta){
    if(millis() > bc_sigMomento_ON){
      bc_sigMomento_ON = millis() + bc_tiempo_ON + bc_tiempo_OFF;
      bc_sigMomento_OFF = millis() + bc_tiempo_ON;
      digitalWrite(LED_BUILTIN, HIGH);
    }
    
    if(millis() > bc_sigMomento_OFF){
      bc_sigMomento_OFF = millis() + bc_tiempo_ON + bc_tiempo_OFF;
      bc_sigMomento_ON = millis() + bc_tiempo_OFF;
      bc_cuenta ++ ;
      digitalWrite(LED_BUILTIN, LOW);
    }
  } else {
    bcSetup = false;
  }
}
