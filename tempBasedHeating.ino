//This program heats up five heating elements until temperature sensors detect that the heating elements are at temperature

// Round side up on temperature sensor; Positive is right terminal


int sensorPin1 = 0; //Thumb input                        
int sensorPin2 = 1; //Index and middle finger input
int sensorPin3 = 2; //Ring and pinky finger input
int sensorPin4 = 3; //Palm input
int sensorPin5 = 5; //Rear of hand input

int fetPin1 = 3; //Thumb output
int fetPin2 = 5; //Index and middle finger output
int fetPin3 = 6; //Ring and pinky finger output
int fetPin4 = 9; //Palm output
int fetPin5 = 10; //Rear of hand output

int idealTemp = 30; //Heating elements turn off when this temperature is reached
 

void setup(void)
{
  Serial.begin(9600);  //Start the serial connection with the computer
                       //to view the result open the serial monitor 
                       
  //set all fetPins at digital outputs
  pinMode(fetPin1, OUTPUT); 
  pinMode(fetPin2, OUTPUT);  
  pinMode(fetPin3, OUTPUT);
  pinMode(fetPin4, OUTPUT);
  pinMode(fetPin5, OUTPUT);

}
void loop(void){                     // run over and over again


  
  //getting the voltage reading from the temperature sensor
 int reading1 = analogRead(sensorPin1);  
 
 // converting that reading to voltage, for 3.3v arduino use 3.3
 float voltage1 = reading1 * 5.0;
 voltage1 /= 1024.0; 
 
 // now print out the temperature
 float temperatureC1 = (voltage1 - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
                                               //to degrees ((voltage - 500mV) times 100)
 Serial.print(temperatureC1); Serial.println(" degrees C # 1");
 
 //if the sensed temperature for thumb is less than the ideal one, turn on heating element
 if (temperatureC1 < idealTemp){
   digitalWrite(fetPin1, HIGH);
   Serial.print("Heating");
 }
 //if the sensed temperature for thumb is equal or greater than the ideal one, turn off heating element
 else if (temperatureC1 >= idealTemp){
   digitalWrite(fetPin1, LOW);
   Serial.print("At temperature");
 }
 
 delay(1000);                                     //waiting a second
 
 //getting the voltage reading from the temperature sensor
 int reading2 = analogRead(sensorPin2);  
 
 // converting that reading to voltage, for 3.3v arduino use 3.3
 float voltage2 = reading2 * 5.0;
 voltage2 /= 1024.0; 
 
 // now print out the temperature
 float temperatureC2 = (voltage2 - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
                                               //to degrees ((voltage - 500mV) times 100)
 Serial.print(temperatureC2); Serial.println(" degrees C # 2");
 
 //if the sensed temperature for index and middle fingers is less than the ideal one, turn on heating element
 if (temperatureC2 < idealTemp){
  digitalWrite(fetPin2, HIGH);
  Serial.print("Heating");
 }
 //if the sensed temperature for index and middle fingers is equal or greater than the ideal one, turn off heating element
  else if (temperatureC2 >= idealTemp){
   digitalWrite(fetPin2, LOW);
   Serial.print("At temperature");
 }
 delay(1000);                                     //waiting a second
 
 //getting the voltage reading from the temperature sensor
 int reading3 = analogRead(sensorPin3);  
 
 // converting that reading to voltage, for 3.3v arduino use 3.3
 float voltage3 = reading3 * 5.0;
 voltage3 /= 1024.0; 
 
 // now print out the temperature
 float temperatureC3 = (voltage3 - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
                                               //to degrees ((voltage - 500mV) times 100)
 Serial.print(temperatureC3); Serial.println(" degrees C # 3");
 
 //if the sensed temperature for ring and pinky fingers is less than the ideal one, turn on heating element
 if (temperatureC3 < idealTemp){ 
  digitalWrite(fetPin3, HIGH); 
  Serial.print("Heating");
 }
 //if the sensed temperature for ring and pinky fingers is equal or greater than the ideal one, turn off heating element
 else if (temperatureC3 >= idealTemp){
   digitalWrite(fetPin3, LOW);
   Serial.print("At temperature");
 } 
 delay(1000);                                     //waiting a second
 
 //getting the voltage reading from the temperature sensor
 int reading4 = analogRead(sensorPin4);  
 
 // converting that reading to voltage, for 3.3v arduino use 3.3
 float voltage4 = reading4 * 5.0;
 voltage4 /= 1024.0; 
 
 // now print out the temperature
 float temperatureC4 = (voltage4 - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
                                               //to degrees ((voltage - 500mV) times 100)
 Serial.print(temperatureC4); Serial.println(" degrees C # 4");
 
  //if the sensed temperature for the palm is less than the ideal one, turn on heating element
 if (temperatureC4 < idealTemp){
   digitalWrite(fetPin4, HIGH);
   Serial.print("Heating");
 } 
 //if the sensed temperature for the palm is equal or greater than the ideal one, turn off heating element
 else if (temperatureC4 >= idealTemp){
   digitalWrite(fetPin4, LOW);
   Serial.print("At temperature");
 } 
 delay(1000);                                     //waiting a second
 
 //getting the voltage reading from the temperature sensor
 int reading5 = analogRead(sensorPin5);  
 
 // converting that reading to voltage, for 3.3v arduino use 3.3
 float voltage5 = reading5 * 5.0;
 voltage5 /= 1024.0; 
 
 // now print out the temperature
 float temperatureC5 = (voltage5 - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
                                               //to degrees ((voltage - 500mV) times 100)
 Serial.print(temperatureC5); Serial.println(" degrees C # 5");

 //if the sensed temperature for the rear of hand is less than the ideal one, turn on heating element
 if (temperatureC5 < idealTemp){
   digitalWrite(fetPin5, HIGH);
   Serial.print("Heating");
 }
 //if the sensed temperature for the rear of hand is equal or greater than the ideal one, turn off heating element
 else if (temperatureC5 >= idealTemp){
   digitalWrite(fetPin5, LOW);
   Serial.print("At temperature");
 } 
 delay(1000);                                     //waiting a second
}
