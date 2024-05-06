#include <Servo.h>

Servo servo1; // Declaramos un objeto Servo para el primer motor
Servo servo2; // Declaramos un objeto Servo para el segundo motor
Servo servo3; // Declaramos un objeto Servo para el tercer motor

int pos1 = 0; // Posición inicial del servomotor 1
int pos2 = 0; // Posición inicial del servomotor 2
int pos3 = 0; // Posición inicial del servomotor 3

void setup() {
  Serial.begin(9600); // Inicializa la comunicación serie con la misma velocidad que en el programa en C

  servo1.attach(9); // Conectamos el primer motor al pin 9
  servo2.attach(10); // Conectamos el segundo motor al pin 10
  servo3.attach(11); // Conectamos el tercer motor al pin 11

  servo1.write(pos1); // Mover el servomotor a la posición inicial
  servo2.write(pos2); // Mover el servomotor a la posición inicial
  servo3.write(pos3); // Mover el servomotor a la posición inicial
}

void loop() {
  if (Serial.available() > 0) {
    String word = Serial.readStringUntil('\n'); // Lee la palabra hasta que se reciba un salto de línea
    Serial.print("Palabra recibida: ");
    Serial.println(word);

    // Recorre la palabra recibida letra por letra
    for (int i = 0; i < word.length(); i++) {
      char letter = word[i]; // Obtén la letra actual
      Serial.print("Letra recibida: ");
      Serial.println(letter);

      // Ejecuta la rutina correspondiente para cada letra
      switch (letter) {
          case 'a':
              write_a();
              Serial.println("Escribiendo letra: A");
              break;
          case 'b':
              write_b();
              Serial.println("Escribiendo letra: B");
              break;
          case 'c':
              write_c();
              Serial.println("Escribiendo letra: C");
              break;
          case 'd':
              write_d();
              Serial.println("Escribiendo letra: D");
              break;
          case 'e':
              write_e();
              Serial.println("Escribiendo letra: E");
              break;
          case 'f':
              write_f();
              Serial.println("Escribiendo letra: F");
              break;
          case 'g':
              write_g();
              Serial.println("Escribiendo letra: G");
              break;
          case 'h':
              write_h();
              Serial.println("Escribiendo letra: H");
              break;
          case 'i':
              write_i();
              Serial.println("Escribiendo letra: I");
              break;
          case 'j':
              write_j();
              Serial.println("Escribiendo letra: J");
              break;
          case 'k':
              write_k();
              Serial.println("Escribiendo letra: K");
              break;
          case 'l':
              write_l();
              Serial.println("Escribiendo letra: L");
              break;
          case 'm':
              write_m();
              Serial.println("Escribiendo letra: M");
              break;
          case 'n':
              write_n();
              Serial.println("Escribiendo letra: N");
              break;
          case 'ñ':
              write_n2();
              Serial.println("Escribiendo letra: Ñ");
              break;
          case 'o':
              write_o();
              Serial.println("Escribiendo letra: O");
              break;
          case 'p':
              write_p();
              Serial.println("Escribiendo letra: P");
              break;
          case 'q':
              write_q();
              Serial.println("Escribiendo letra: Q");
              break;
          case 'r':
              write_r();
              Serial.println("Escribiendo letra: R");
              break;
          case 's':
              write_s();
              Serial.println("Escribiendo letra: S");
              break;
          case 't':
              write_t();
              Serial.println("Escribiendo letra: T");
              break;
          case 'u':
              write_u();
              Serial.println("Escribiendo letra: U");
              break;
          case 'v':
              write_v();
              Serial.println("Escribiendo letra: V");
              break;
          case 'w':
              write_w();
              Serial.println("Escribiendo letra: W");
              break;
          case 'x':
              write_x();
              Serial.println("Escribiendo letra: X");
              break;
          case 'y':
              write_y();
              Serial.println("Escribiendo letra: Y");
              break;
          case 'z':
              write_z();
              Serial.println("Escribiendo letra: Z");
              break;
      }

    }
  }
}



// ***************** RUTINAS DE ESCRITURA PARA CADA LETRA *****************



