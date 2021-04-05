#include "ESP8266WiFi.h" 
#include "FirebaseESP8266.h" 
#include "DHT.h" 

#define FIREBASE_HOST "tma42-898f9-default-rtdb.firebaseio.com" 
#define FIREBASE_AUTH "M9XrPT5rh7YiU5PDJPTOXfPxpngbJEswOtAC6gcv" 

#define WIFI_SSID "SLT-4G-8490" 
#define WIFI_PASSWORD "1GQ7AG7B81F"
#define DHTPIN D5 
#define DHTTYPE DHT11 
DHT dht (DHTPIN, DHTTYPE);
FirebaseData firebaseData;
FirebaseData ledData;

FirebaseJson json;

void setup () {
  Serial.begin (9600);
  delay (1000);
  WiFi.begin (WIFI_SSID, WIFI_PASSWORD); 
  Serial.print ("Connecting to");
  Serial.print (WIFI_SSID);
  while (WiFi.status()!= WL_CONNECTED) {
    Serial.print (".");
    delay (500);
  }
  Serial.println ();
  Serial.print ("Connected to");
  Serial.print (" ");
  Serial.println (WIFI_SSID);
  Serial.print ("IP Address is:");
  Serial.println (WiFi.localIP ()); 
  Firebase.begin (FIREBASE_HOST, FIREBASE_AUTH); 
  dht.begin (); 
}
void loop () 
{
  float h = dht.readHumidity (); 
  float t = dht.readTemperature (); 
    
  if (isnan (h) || isnan (t)) {
    Serial.println ("Failed to read from DHT sensor!");
    return;
  }  
  Serial.print ("Humidity: "); Serial.print (h);
  String firebaseHumid = String (h) + String ("%"); 
  Serial.print ("% ; Temperature: "); Serial.print (t); Serial.println ("°C");
  String firebaseTemp = String (t) + String ("°C"); 
  delay (100);
  
  if (Firebase.setFloat(firebaseData, "/FirebaseIOT/temperature", t))
  {
    Serial.println("PASSED");
    
  }
  else
  {
    Serial.println("FAILED");
    
  }

  if (Firebase.setFloat(firebaseData, "/FirebaseIOT/humidity", h))
  {
    Serial.println("PASSED");
  }
  else
  {
    Serial.println("FAILED");
    
  } 
} 
