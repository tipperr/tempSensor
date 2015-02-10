#include <SD.h>
#include <Wire.h>
#include "RTClib.h"

// A simple data logger for the Arduino analog pins

// how many milliseconds between grabbing data and logging it. 1000 ms is once a second
#define LOG_INTERVAL  1000 // mills between entries (reduce to take more/faster data)

// how many milliseconds before writing the logged data permanently to disk
// set it to the LOG_INTERVAL to write each time (safest)
// set it to 10*LOG_INTERVAL to write all data every 10 datareads, you could lose up to 
// the last 10 reads if power is lost but it uses less power and is much faster!
#define SYNC_INTERVAL 1000 // mills between calls to flush() - to write data to the card
uint32_t syncTime = 0; // time of last sync()

#define ECHO_TO_SERIAL   1 // echo data to serial port
#define WAIT_TO_START    0 // Wait for serial input in setup()

// the digital pins that connect to the LEDs
#define redLEDpin 2
#define greenLEDpin 3

// The analog pins that connect to the sensors
int sensorPin1 = 0; //the analog pin the TMP36's Vout (sense) pin is connected to
                        //the resolution is 10 mV / degree centigrade with a
                        //500 mV offset to allow for negative temperatures
                        
int sensorPin2 = 1;
int sensorPin3 = 2;
int sensorPin4 = 3;
int sensorPin5 = 5;

RTC_DS1307 RTC; // define the Real Time Clock object

// for the data logging shield, we use digital pin 10 for the SD cs line
const int chipSelect = 10;

// the logging file
File logfile;

void error(char *str)
{
  Serial.print("error: ");
  Serial.println(str);
  
  // red LED indicates error
  digitalWrite(redLEDpin, HIGH);

  while(1);
}

void setup(void)
{
  Serial.begin(9600);
  Serial.println();
  
  // use debugging LEDs
  pinMode(redLEDpin, OUTPUT);
  pinMode(greenLEDpin, OUTPUT);
  
#if WAIT_TO_START
  Serial.println("Type any character to start");
  while (!Serial.available());
#endif //WAIT_TO_START

  // initialize the SD card
  Serial.print("Initializing SD card...");
  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(10, OUTPUT);
  digitalWrite(10,HIGH);
  
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    error("Card failed, or not present");
    pinMode(redLEDpin, OUTPUT);
  }
  Serial.println("card initialized.");
  
  // create a new file
  char filename[] = "LOGGER00.CSV";
  for (uint8_t i = 0; i < 100; i++) {
    filename[6] = i/10 + '0';
    filename[7] = i%10 + '0';
    if (! SD.exists(filename)) {
      // only open a new file if it doesn't exist
      logfile = SD.open(filename, FILE_WRITE); 
      break;  // leave the loop!
    }
  }
  
  if (! logfile) {
    error("couldnt create file");
  }
  
  Serial.print("Logging to: ");
  Serial.println(filename);

  // connect to RTC
  Wire.begin();  
  if (!RTC.begin()) {
    logfile.println("RTC failed");
#if ECHO_TO_SERIAL
    Serial.println("RTC failed");
#endif  //ECHO_TO_SERIAL
  }
  

  logfile.println("stamp,datetime,middletemp,pinkietemp,palmtemp,thumbtemp,whitepointertemp");    
#if ECHO_TO_SERIAL
  Serial.println("stamp,datetime,middletemp,pinkietemp,palmtemp,thumbtemp,whitepointertemp");
#endif //ECHO_TO_SERIAL
 
  // If you want to set the aref to something other than 5v
 // analogReference(EXTERNAL);
}

