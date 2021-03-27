#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>

Servo servo;

char auth[] = "h5PLxF_fX2SFjtgrepbRbYHGLvz2ImeZ"; //  your auth code 
char ssid[] = "Dil-JD";
char pass[] = "Spl24GJD/AB"; 

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);

  servo.attach(2); // NodeMCU D4 pin
  
 }
  
void loop()
{
  
  Blynk.run();
  
}
BLYNK_WRITE(V1)
{
   servo.write(param.asInt());
}
