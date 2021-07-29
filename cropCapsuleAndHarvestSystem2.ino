/***
 * Created by Charles Soarez
 * Date: 07-25-2021 
*/
#include <Servo.h>
#include <LiquidCrystal.h>

const float OPT_TEMP = 35.0;
const float OPT_HUM = 50.0;
const float OPT_DIST = 40.0;

#define PIN_TRIGGER 13
#define PIN_ECHO 12
#define PIN_BUTTON 11
#define PIN_RED_LED 10
#define PIN_GREEN_LED 9
#define PIN_BLUE_LED 8
#define PIN_WHITE_LED 7
#define PIN_TEMP A0
#define PIN_HUM A1
#define PIN_SERVO 2
#define MIN_PULSE 1000
#define MAX_PULSE 2000

//Create a LiquidCrystal object
LiquidCrystal lcd(1, 0, 6, 5, 4, 3);

void setup(){
  	pinMode(PIN_ECHO, INPUT);
  	pinMode(PIN_TRIGGER, OUTPUT);
  	pinMode(PIN_BUTTON, INPUT);	
  	pinMode(PIN_RED_LED, OUTPUT);
  	pinMode(PIN_GREEN_LED, OUTPUT);
  	pinMode(PIN_BLUE_LED, OUTPUT);
  	pinMode(PIN_WHITE_LED, OUTPUT);
  	pinMode(PIN_TEMP, INPUT);
}

void loop(){
	bool 
      	optimalHumidity = false, 
		optimalTemperature = false,
  		optimalDistance = false, 
  		selectToCut = false;

  if(getHumidity() > OPT_HUM){
  	digitalWrite(PIN_RED_LED, HIGH);
    optimalHumidity = true;
    printToLcd("Optimal humidity: " + (String)(getHumidity()/100) );
   	Serial.println("Optimal humidity: " + (String)(getHumidity()/100));
  }else{
    digitalWrite(PIN_RED_LED, LOW);
    printToLcd("Not an oprimtal humidity: " + (String)(getHumidity()/100) );
    Serial.println("Not an oprimtal humidity: " + (String)(getHumidity()));
  }
    
  if(getTemperature() > OPT_TEMP){
   	optimalTemperature = true; 
    digitalWrite(PIN_GREEN_LED, HIGH);
    printToLcd("Optimal temperature: " + (String)(getTemperature()));
    Serial.println("Optimal temperature: " + (String)(getTemperature()));
  }else{
    digitalWrite(PIN_GREEN_LED, LOW);
    printToLcd("Not optimal temperature: " + (String)(getTemperature()));
  	Serial.println("Not an oprimtal temperature: " + (String)(getTemperature()));
  }
    
  if(getDistance() > OPT_DIST){
  	optimalDistance = true;
    digitalWrite(PIN_BLUE_LED, HIGH);
    Serial.println("Optimal distance: " + (String)(getDistance()) + " cm");
  }else{
  	digitalWrite(PIN_BLUE_LED, LOW);
    Serial.println("Not optimal Distance: " + (String)(getDistance()) + " cm");
  }
  
  if(isButtonPressed()){
  	selectToCut = true;
    Serial.println("The user pressed the harvest button: " + (String)(isButtonPressed()));
  }else{
  	selectToCut = false;
        digitalWrite(PIN_WHITE_LED, LOW);
  }
    
  if(optimalHumidity && optimalTemperature && optimalDistance && selectToCut){
  	printToLcd("It is harvest time!");
    digitalWrite(PIN_WHITE_LED, HIGH);
    //Here we call the servo to move the ramp
    elevateServoRamp(1);
    //Then we wait a litle and close put se servo in the normal state
    delay(1000);
    elevateServoRamp(0);
  }
}

/**
 * Function that simulates a humidity sensor, probably a DHT11 sensor
 *@return humidity porcentage
*/
float getHumidity(){
	unsigned int humidity = analogRead(PIN_HUM);
  	  
  	delay(500);
 
  	Serial.println(humidity);
	
  	return humidity/10;
}

/**
 * Function that calculates the actual sensed temperature by the TMP36 sensor
 * @return temperature
 */
float getTemperature(){
	unsigned int StValue = analogRead(PIN_TEMP);
  	
	float temperature = 0.0;
  
	float voltage = (StValue * 5000.0) / 1023.0;
  
  	if (voltage > 500.0){
   		temperature = (voltage - 500.0) / 10.0;
	}
	
  return temperature;
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
  	distance = (duration / 2.0) / 29.0;
  
  	Serial.println("distancia: " + (String)(distance));
  	if (distance >= 500.0 || distance <= 0.0)
  		Serial.println("--");
      else
      	Serial.println("distancia: " + (String)(distance));
  
	return distance;
}

/*
 * Function that detects if the user wants to harvest the plant
 *@return true or false
 */
bool isButtonPressed(){
  bool state = digitalRead(PIN_BUTTON);
  
	if(state == 1)
      return true;
     else
      return false;
}

/**
 * Method that prints messages in the LCD 
 */
void printToLcd(String message){ 
	lcd.begin(16, 2);
 	lcd.clear();
  	lcd.print(message);
  	for(int i = 0; i < message.length(); ++i){
  		lcd.scrollDisplayLeft();
      	delay(200);
  	}
	
  	delay(2000);
}

/**
* Funcrion that moves the servo motor from 0° to 180° end vice versa
*/
void elevateServoRamp(int option){
  Servo servo;
  
  servo.attach(PIN_SERVO, MIN_PULSE, MAX_PULSE);
  
  if(option == 1){
    servo.write(180);
  	delay(5000);
  	servo.write(0);
  }
}
