#include <dht.h>

#include <Wire.h>

#include <dht.h>
#include <SoftwareSerial.h>

dht DHT;

#define DHT11_PIN 7
#define RX 10
#define TX 11

//String AP = "motophone";       // CHANGE ME
//String PASS = "12345678"; // CHANGE ME
String AP = "ONE";       // CHANGE ME
String PASS = ""; // CHANGE ME

int countTrueCommand;
int countTimeCommand; 
boolean found = false; 
int valSensor = 1;
String HOST = "173.255.227.48";
//String HOST = "192.168.0.7";
String PORT = "9999";
int Sensor_Val = 0;

SoftwareSerial esp8266(RX,TX); 

void setup() 
{
  Serial.begin(9600);
  esp8266.begin(9600);
  sendCommand("AT",5,"OK");
  sendCommand("AT+CWMODE=1",5,"OK");
  sendCommand("AT+CWJAP=\""+ AP +"\",\""+ PASS +"\"",20,"OK");
}

void loop() {

   /* READ THE SENSOR VALUE */
  int chk = DHT.read11(DHT11_PIN);
  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);
  
  /* Reading the data in every 10 seconds and sending it */
  delay(1000);
  Sensor_Val = analogRead(A0);
  String getData = "MOISTURE_DATA_NAN"+String(Sensor_Val);//change
  Serial.println(getData); 
  sendCommand("AT+CIPMUX=1",5,"OK");
  sendCommand("AT+CIPSTART=0,\"TCP\",\""+ HOST +"\","+ PORT,15,"OK");
  sendCommand("AT+CIPSEND=0," +String(getData.length()),4,">");
  esp8266.println(getData);
  delay(1500);
  sendCommand("AT+CIPCLOSE=0",5,"OK");
}

void sendCommand(String command, int maxTime, char readReplay[]) {
  Serial.print(countTrueCommand);
  Serial.print(". at command => ");
  Serial.print(command);
  Serial.print(" ");
  while(countTimeCommand < (maxTime*1))
  {
    esp8266.println(command);//at+cipsend
    if(esp8266.find(readReplay))//ok
    {
      found = true;
      break;
    }
  
    countTimeCommand++;
  }
  
  if(found == true)
  {
    Serial.println("OK");
    countTrueCommand++;
    countTimeCommand = 0;
  }
  
  if(found == false)
  {
    Serial.println("Fail");
    countTrueCommand = 0;
    countTimeCommand = 0;
  }
  
  found = false;
 }
