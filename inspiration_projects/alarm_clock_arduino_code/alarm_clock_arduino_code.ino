#include <Wire.h>
#include <DS3231.h>

DS3231 clock;
RTCDateTime dt;

int button = 9;
int pirPin = 7; // Input for HC-S501
int pirValue; // Place to store read PIR Value

//--------------------------------------
int set_hour = 7;
int set_minute = 0;
//--------------------------------------

void setup() {
  clock.begin();
  pinMode(button, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  //clock.setDateTime(__DATE__, __TIME__); // !!AFTER THE FIRST UPLOAD YOU HAVE TO COMMENT OUT THIS LINE. OTHERWISE YOU WILL GET A WRONG TIME!!
  pinMode(pirPin, INPUT);
}



void alarm(int minute){
  bool button_pressed = false;
  bool awake = false;
  bool movement = false;
  
  while(!button_pressed){     //the alarm is on as long the button isn't pressed
    for(int i = 0; i < 4; i++){
      tone(11, 523, 100);
      delay(100);
      tone(11, 784, 50);

      for(int i = 0; i < 20; i++){
        if(digitalRead(button) == LOW){
        button_pressed = true;
        awake = true;
        dt = clock.getDateTime();
        minute = dt.minute;
        }
        delay(65);
      }
    }
  }

  dt = clock.getDateTime();
  minute = dt.minute;

  while(awake){
    movement = false;
    dt = clock.getDateTime();
    for(int i = 0; i < 30; i++){
      if(digitalRead(pirPin)){movement = true;}
    }
    digitalWrite(LED_BUILTIN, movement);
    if(!pirValue){
      delay(5000);
      for(int i = 0; i < 40; i++){
        if(digitalRead(pirPin)){movement = true;}
      }
      if(!movement){
        alarm(minute); //if no motion is detected for too long the alarm resets
      }
    }

    if(abs(dt.minute - minute) >= 1){ //set the time period where you must be in front of the sensor
      tone(11, 698, 50);
      delay(100);
      tone(11, 698, 50);
      digitalWrite(LED_BUILTIN, 0);
      awake = false;
    }

    delay(100);
  }

}
 
void loop() {  
  dt = clock.getDateTime();
  if(set_minute == dt.minute && set_hour == dt.hour){
    alarm(set_minute);
  }

  delay(10000);
}
