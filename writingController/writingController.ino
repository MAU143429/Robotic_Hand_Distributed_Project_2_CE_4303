#include <Servo.h>

Servo servo1; // Declaramos un objeto Servo para el primer motor
Servo servo2; // Declaramos un objeto Servo para el segundo motor
Servo servo3; // Declaramos un objeto Servo para el tercer motor

int pos1 = 0; // Posición inicial del servomotor 1
int pos2 = 0; // Posición intermedia del servomotor 1
int pos3 = 0; // Posición final del servomotor 

void setup() {
  servo1.attach(9); // Conectamos el primer motor al pin 9
  servo2.attach(10); // Conectamos el segundo motor al pin 10
  servo3.attach(11); // Conectamos el tercer motor al pin 11
}

void loop() {
  
  if(pos2 >= 90){
    pos3 =0;
    pos2 = 0;
  }else{
    pos3++;
    pos2++;
  }


  delay(50); // Esperar 1 segundo

  servo1.write(pos1); // Mover el servomotor a la posición actual (pos1)
  servo2.write(pos2); // Mover el servomotor a la posición actual (pos1)
  servo3.write(pos3); // Mover el servomotor a la posición actual (pos1)

  

}
