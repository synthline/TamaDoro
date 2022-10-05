  
/* Project by:
*                      __  __    ___          
*    _______  ______  / /_/ /_  / (_)___  ___ 
*   / ___/ / / / __ \/ __/ __ \/ / / __ \/ _ \
*  (__  ) /_/ / / / / /_/ / / / / / / / /  __/
* /____/\__, /_/ /_/\__/_/ /_/_/_/_/ /_/\___/ 
*      /____/                                 
*      
* The project is a combination of several projects. Here are the original projects and authors:
* 
* 1. LCD Screens and the Arduino Uno article by Aidan
* Link: https://core-electronics.com.au/guides/use-lcd-arduino-uno/
*
* 2. Arduino DS3231 Real Time Clock Module Tutorial, created by Dejan Nedelkovski --> www.HowToMechatronics.com
* Link: https://howtomechatronics.com/tutorials/arduino/arduino-ds3231-real-time-clock-tutorial/
* 
* 2.1 Download the DS3231 libary from http://www.rinkydinkelectronics.com
* 
* 3. How to Make an Arduino Alarm Clock Using a Real-Time Clock and LCD Screen
* Link: https://maker.pro/arduino/projects/arduino-alarm-clock-using-real-time-clock-lcd-screen
* 
* 4. Arduino 2 Led Blink
* Link: https://create.arduino.cc/projecthub/sumeyye-varmis/arduino-2-led-blink-24c93c
* 
*/

#include <DS3231.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include "DHT.h"

// The pins the LED is connected to
#define green_led 8
#define red_led 9

// Initialise the LCD with the arduino. 
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
DS3231 rtc(SDA, SCL);

Time ti ;

// Digital pin connected to the DHT sensor
#define DHTPIN 6
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// Assign via number to the buzzer
#define buz 10

// Define the time elements
int Hor, Min, Sec;

void setup() {
  // Declare the LEDs as an output
  pinMode(green_led, OUTPUT);
  pinMode(red_led, OUTPUT);
  
  // Switch on the LCD screen
  lcd.begin(16, 2);

  Wire.begin();
  dht.begin();
  
  // Uncomment the next line if you are using an Arduino Leonardo
  //while (!Serial) {}
  
  // Initialize the rtc object
  rtc.begin();

  // Setup Serial connection
  Serial.begin(9600);

  pinMode(buz, OUTPUT);
  lcd.begin(16,2);

  // Welcome Messages:
  lcd.setCursor(0,0);
  lcd.print("Welcome to");
  delay(1000);
  lcd.clear();
  
  lcd.setCursor(0,1);
  lcd.print("The amazing");
  delay(1000);
  lcd.clear();
  
  lcd.setCursor(0,0);
  lcd.print("Synthline's LCD");
  delay(2000);
  lcd.clear();
  
  lcd.setCursor(0,1);
  lcd.print("Alarm Clock v1.0");
  delay(2000);
  lcd.clear();

  // Set the date and time
  // Set Day-of-Week to SUNDAY
  rtc.setDOW(FRIDAY);
  
  // Set the time to 12:00:00 (24hr format)
  rtc.setTime(13, 35, 0);
  
  // Set the date to January 1st, 20
  rtc.setDate(30, 9, 2022);  
  
  delay(500);
}



void loop() {
  // DHT
  // Read Humidity
  float h = dht.readHumidity();
  
  // Read Temperature
  float temp = dht.readTemperature();
  
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again)
  if (isnan(h) || isnan(temp) || isnan(f)) {
    lcd.setCursor(0,0);
    lcd.print("Failed to read ");
    lcd.setCursor(0,1);
    lcd.print("from DHT sensor!");
    delay(500);
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);

  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(temp, h, false);
  
  // RTC
  ti = rtc.getTime();
  Hor = ti.hour;
  Min = ti.min;
  Sec = ti.sec;

 lcd.setCursor(0,0);

 lcd.print("Time: ");

 lcd.print(rtc.getTimeStr());

 lcd.setCursor(0,1);

 lcd.print("Date: ");

 lcd.print(rtc.getDateStr());

 delay (5000);

 // Display the Temperature and Humidity:
 
  lcd.setCursor(0,0);

  lcd.print("Humid. ");

  lcd.print(h);

  lcd.print(" %");

  lcd.setCursor(0,1);

  lcd.print("Temp. ");

  lcd.print(temp);

  lcd.print(" C.  ");

  //Here you could also add a Heat Index, both in Celcius and Fahrerheit. Check the original project (#3) on further instructions.

  delay (5000);
 
  //Comparing the current time with the Alarm time 
  if( Hor == 13 && (Min == 36 || Min == 00)) {

  Buzzer();

  Buzzer();

  lcd.clear();

  lcd.print("Alarm ON");

  lcd.setCursor(0,1);

  lcd.print("Alarming!!");

  Buzzer();

  Buzzer();

  } 

 delay(500); 

}

void Buzzer() {

  digitalWrite(buz,HIGH);
  
  // Turn the LED on
  digitalWrite(green_led, HIGH);
  digitalWrite(red_led, LOW);
  delay(500);
  digitalWrite(green_led, LOW);
  digitalWrite(red_led, HIGH);
  delay(500);
  digitalWrite(buz, LOW);


 // Wait half a second before repeating
  delay(500);

}
