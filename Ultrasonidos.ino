/***   Global variables   ***/
//Declaramos las variables globales necesarias
long tiempo;
int salida = 4;   // triger
int entrada = 5;      // echo
float distancia;

void setup(){
  //Declaramos los pines de entrada y salida de los ultrasonidos
  pinMode(salida, OUTPUT);
  pinMode(entrada, INPUT);
  
  Serial.begin(9600);
}
void loop(){
  digitalWrite(salida, HIGH); // Lanzamos un pequeño pulso para activar el sensor
  delayMicroseconds(10);
  digitalWrite(salida, LOW); //Desactivamos el pulso 
  
  // Medimos el pulso de respuesta
  tiempo = (pulseIn(entrada, HIGH)/2); //Recogemos el pulso antes enviado y lo dividimos por 2 
                                        //para calcular el tiempo que tarda el pulso en ir y volver
                                    
  // Ahora calcularemos la distancia en cm
  // Sabiendo que el espacio es igual a la velocidad por el tiempo y que la velocidad del sonido es de 343m/s 
  // y que el tiempo lo tenemos en millonesimas de segundo
  distancia = float(tiempo * 0.0343);
    Serial.println(distancia); //Mostramos los datos del sensor de ultrasonidos en el monitor
  delay(1000);
}
