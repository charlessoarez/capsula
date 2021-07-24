/***
*@autor: Charles Soarez
*Date: 07-24-2021
*/
void setup()
{
  Serial.begin(9600);
  /**
  * Se declara un array de pines
  * Se declara la variable i para iterar
  */
  int pinArray[] = {12, 11, 10, 9, 7, 6, 5};
  int i;
  
  /**
  * Se configuran los pines de salida
  * Del pin 12 al 9 como entradas lógicas
  */
  for(i = 0; i <= 3; ++i)
    pinMode(pinArray[i], INPUT);

  /**
  * Se configuran los pines de salida
  * Del pin 7 al 5 como salidas lógicas
  */
  for(i = 3; i <= 7; ++i)
    pinMode(pinArray[i], OUTPUT);

}

void loop()
{
  //Se declaran variables booleanas para establecer estados
  bool 
  	sensorHumedad = false, 
  	sensorTemperatura = false, 
  	sensorBarrera = false,
    sensorCorte = false;
  
  /***
  * Si el Pin 12 recibe una señal se pone en HIGH o en 1 el pin 7
  * Se enciende el LED rojo para mostrar visualmente que
  * la humedad es óptima.
  * Si no se cumple la condición se pone en 0 o en LOW
  */
  if(digitalRead(12)){ //
  	digitalWrite(7, HIGH);
    sensorHumedad = true;
  }else
    digitalWrite(7, LOW); 

  /***
  * Si el Pin 11 recibe una señal se pone en HIGH o en 1 el pin 6
  * Se enciende el LED verde para mostrar visualmente que
  * la temperatura es óptima.
  * Si no se cumple la condición se pone en 0 o en LOW
  */
  if(digitalRead(11)){
    digitalWrite(6, HIGH);
    sensorTemperatura = true;
  }else
    digitalWrite(6, LOW);
  
  /***
  * Si el Pin 10 recibe una señal se pone en HIGH o en 1 el pin 5
  * Se enciende el LED azul para mostrar visualmente que
  * la altura es óptima.
  * Si no se cumple la condición se pone en 0 o en LOW
  */
  if(digitalRead(10)){
    digitalWrite(5, HIGH);
    sensorBarrera = true;
  }else
    digitalWrite(5, LOW);
  
  // Si el Pin 9 recibe una señal se pone la variable sensorCorte a true.
  if (digitalRead(9))sensorCorte = true;
    
  if(sensorHumedad == true && sensorTemperatura == true && 
     sensorBarrera == true && sensorCorte == true){
    digitalWrite(4, HIGH);
    Serial.println("Se cosecha");
    delay(200);
  }else{
    digitalWrite(4, LOW);
  }
}
