#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include <Servo.h>
int sensorpin=A0;
int sensorvalue=0;
int outputvalue=0;
Servo servo;

char auth[] = "tYfWZFANJ5wQEcd2ZG35YB6BWiGBPrXa";
 
char ssid[] = "SLT-4G_RVA";
char pass[] = "rv724@SLT";
#define DHTPIN 0          // D3
 

#define DHTTYPE DHT11     // DHT 11

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
 
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, t);
  Blynk.virtualWrite(V6, h);
}

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  dht.begin();
  servo.attach(2); // NodeMCU D4 pin
 
 
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  sensorvalue=analogRead(sensorpin);
  outputvalue=map(sensorvalue,0,1023,0,100); //100,0 pottupaaru
  delay(1000);

  if(outputvalue>74)
  {
       Serial.println("water your plant");
       Serial.print(outputvalue);
       Blynk.notify("water your plant");
       delay(1000); 
  }
  else if(outputvalue<45)
  {
       Serial.println("soil is wet enough to water");
       Serial.print(outputvalue);
       Blynk.notify("soil is wet enough to water");
       delay(1000);
  }
  
  Blynk.virtualWrite(V0,outputvalue);
  Blynk.run();
  timer.run();
}
BLYNK_WRITE(V1)
{
   servo.write(param.asInt());
}
