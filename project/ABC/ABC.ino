 
 
//Prateek
//www.prateeks.in

#define BLYNK_PRINT Serial            
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <ESP8266mDNS.h>  
#include <WiFiUdp.h>
#include <ArduinoOTA.h>  


BlynkTimer timer;

void checkPhysicalButton();

int relay1State = LOW;
int pushButton1State = HIGH;

#define RightMotorSpeed       D5   //14 
#define RightMotorDir         D6   //12 
#define LeftMotorSpeed        D7   //13 
#define LeftMotorDir          D8   //15 

#define AUTH "htRQBvanaavmF-d4ovJ0iqrBhgr3YqhG"
#define WIFI_SSID "SLT-4G_RVA"                  
#define WIFI_PASS "rv724@SLT"            

#define SERVER "blynk-cloud.com "           
#define PORT 8442

#define RELAY_PIN_1      D4


#define PUSH_BUTTON_1    D6


#define VPIN_BUTTON_1    V12 


#define OTA_HOSTNAME "Home_Automation"

int minRange = 312;
int maxRange = 712;

int minspeed = 450;
int maxspeed = 1020;
int nospeed = 0;


void moveControl(int x, int y)
{
//Move Forward
    if(y >= maxRange && x >= minRange && x<= maxRange)
    {
        digitalWrite( RightMotorDir,HIGH);
        digitalWrite(LeftMotorDir,HIGH);
        analogWrite(RightMotorSpeed, maxspeed);
        analogWrite(LeftMotorSpeed , maxspeed);
    }


//Move Forward Right
    else if(x >= maxRange && y >= maxRange)
    {
        digitalWrite( RightMotorDir, HIGH);
        digitalWrite(LeftMotorDir,HIGH);
        analogWrite(RightMotorSpeed,minspeed);
        analogWrite(LeftMotorSpeed ,maxspeed);
    }

//Move Forward Left
    else if(x <= minRange && y >= maxRange)
    {
        digitalWrite( RightMotorDir,HIGH);
        digitalWrite(LeftMotorDir,HIGH);
        analogWrite(RightMotorSpeed,maxspeed);
        analogWrite(LeftMotorSpeed ,minspeed);
    }

//No Move
    else if(y < maxRange && y > minRange && x < maxRange && x > minRange)
    {
        analogWrite(RightMotorSpeed,nospeed);
        analogWrite(LeftMotorSpeed , nospeed);
    }

//Move Backward
    else if(y <= minRange && x >= minRange && x <= maxRange)
    {
        digitalWrite( RightMotorDir,LOW);
        digitalWrite(LeftMotorDir,LOW);
        analogWrite(RightMotorSpeed,maxspeed);
        analogWrite(LeftMotorSpeed ,maxspeed);
    }

//Move Backward Right
    else if(y <= minRange && x <= minRange)
    {
        digitalWrite( RightMotorDir,LOW);
        digitalWrite(LeftMotorDir,LOW);
        analogWrite(RightMotorSpeed,minspeed);
        analogWrite(LeftMotorSpeed ,maxspeed);
    }

//Move Backward Left
    else if(y <= minRange && x >= maxRange)
    {
        digitalWrite( RightMotorDir,LOW);
        digitalWrite(LeftMotorDir,LOW);
        analogWrite(RightMotorSpeed,maxspeed);
        analogWrite(LeftMotorSpeed ,minspeed);
    }
}


BLYNK_CONNECTED() {

  // Request the latest state from the server

  Blynk.syncVirtual(VPIN_BUTTON_1);



}

// When App button is pushed - switch the state

BLYNK_WRITE(VPIN_BUTTON_1) {
  relay1State = param.asInt();
  digitalWrite(RELAY_PIN_1, relay1State);
}

void checkPhysicalButton()
{
  if (digitalRead(PUSH_BUTTON_1) == LOW) {
    // pushButton1State is used to avoid sequential toggles
    if (pushButton1State != LOW) {

      // Toggle Relay state
      relay1State = !relay1State;
      digitalWrite(RELAY_PIN_1, relay1State);

      // Update Button Widget
      Blynk.virtualWrite(VPIN_BUTTON_1, relay1State);
    }
    pushButton1State = LOW;
  } else {
    pushButton1State = HIGH;
  }
  
}

void setup()
{

  Serial.begin(115200);
  Blynk.begin(AUTH, WIFI_SSID, WIFI_PASS,"blynk-cloud.com", 8442);
  ArduinoOTA.setHostname(OTA_HOSTNAME);  // For OTA - Use your own device identifying name
  ArduinoOTA.begin();  // For OTA

  pinMode(RELAY_PIN_1, OUTPUT);
  pinMode(PUSH_BUTTON_1, INPUT_PULLUP);
  digitalWrite(RELAY_PIN_1, relay1State);


  // Setup a function to be called every 100 ms
  timer.setInterval(500L, checkPhysicalButton);

   pinMode(RightMotorSpeed, OUTPUT);
    pinMode(LeftMotorSpeed , OUTPUT);
    pinMode( RightMotorDir, OUTPUT);
    pinMode(LeftMotorDir, OUTPUT);

    digitalWrite(RightMotorSpeed, LOW);
    digitalWrite(LeftMotorSpeed , LOW);
    digitalWrite( RightMotorDir, HIGH);
    digitalWrite(LeftMotorDir, HIGH);
}

void loop()
{
  Blynk.run();
  ArduinoOTA.handle();  
  timer.run();
}

BLYNK_WRITE(V1)
{
    int x = param[0].asInt();
    int y = param[1].asInt();
    moveControl(x,y);
}
