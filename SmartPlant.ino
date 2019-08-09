  /*
  # Editor     : Lauren
  # Date       : 13.01.2012
  # Version    : 1.0
  # Connect the sensor to the A0(Analog 0) pin on the Arduino board
  # the sensor value description
  # 0  ~300     dry soil
  # 300~700     humid soil
  # 700~950     in water
  */
const int ledPin = LED_BUILTIN;
int ledState = LOW;
int sensorValue;

int  limit = 300;

 
void setup() 
{
  pinMode (ledPin, OUTPUT);   //setup the digital pin as output

  Serial.begin(9600); // open serial port, set the baud rate as 9600 bps
}
void loop() 
{
  
  sensorValue = analogRead(0); //connect sensor to Analog 0
  Serial.println(sensorValue); //print the value to serial port
  
  if (sensorValue<limit)
  {
    ledState == HIGH;
    
  }
  else 
  {
    ledState == LOW;
   
  }

  digitalWrite(ledPin, ledState);
  

}