void write_a() {
    // Rutina para escribir la letra 'A'
    servo3.write(0); // Por ejemplo, mueve el tercer servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada

    servo1.write(0); // Por ejemplo, mueve el primer servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
  
    servo2.write(0); // Por ejemplo, mueve el segundo servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
  
    
}

void write_b() {
    // Rutina para escribir la letra 'B'

    servo1.write(90); // Por ejemplo, mueve el primer servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
  
    servo2.write(90); // Por ejemplo, mueve el segundo servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
  
    servo3.write(90); // Por ejemplo, mueve el tercer servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
}

void write_c() {
    // Rutina para escribir la letra 'C'

    servo1.write(90); // Por ejemplo, mueve el primer servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
  
    servo2.write(90); // Por ejemplo, mueve el segundo servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
  
    servo3.write(90); // Por ejemplo, mueve el tercer servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
}

void write_d() {
    // Rutina para escribir la letra 'D'

    servo1.write(90); // Por ejemplo, mueve el primer servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
  
    servo2.write(90); // Por ejemplo, mueve el segundo servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
  
    servo3.write(90); // Por ejemplo, mueve el tercer servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
}

void write_e() {
    // Rutina para escribir la letra 'E'

    servo1.write(90); // Por ejemplo, mueve el primer servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
  
    servo2.write(90); // Por ejemplo, mueve el segundo servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
  
    servo3.write(90); // Por ejemplo, mueve el tercer servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
}

void write_f() {
    // Rutina para escribir la letra 'F'

    servo1.write(90); // Por ejemplo, mueve el primer servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
  
    servo2.write(90); // Por ejemplo, mueve el segundo servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
  
    servo3.write(90); // Por ejemplo, mueve el tercer servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
}

void write_g() {
    // Rutina para escribir la letra 'G'

    servo1.write(90); // Por ejemplo, mueve el primer servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
  
    servo2.write(90); // Por ejemplo, mueve el segundo servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
  
    servo3.write(90); // Por ejemplo, mueve el tercer servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
}

void write_h() {
    // Rutina para escribir la letra 'H'

    servo1.write(90); // Por ejemplo, mueve el primer servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
  
    servo2.write(90); // Por ejemplo, mueve el segundo servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
  
    servo3.write(90); // Por ejemplo, mueve el tercer servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
}

void write_i() {
    // Rutina para escribir la letra 'I'

    servo1.write(90); // Por ejemplo, mueve el primer servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
  
    servo2.write(90); // Por ejemplo, mueve el segundo servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
  
    servo3.write(90); // Por ejemplo, mueve el tercer servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
}

void write_j() {
    // Rutina para escribir la letra 'J'

    servo1.write(90); // Por ejemplo, mueve el primer servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
  
    servo2.write(90); // Por ejemplo, mueve el segundo servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
  
    servo3.write(90); // Por ejemplo, mueve el tercer servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
}

void write_k() {
    // Rutina para escribir la letra 'K'
    servo2.write(90); // Por ejemplo, mueve el segundo servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada

    servo1.write(90); // Por ejemplo, mueve el primer servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
  
    servo3.write(90); // Por ejemplo, mueve el tercer servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
}

void write_l() {
    // Rutina para escribir la letra 'L'

    servo1.write(90); // Por ejemplo, mueve el primer servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
  
    servo2.write(90); // Por ejemplo, mueve el segundo servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
  
    servo3.write(90); // Por ejemplo, mueve el tercer servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
}

void write_m() {
    // Rutina para escribir la letra 'M'


    servo2.write(90); // Por ejemplo, mueve el segundo servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada

    servo3.write(90); // Por ejemplo, mueve el tercer servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada

    servo1.write(90); // Por ejemplo, mueve el primer servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
  
    
}

void write_n() {
    // Rutina para escribir la letra 'N'

    servo1.write(90); // Por ejemplo, mueve el primer servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
  
    servo2.write(90); // Por ejemplo, mueve el segundo servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
  
    servo3.write(90); // Por ejemplo, mueve el tercer servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
}

