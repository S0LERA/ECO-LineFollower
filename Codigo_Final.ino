#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  180 // (180) this is the 'minimum' pulse length count (out of 4096)
#define SERVOSTOP 340 // pulse length to stop de servo
#define SERVOMAX  500 // (500) this is the 'maximum' pulse length count (out of 4096)

/***   Global variables   ***/
//Declaramos todas las variables globales necesarias
int servo_derecho=0;
int servo_izquierdo=1;
int NEGRO=0;
int zumbador=10;
const int tonos[] = {261,494};

/***   Function declaration   ***/
void setup(){
  //Declaramos los pines que nos van a hacer falta para la entrada de los servos y la variable ultim para ver por que lado se ha salido el robot
  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
  pinMode( 2 , INPUT);
  pinMode( 3 , INPUT);
  pinMode( 10, OUTPUT);
}
void loop(){
  int ir_derecho=digitalRead(2);
  int ir_izquierdo=digitalRead(3);
  int ultim;
   //Este if es para que el robot vaya recto al detectar los dos sensores negro
 if (ir_derecho == NEGRO && ir_izquierdo ==NEGRO) {
    pwm.setPWM(servo_izquierdo, 0, SERVOMIN);
    pwm.setPWM(servo_derecho, 0, SERVOMAX);
   }
// Este elseif es para cuando el sensor izquierdo deje de detectar negro, aqui cambiamos ultim que la usaremos más tarde
// La función tone es para que el robot pite cuando el sensor izquierdo no detecta negro
  else if (ir_derecho == NEGRO && ir_izquierdo != NEGRO){
    pwm.setPWM(servo_izquierdo, 0, SERVOMIN);
    pwm.setPWM(servo_derecho, 0, SERVOSTOP);
    tone(zumbador, tonos[0]);
    ultim=1;
  }
// Este elseif es para cuando el sensor derecho deje de detectar negro y también cambiamos ultim para usarla más tarde
// La función tone es para que el robot pite cuando el sensor derecho no detecta negro
  else if (ir_derecho != NEGRO && ir_izquierdo== NEGRO){
    pwm.setPWM(servo_izquierdo, 0, SERVOSTOP);
    pwm.setPWM(servo_derecho, 0, SERVOMAX);
    tone(zumbador, tonos[1]);
    ultim=2;
  }
// Este elseif es para que el robot recuerde que se ha salido por la izquierda y vuelva a la línea usando la variable ultim
// La función tone es para que el robot pite cuando el sensor izquierdo no detecta negro
  else if (ir_derecho != NEGRO && ir_izquierdo != NEGRO && ultim==1){
    pwm.setPWM(servo_izquierdo, 0, SERVOMIN);
    pwm.setPWM(servo_derecho, 0, SERVOSTOP);
    tone(zumbador, tonos[1]);
    ultim=2;
  }
// Este elseif es para que el robot recuerde que se ha salido por la derecha y vuelva a la línea usando la variable ultim
// La función tone es para que el robot pite cuando el sensor derecho no detecta negro
  else if (ir_derecho != NEGRO && ir_izquierdo != NEGRO && ultim==2){
    pwm.setPWM(servo_izquierdo, 0, SERVOSTOP);
    pwm.setPWM(servo_derecho, 0, SERVOMAX);
    tone(zumbador, tonos[0]);
  ultim=1;
  }
}

