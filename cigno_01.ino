/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the RESET.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld

*/

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int pinTemp = A0;

const int pinLight = A1;

const int pinLED_V = 7;

const int pinLED_R = 8;

const int pinButton = 9;


int valueLight = 0;

int sum_valueTemp = 0;

int sum_valueLight = 0;

int valueButton = LOW;

int lastvalueButton = 0;

int RESET = 0;


void setup() {
  Serial.begin(9600); // open the serial port at 9600 bps

  pinMode(pinButton, INPUT);
  
  pinMode(pinLED_V, OUTPUT);
  digitalWrite(pinLED_V, LOW);
  
  pinMode(pinLED_R, OUTPUT);
  digitalWrite(pinLED_R, LOW);
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  
  // Print an initial message to the LCD.
  lcd.print("hello, world!");
  
  // set up the temperature pin as an input
  pinMode(pinTemp, INPUT);

  pinMode(pinLight, INPUT);
  
  delay(2000);
  
  lcd.clear();
  
  Serial.print("--- START ---");
  Serial.println();
  
}




void loop() {
  
  valueButton = digitalRead(pinButton);
  Serial.print(valueButton);
  Serial.print("\t");
  
  RESET = RESET + 1;
  if (RESET % 5 == 0) {
    lcd.clear();
    RESET = 0;
  }
  Serial.print(RESET);
  Serial.print("\t");
  
  Serial.print("sum_valueS ");
  sum_valueTemp = 0;
  sum_valueLight = 0;
  
  for(int i=0;i<10;i++) {
    Serial.print(i);
    int valueLight = analogRead(pinLight);
    int valueTemp = analogRead(pinTemp);
    sum_valueLight = sum_valueLight + valueLight;
    sum_valueTemp = sum_valueTemp + valueTemp;
  }
  
  Serial.println();
  
  sum_valueTemp = sum_valueTemp / 10;
  float voltage = (sum_valueTemp / 1024.0) * 5.0;
  float temperatureC = (voltage - .5) * 100;

  sum_valueLight = sum_valueLight / 10;
  int Lightness = map(sum_valueLight, 0, 250, 0, 100);
  
  if (Lightness < 10){
    digitalWrite(pinLED_V, HIGH);
  } else {
    digitalWrite(pinLED_V, LOW);
  }

  if (temperatureC > 21){
    digitalWrite(pinLED_R, HIGH);
  } else {
    digitalWrite(pinLED_R, LOW);
  }
  

 // codice per scrivere sul display LCD
 
  if (valueButton == 1) {
    if ((temperatureC > 25) and (Lightness < 2)) { //Easter Egg
      lcd.clear();
      delay(200);
      lcd.setCursor(0, 0);
      lcd.print("4 8 15 16 23 42");
      lcd.setCursor(0, 1);
      lcd.print("DHARMAinitiative");
      digitalWrite(pinLED_V, LOW);
      digitalWrite(pinLED_R, LOW);
      delay(300);
      
    } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Scemo chi preme");
    lcd.setCursor(0, 1);
    lcd.print("pulsanti a caso!");
  } 
  } else { 
    if (valueButton == 0) {
    lcd.setCursor(0, 0);
    lcd.print("Temp : ");
    lcd.print(temperatureC);
    lcd.setCursor(12, 0);
    lcd.print("C");

    lcd.setCursor(0, 1);
    lcd.print("Light: ");
    lcd.print(Lightness);
    lcd.setCursor(10, 1);
    lcd.print("%");
    lcd.setCursor(12, 1);
    lcd.print(sum_valueLight);
    lcd.print("L");
  }}




  
  /*
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis() / 1000);
*/

  delay(1000);
}
