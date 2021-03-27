#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

int sensorpin=A0;
int sensorvalue=0;
int outputvalue=0;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "jMrSvsQlsoBhOig2wiVKXoUe1UxMW3pS";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Dil-JD";
char pass[] = "Spl24GJD/AB";

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
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
  
  Blynk.virtualWrite(V1,outputvalue);
  Blynk.run();
}
