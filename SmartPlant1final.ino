//Libraries
#include "SD.h"
#include <Wire.h>
#include "RTClib.h"

#define LOG_INTERVAL  1000 // mills between entries. 
// how many milliseconds before writing the logged data permanently to disk
// set it to the LOG_INTERVAL to write each time (safest)
// set it to 10*LOG_INTERVAL to write all data every 10 datareads, you could lose up to
// the last 10 reads if power is lost but it uses less power and is much faster!
#define SYNC_INTERVAL 1000 // mills between calls to flush() - to write data to the card
uint32_t syncTime = 0; // time of last sync()

int sensorPin = A0; 
int sensorValue;  
int limit = 300;

#define ECHO_TO_SERIAL   1 // echo data to serial port. 


//Variables
char activeMotion [] = "Active";
char inactiveMotion [] = "Inactive";
char* state ;

RTC_PCF8523 RTC; // define the Real Time Clock object

// for the data logging shield, we use digital pin 10 for the SD cs line
const int chipSelect = 10;

// the logging file
File logfile;


void setup() {
 Serial.begin(9600);
 pinMode(13, OUTPUT);

  initSDcard();

  createFile();
  initRTC();

  logfile.println("millis,stamp,datetime,motion");
#if ECHO_TO_SERIAL
  Serial.println("millis,stamp,datetime,motion");
#endif 

  pinMode(6, INPUT);
}

void loop() {

 sensorValue = analogRead(sensorPin); 
 
 Serial.println(sensorValue);
 
 if (sensorValue<limit) 
 {
 digitalWrite(13, HIGH);
  
 }
 else 
 {
 digitalWrite(13, LOW);
  
 }
 
 delay(1800);

 DateTime now;

 
  delay((LOG_INTERVAL - 1) - (millis() % LOG_INTERVAL));

 
  uint32_t m = millis();
  logfile.print(m);           
  logfile.print(", ");
#if ECHO_TO_SERIAL
  Serial.print(m);         
  Serial.print(", ");
#endif

  // fetch the time
  now = RTC.now();
  // log time
  logfile.print(now.unixtime()); // seconds since 2000
  logfile.print(", ");
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
#if ECHO_TO_SERIAL
  Serial.print(now.unixtime()); // seconds since 2000
  Serial.print(", ");
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
#endif 
  if (analogRead(6) == HIGH) {
    
    state = activeMotion;
  }
  else {
   
    state = inactiveMotion;
  }

  logfile.print(", ");
  logfile.println(state);

#if ECHO_TO_SERIAL
  Serial.print(", ");
  Serial.println(state);

#endif

  if ((millis() - syncTime) < SYNC_INTERVAL) return;
  syncTime = millis();

  logfile.flush();
}

void error(char const *str)
{
  Serial.print("error: ");
  Serial.println(str);

  while (1);
}

void initSDcard()
{
  Serial.print("Initializing SD card...");
  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(10, OUTPUT);

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");

}

void createFile()
{
  //file name must be in 8.3 format (name length at most 8 characters, follwed by a '.' and then a three character extension.
  char filename[] = "MLOG00.CSV";
  for (uint8_t i = 0; i < 100; i++) {
    filename[4] = i / 10 + '0';
    filename[5] = i % 10 + '0';
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
}

void initRTC()
{
  Wire.begin();
  if (!RTC.begin()) {
    logfile.println("RTC failed");
#if ECHO_TO_SERIAL
    Serial.println("RTC failed");
#endif  

  }

 
 
}
