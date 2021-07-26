/***
 * Created by Charles Soarez
 * Date: 07-25-2021 
*/

const float OPT_TEMP = 35.0;
const float OPT_HUM = 500.0;
const float OPT_DIST = 40.0;

#define PIN_HUM 12 //	In the real project, It is used for DTH11.
#define PIN_ECHO 11
#define PIN_TRIGGER 10
#define PIN_BUTTON 9

void setup(){
	Serial.begin(9600);	
  	pinMode(2, OUTPUT);
  	pinMode(PIN_ECHO, INPUT);
  	pinMode(PIN_TRIGGER, OUTPUT);
  	pinMode(PIN_BUTTON, INPUT);	
}

void loop(){
	bool 
      	optimalHumidity = false, 
		optimalTemperature = false,
  		optimalDistance = false, 
  		selectToCut = false;
     
  if(getTemperature() > OPT_TEMP){
   	optimalTemperature = true; 
    Serial.println("Optimal temperature: " + (String)(getTemperature()));
  }else
  	Serial.println();
    
  if(getHumidity() > OPT_HUM){
  	optimalHumidity = true;
    Serial.println("Optimal humidity: " + (String)(getHumidity()));
  }
  
  if(getDistance() > OPT_DIST){
  	optimalDistance = true;
    Serial.println("Distance: " + (String)(getDistance()) + " cm");
  }
  
  if(isButtonPressed()){
  	selectToCut = true;
    Serial.println("The user wants to harvest: " + (String)(isButtonPressed()));
  }
    
  if(optimalHumidity && optimalTemperature && optimalDistance && selectToCut){
  	
  }
  delay(200);
}

/**
 * Function that calculates the actual sensed temperature by the TMP36 sensor
 * @return temperature
 */
float getTemperature(){
	unsigned int StValue = analogRead(A0);
	float temperature = 0.0;
  
	float voltage = (StValue * 5000.0) / 1023.0;
  
  	if (voltage > 500.0){
   		temperature = (voltage - 500.0) / 10.0;
	}
	
  return temperature;
}

/**
 * Function that simulates a humidity sensor, probably a DHT11 sensor
 *@return humidity porcentage
*/
float getHumidity(){
	unsigned int humidity = analogRead(A1);
  	  
  	delay(500);
 
  	Serial.println(humidity);
	
  	return humidity;
}

/**
 * Function that returns the distance in centimeters using the ping sensor HC-SR04
 *@return distance
*/
float getDistance(){
  	delay(400);
	long duration = 0.0, distance = 0.0;
  
  	digitalWrite(PIN_TRIGGER, LOW);
  	delayMicroseconds(2);
  	digitalWrite(PIN_TRIGGER, HIGH);
  	delayMicroseconds(10);
  	digitalWrite(PIN_TRIGGER, LOW);
  
  	duration = pulseIn(PIN_ECHO, HIGH); //Don not recognise this function
  	distance = (duration / 2) / 29;
  
  	if (distance >= 500 || distance <= 0)
  		Serial.println("--");
  
	return distance;
}

/*
 *Function that detects if the user wants to harvest the plant
 *@return true or false
 */
bool isButtonPressed(){
	if(digitalRead(PIN_BUTTON))
      return true;
     else
      return false;
}
