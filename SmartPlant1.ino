

int sensorPin = A0; 
int sensorValue;  
int limit = 300; 

void setup() {
 Serial.begin(9600);
 pinMode(13, OUTPUT);
}

void loop() {

 sensorValue = analogRead(sensorPin); 
 Serial.println("Analog Value : ");
 Serial.println(sensorValue);
 
 if (sensorValue<limit) 
 {
 digitalWrite(13, HIGH);
 Serial.println("LED ON"); 
 }
 else 
 {
 digitalWrite(13, LOW);
 Serial.println("LED OFF");  
 }
 
 delay(1000); 
 
}
