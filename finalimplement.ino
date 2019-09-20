
int mid_sensor;
int side_sensors;

void setup() {
  // put your setup code here, to run once:

pinMode(mid_sensor, INPUT);
pinMode(side_sensors, INPUT);
pinMode(LED_BUILTIN, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  if((digitalRead(mid_sensor) == HIGH) || digitalRead(side_sensors) == HIGH);
  {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(10000);
    digitalWrite(LED_BUILTIN, LOW);
    
  }

  else
  {
    delay(5000);
  }

}
