#define BLYNK_PRINT Serial   
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

#define BLYNK_PRINT Serial
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS D4
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

char auth[] ="fXgQx1xCNKPYJ1PDy1U8IwoBfnW2RtUq"; //kode auth yg dikirim ke email
char ssid[] = " your ssid"; //ssid 
char pass[] = "your pass";  //password 

#define sensorPin D3 
int sensorState = 0;
int lastState = 0;

#define DHTPIN D4    
#define DHTTYPE DHT11
     
DHT dht(DHTPIN, DHTTYPE);
void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
   pinMode(sensorPin, INPUT);
  dht.begin();

  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
   sensors.begin();
}
int sensor=0;
void sendTemps()
{
sensor=analogRead(A0);
sensors.requestTemperatures();
float temp = sensors.getTempCByIndex(0); 
Serial.println(temp);
Serial.println(sensor);
Blynk.virtualWrite(V1, temp);
Blynk.virtualWrite(V2,sensor);
delay(1000);
}
void loop()
{
  Blynk.run(); 
  sendTemps();
  sensorState = digitalRead(sensorPin);
Serial.println(sensorState);

if (sensorState == 1 && lastState == 0) {
  Serial.println("Tanaman butuh air");
  Blynk.notify("Siram tanaman anda");
  lastState = 1;
  delay(1000);
    
  } 
  else if (sensorState == 1 && lastState == 1) {
  Serial.println("Tanaman belum membutuhkan air");
  delay(1000);
  }
  else {
    Serial.println("Tidak perlu disiram");
    lastState = 0;
    delay(1000);
  }
  
  delay(100);
}
