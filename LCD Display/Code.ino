#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int temp,inte;
long tm,t,d;
void setup() {
 lcd.begin(16, 2);
 lcd.print("Hello world");
 Serial.begin(9600);
 pinMode(0,INPUT);//temperature sensor connected to analog 0
 analogReference(DEFAULT);
}
void loop()
{
 temp = analogRead(0); //analog reading temperature sensor values
 //inte = atoi (temp);
 //required for converting time to seconds
 tm = millis();
 t = tm/1000;
 d = tm%1000;
 Serial.flush();
 //printing time in seconds
 Serial.print("time : ");
 Serial.print(t);
 Serial.print(".");
 Serial.print(d);
 Serial.print("s\t");

 //printing temperature sensor values
 Serial.print("temperature : ");
 Serial.print(temp);
 Serial.println("f");
 lcd.setCursor (0,0);
 lcd.print ("hello kala ");
 lcd.print (t);
 lcd.print (".");
 lcd.print (d);
 lcd.print ("s\t");
 lcd.setCursor (0,1);
 lcd.print ("farhan ");
 lcd.print (temp);

 delay(2000);//delay of 2 seconds
}