void write_n2() {
    // Rutina para escribir la letra 'Ñ'

    servo1.write(90); // Por ejemplo, mueve el primer servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
  
    servo2.write(90); // Por ejemplo, mueve el segundo servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
  
    servo3.write(90); // Por ejemplo, mueve el tercer servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
}

void write_o() {
    // Rutina para escribir la letra 'O'

    servo1.write(90); // Por ejemplo, mueve el primer servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
  
    servo2.write(90); // Por ejemplo, mueve el segundo servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
  
    servo3.write(90); // Por ejemplo, mueve el tercer servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
}

void write_p() {
    // Rutina para escribir la letra 'P'

    servo1.write(90); // Por ejemplo, mueve el primer servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
  
    servo2.write(90); // Por ejemplo, mueve el segundo servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
  
    servo3.write(90); // Por ejemplo, mueve el tercer servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
}

void write_q() {
    // Rutina para escribir la letra 'Q'

    servo1.write(90); // Por ejemplo, mueve el primer servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
  
    servo2.write(90); // Por ejemplo, mueve el segundo servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
  
    servo3.write(90); // Por ejemplo, mueve el tercer servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
}

void write_r() {
    // Rutina para escribir la letra 'R'

    servo1.write(90); // Por ejemplo, mueve el primer servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
  
    servo2.write(90); // Por ejemplo, mueve el segundo servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
  
    servo3.write(90); // Por ejemplo, mueve el tercer servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
}

void write_s() {
    // Rutina para escribir la letra 'S'

    servo1.write(90); // Por ejemplo, mueve el primer servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
  
    servo2.write(90); // Por ejemplo, mueve el segundo servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
  
    servo3.write(90); // Por ejemplo, mueve el tercer servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
}

void write_t() {
    // Rutina para escribir la letra 'T'

    servo1.write(90); // Por ejemplo, mueve el primer servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
  
    servo2.write(90); // Por ejemplo, mueve el segundo servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
  
    servo3.write(90); // Por ejemplo, mueve el tercer servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
}

void write_u() {
    // Rutina para escribir la letra 'U'

    servo1.write(90); // Por ejemplo, mueve el primer servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
  
    servo2.write(90); // Por ejemplo, mueve el segundo servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
  
    servo3.write(90); // Por ejemplo, mueve el tercer servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
}

void write_v() {
    // Rutina para escribir la letra 'V'

    servo1.write(90); // Por ejemplo, mueve el primer servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
  
    servo2.write(90); // Por ejemplo, mueve el segundo servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
  
    servo3.write(90); // Por ejemplo, mueve el tercer servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
}

void write_w() {
    // Rutina para escribir la letra 'W'

    servo1.write(90); // Por ejemplo, mueve el primer servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
  
    servo2.write(90); // Por ejemplo, mueve el segundo servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
  
    servo3.write(90); // Por ejemplo, mueve el tercer servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
}

void write_x() {
    // Rutina para escribir la letra 'X'

    servo1.write(90); // Por ejemplo, mueve el primer servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
  
    servo2.write(90); // Por ejemplo, mueve el segundo servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
  
    servo3.write(90); // Por ejemplo, mueve el tercer servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
}

void write_y() {
    // Rutina para escribir la letra 'Y'

    servo1.write(90); // Por ejemplo, mueve el primer servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
  
    servo2.write(90); // Por ejemplo, mueve el segundo servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
  
    servo3.write(90); // Por ejemplo, mueve el tercer servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
}

void write_z() {
    // Rutina para escribir la letra 'Z'

    servo1.write(90); // Por ejemplo, mueve el primer servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
  
    servo2.write(90); // Por ejemplo, mueve el segundo servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
  
    servo3.write(90); // Por ejemplo, mueve el tercer servomotor a 90 grados
    delay(500); // Espera un tiempo para que el servomotor llegue a la posición deseada
}


