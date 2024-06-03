#include <Servo.h>

Servo servo1; // Declaramos un objeto Servo para el primer motor
Servo servo2; // Declaramos un objeto Servo para el segundo motor
Servo servo3; // Declaramos un objeto Servo para el tercer motor
Servo servo4; // Declaramos un objeto Servo para el cuarto motor

int pos1 = 90;
int pos2 = 40;
int pos3 = 180;
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

  while (pos2 != 40){
    if(pos2 > 40){
      pos2 = pos2 - 2;
    }else{
      pos2 = pos2 + 2;
    }
    refreshServos();
  }
  
  while (pos3 != 180){
    if(pos3 > 180){
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

void pushKey(int p1, int p2, int p3, int p4,int p2_Click){  
  //pos2 = p2-10;
  //if (pos4 > 90){
  //  roboticMovement4(p4);
  //}
  roboticMovement2(p2-20);
  refreshServos();
  delay(1000);
  //pos1 = p1;
  //pos3 = p3;
  //pos4 = p4;
  pos1 = p1;
  refreshServos();
  delay(1500);
  roboticMovement3(p3);
  roboticMovement4(p4);
  refreshServos();
  delay(1000);
  roboticMovement2(p2);
  refreshServos();
  delay(1000);
  pos2 = p2_Click;
  refreshServos();
  delay(100);
  pos2 = p2;
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
        case 'a':
          pushKey(126, 56, 160, 66, 70);
          Serial.println("Escribiendo una A");
          break;
        case 'b':
          pushKey(90, 20, 180, 116, 36);
          Serial.println("Escribiendo una B");
          break;
        case 'c':
          pushKey(112, 24, 180, 100, 40);
          Serial.println("Escribiendo una C");
          break;
        case 'd':
          pushKey(112, 40, 166, 90, 56);
          Serial.println("Escribiendo una D");
          break;
        case 'e':
          pushKey(112, 50, 168, 60, 66);
          Serial.println("Escribiendo una E");
          break;
        case 'f':
          pushKey(108, 30, 180, 86, 46);
          Serial.println("Escribiendo una F");
          break;
        case 'g':
          pushKey(98, 30, 180, 86, 46);
          Serial.println("Escribiendo una G");
          break;
        case 'h':
          pushKey(88, 30, 180, 90, 46);
          Serial.println("Escribiendo una H");
          break;
        case 'i':
          pushKey(72, 40, 176, 66, 56);
          Serial.println("Escribiendo una I");
          break;
        case 'j':
          pushKey(78, 30, 180, 90, 46);
          Serial.println("Escribiendo una J");
          break;
        case 'k':
          pushKey(68, 30, 180, 84, 46);
          Serial.println("Escribiendo una K");
          break;
        case 'l':
          pushKey(60, 30, 180, 80, 46);
          Serial.println("Escribiendo una L");
          break;
        case 'm':
          pushKey(70, 16, 180, 116, 30);
          Serial.println("Escribiendo una M");
          break;
        case 'n':
          pushKey(80, 16, 180, 116, 30);
          Serial.println("Escribiendo una N");
          break;
        case 'ñ':
          pushKey(52, 30, 170, 80, 50);
          Serial.println("Escribiendo una Ñ");
          break;
        case 'o':
          pushKey(64, 40, 176, 68, 60);
          Serial.println("Escribiendo una O");
          break;
        case 'p':
          pushKey(58, 46, 160, 70, 56);
          Serial.println("Escribiendo una P");
          break;
        case 'q':
          pushKey(124, 70, 130, 70, 86);
          Serial.println("Escribiendo una Q");
          break;
        case 'r':
          pushKey(106, 40, 180, 60, 56);
          Serial.println("Escribiendo una R");
          break;
        case 's':
          pushKey(120, 46, 166, 70, 60);
          Serial.println("Escribiendo una S");
          break;
        case 't':
          pushKey(100, 40, 180, 60, 56);
          Serial.println("Escribiendo una T");
          break;
        case 'u':
          pushKey(80, 40, 180, 66, 56);
          Serial.println("Escribiendo una U");
          break;
        case 'v':
          pushKey(106, 20, 180, 110, 36);
          Serial.println("Escribiendo una V");
          break;
        case 'w':
          pushKey(118, 56, 156, 60, 70);
          Serial.println("Escribiendo una W");
          break;
        case 'x':
          pushKey(122, 40, 166, 106, 50);
          Serial.println("Escribiendo una X");
          break;
        case 'y':
          pushKey(90, 40, 180, 66, 56);
          Serial.println("Escribiendo una Y");
          break;
        case 'z':
          pushKey(126, 40, 166, 90, 56);
          Serial.println("Escribiendo una Z");
          break;
        default:
          Serial.println("Letra no reconocida");
          break;
      }
    }
  }
}