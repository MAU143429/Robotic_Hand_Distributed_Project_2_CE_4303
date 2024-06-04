#include <Servo.h>

Servo servo1; // Declaramos un objeto Servo para el primer motor
Servo servo2; // Declaramos un objeto Servo para el segundo motor
Servo servo3; // Declaramos un objeto Servo para el tercer motor
Servo servo4; // Declaramos un objeto Servo para el cuarto motor

int pos1 = 90;
int pos2 = 20;
int pos3 = 90;
int pos4 = 50;

void setup() {
  Serial.begin(9600); // Inicializa la comunicación serie con la misma velocidad que en el programa en C

  servo1.attach(3);
  servo2.attach(9); // Conectamos el primer motor al pin 9
  servo3.attach(10); // Conectamos el segundo motor al pin 10
  servo4.attach(11); // Conectamos el tercer motor al pin 11

  refreshServos();
}

void refreshServos(){
  servo1.write(pos1);
  servo2.write(pos2);
  servo3.write(pos3);
  servo4.write(pos4);
  Serial.println("Posiciones actuales:");
  Serial.println("Pos1:");
  Serial.println(pos1);
  Serial.println("Pos2:");
  Serial.println(pos2);
  Serial.println("Pos3:");
  Serial.println(pos3);
  Serial.println("Pos4:");
  Serial.println(pos4);
}

void reset(){

  while (pos4 != 50){
    if(pos4 > 50){
      pos4 = pos4 - 2;
    }else{
      pos4 = pos4 + 2;
    }
    refreshServos();
  }

  while (pos2 != 26){
    if(pos2 > 26){
      pos2 = pos2 - 2;
    }else{
      pos2 = pos2 + 2;
    }
    refreshServos();
  }
  
  while (pos3 != 90){
    if(pos3 > 90){
      pos3 = pos3 - 2;
    }else{
      pos3 = pos3 + 2;
    }
    refreshServos();
  }
  
   while (pos1 != 90){
    if(pos1 > 90){
      pos1 = pos1 - 2;
    }else{
      pos1 = pos1 + 2;
    }
    refreshServos();
  }
}

void roboticMovement1(int position){
  while(pos1 != position){
    if(pos1 < position){
      pos1 = pos1+2;
    }else{
      pos1 = pos1-2;
    }
    refreshServos();
  }
}

void roboticMovement2(int position){
  while(pos2 != position){
    if(pos2 < position){
      pos2 = pos2+2;
    }else{
      pos2 = pos2-2;
    }
    refreshServos();
  }
}

void roboticMovement3(int position){
  while(pos3 != position){
    if(pos3 < position){
      pos3 = pos3+2;
    }else{
      pos3 = pos3-2;
    }
    refreshServos();
  }
}

void roboticMovement4(int position){
  while(pos4 != position){
    if(pos4 < position){
      pos4 = pos4+2;
    }else{
      pos4 = pos4-2;
    }
    refreshServos();
  }
}

void pushKey(int p1, int p2, int p3, int p4,int p3_Click){  
  roboticMovement2(p2-20);
  refreshServos();
  delay(1000);
  roboticMovement1(p1);
  refreshServos();
  delay(1500);
  roboticMovement2(p2);
  refreshServos();
  delay(1000);
  roboticMovement4(p4);
  refreshServos();
  delay(1000);
  roboticMovement3(p3);
  refreshServos();
  delay(1000);
  pos3 = p3_Click;
  refreshServos();
  delay(100);
  pos3 = p3;
  refreshServos();
  delay(100);
  reset();

}


void loop() {
  if (Serial.available() > 0) {
    String word = Serial.readStringUntil('\n'); // Lee la palabra enviada por el puerto serie hasta un salto de línea

    for (int i = 0; i < word.length(); i++) {
      char letter = word.charAt(i); // Toma cada letra de la palabra

      switch (letter) {
        case ',':
          reset();
          Serial.println("Reiniciando Posiciones");
          break;
        case 'a':
          pushKey(132, 56, 60, 120, 160);
          Serial.println("Escribiendo una A");
          break;
        case 'b':
          pushKey(98, 16, 110, 150, 150);
          Serial.println("Escribiendo una B");
          break;
        case 'c':
          pushKey(116, 16, 120, 130, 140);
          Serial.println("Escribiendo una C");
          break;
        case 'd':
          pushKey(116, 26, 120, 110, 160);
          Serial.println("Escribiendo una D");
          break;
        case 'e':
          pushKey(116, 26, 130, 80, 160);
          Serial.println("Escribiendo una E");
          break;
        case 'f':
          pushKey(108, 26, 114, 120, 150);
          Serial.println("Escribiendo una F");
          break;
        case 'g':
          pushKey(100, 26, 110, 130, 160);
          Serial.println("Escribiendo una G");
          break;
        case 'h':
          pushKey(86, 26, 110, 140, 150);
          Serial.println("Escribiendo una H");
          break;
        case 'i':
          pushKey(74, 40, 110, 120, 140);
          Serial.println("Escribiendo una I");
          break;
        case 'j':
          pushKey(80, 30, 100, 138, 130);
          Serial.println("Escribiendo una J");
          break;
        case 'k':
          pushKey(66, 36, 86, 144, 140);
          Serial.println("Escribiendo una K");
          break;
        case 'l':
          pushKey(58, 36, 94, 134, 120);
          Serial.println("Escribiendo una L");
          break;
        case 'm':
          pushKey(70, 16, 110, 150, 130);
          Serial.println("Escribiendo una M");
          break;
        case 'n':
          pushKey(82, 16, 110, 150, 130);
          Serial.println("Escribiendo una N");
          break;
        case 'o':
          pushKey(64, 44, 86, 116, 150);
          Serial.println("Escribiendo una O");
          break;
        case 'p':
          pushKey(56, 48, 80, 110, 160);
          Serial.println("Escribiendo una P");
          break;
        case 'q':
          pushKey(128, 70, 60, 100, 160);
          Serial.println("Escribiendo una Q"); 
          break;
        case 'r':
          pushKey(106, 40, 100, 110, 160);
          Serial.println("Escribiendo una R"); 
          break;
        case 's':
          pushKey(124, 50, 94, 130, 120);
          Serial.println("Escribiendo una S");
          break;
        case 't':
          pushKey(98, 46, 92, 124, 130);
          Serial.println("Escribiendo una T");
          break;
        case 'u':
          pushKey(80, 44, 90, 130, 110);
          Serial.println("Escribiendo una U"); 
          break;
        case 'v':
          pushKey(108, 16, 116, 144, 150);
          Serial.println("Escribiendo una V"); 
          break;
        case 'w':
          pushKey(122, 60, 90, 106, 140);
          Serial.println("Escribiendo una W");
          break;
        case 'x':
          pushKey(126, 16, 130, 120, 160);
          Serial.println("Escribiendo una X");
          break;
        case 'y':
          pushKey(90, 44, 100, 128, 130);
          Serial.println("Escribiendo una Y");
          break;
        case 'z':
          pushKey(134, 30, 130, 114, 160);
          Serial.println("Escribiendo una Z");
          break;
        default:
          Serial.println("Letra no reconocida");
          break;
      }
    }
  }
}
