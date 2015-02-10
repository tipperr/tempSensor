//Time between sensor checks
long interval = 1000;
  
// This class takes in an Analog Sensor pin, takes a reading from it, converts the reading to a temperature and prints it
class Check{
  
  // Number of the analog sensor to read
  int sensorPin;
  // number of milliseconds since last sensor reading
  unsigned long previousMillis;

  
  public:
  Check(int pin){
    
    sensorPin = pin;
    pinMode(sensorPin, INPUT);
    previousMillis = 0;
  }
  

  void Update(){
    
    unsigned long currentMillis = millis();
    
    if(currentMillis - previousMillis > interval){
      previousMillis = currentMillis;
      int reading = analogRead(sensorPin);
      float voltage = reading * 5.0;
      voltage /= 1024.0;
      float temperatureC = (voltage - 0.5) * 100;
      Serial.print(temperatureC); Serial.println(" degrees C; "); Serial.println(sensorPin);
    
    }}};
    
Check sensor1(0);
Check sensor2(1);
Check sensor3(2);
Check sensor4(3);
Check sensor5(4);


void setup(){
  Serial.begin(9600);
}

void loop(){
  sensor1.Update();
  sensor2.Update();
  sensor3.Update();
  sensor4.Update();
  sensor5.Update();
}