void loop(void)
{
  DateTime now;

  // delay for the amount of time we want between readings
  delay((LOG_INTERVAL -1) - (millis() % LOG_INTERVAL));
  
  digitalWrite(greenLEDpin, HIGH);
  
  // log milliseconds since starting
  uint32_t m = millis();
  //logfile.println(m);           // milliseconds since start
  //logfile.print(", ");    
#if ECHO_TO_SERIAL
  //Serial.println(m);         // milliseconds since start
  //Serial.print(", ");  
#endif

  // fetch the time
  now = RTC.now();
  // log time
  logfile.println(now.unixtime()); // seconds since 1/1/1970
  logfile.print(", ");
  logfile.print('"');
  logfile.print(now.year(), DEC);
  logfile.print("/");
  logfile.print(now.month(), DEC);
  logfile.print("/");
  logfile.print(now.day(), DEC);
  logfile.print(" ");
  logfile.print(now.hour(), DEC);
  logfile.print(":");
  logfile.print(now.minute(), DEC);
  logfile.print(":");
  logfile.print(now.second(), DEC);
  logfile.print('"');
#if ECHO_TO_SERIAL
  Serial.println(now.unixtime()); // seconds since 1/1/1970
  Serial.print(", ");
  Serial.print('"');
  Serial.print(now.year(), DEC);
  Serial.print("/");
  Serial.print(now.month(), DEC);
  Serial.print("/");
  Serial.print(now.day(), DEC);
  Serial.print(" ");
  Serial.print(now.hour(), DEC);
  Serial.print(":");
  Serial.print(now.minute(), DEC);
  Serial.print(":");
  Serial.print(now.second(), DEC);
  Serial.print('"');
#endif //ECHO_TO_SERIAL
  
  /*analogRead(sensorPin1); 
  delay(10);
  analogRead(sensorPin2); 
  delay(10);
  analogRead(sensorPin2); 
  delay(10);
  analogRead(sensorPin2); 
  delay(10);
  analogRead(sensorPin2); 
  delay(10); */   
  // converting that reading to voltage, for 3.3v arduino use 3.3, for 5.0, use 5.0
  int tempReading1 = analogRead(sensorPin1);
  float voltage1 = tempReading1 * 5.0;
  voltage1 /= 1024;  
  float temperatureC1 = (voltage1 - 0.5) * 100 ;
  delay(500);
  int tempReading2 = analogRead(sensorPin2);
  float voltage2 = tempReading2 * 5.0;
  voltage2 /= 1024;  
  float temperatureC2 = (voltage2 - 0.5) * 100 ;
  delay(500);
  int tempReading3 = analogRead(sensorPin3);
  float voltage3 = tempReading3 * 5.0;
  voltage3 /= 1024;  
  float temperatureC3 = (voltage3 - 0.5) * 100 ;
  delay(500);
  int tempReading4 = analogRead(sensorPin4);
  float voltage4 = tempReading4 * 5.0;
  voltage4 /= 1024;  
  float temperatureC4 = (voltage4 - 0.5) * 100 ;
  delay(500);
  int tempReading5 = analogRead(sensorPin5);
  float voltage5 = tempReading5 * 5.0;
  voltage5 /= 1024;  
  float temperatureC5 = (voltage1 - 0.5) * 100 ;
  delay(500);
  
  logfile.print(", ");    
  logfile.print(temperatureC1);
  logfile.print(", ");    
  logfile.print(temperatureC2);
  logfile.print(", ");    
  logfile.print(temperatureC3);
  logfile.print(", ");    
  logfile.print(temperatureC4);
  logfile.print(", ");    
  logfile.print(temperatureC5);
#if ECHO_TO_SERIAL
  Serial.print(", ");    
  Serial.print(temperatureC1);
  Serial.print(", ");    
  Serial.print(temperatureC2);
  Serial.print(", ");    
  Serial.print(temperatureC3);
  Serial.print(", ");    
  Serial.print(temperatureC4);
  Serial.print(", ");    
  Serial.print(temperatureC5);
#endif //ECHO_TO_SERIAL


  digitalWrite(greenLEDpin, LOW);

  // Now we write data to disk! Don't sync too often - requires 2048 bytes of I/O to SD card
  // which uses a bunch of power and takes time
  if ((millis() - syncTime) < SYNC_INTERVAL) return;
  syncTime = millis();
  
  // blink LED to show we are syncing data to the card & updating FAT!
  digitalWrite(redLEDpin, HIGH);
  logfile.flush();
  digitalWrite(redLEDpin, LOW);
  
}


