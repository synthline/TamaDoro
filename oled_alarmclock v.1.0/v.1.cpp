#include <Arduino.h>
#include <U8x8lib.h>
#include <Wire.h> 
#include <ds3231.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif

U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(/* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);

void setup(void)
{
  /* U8g2 Project: SSD1306 Test Board */
  //pinMode(10, OUTPUT);
  //pinMode(9, OUTPUT);
  //digitalWrite(10, 0);
  //digitalWrite(9, 0);		
  
  /* U8g2 Project: KS0108 Test Board */
  //pinMode(16, OUTPUT);
  //digitalWrite(16, 0);	
  
  u8x8.begin();
  u8x8.setPowerSave(0);
  
  Wire.begin();
  DS3231_init(DS3231_CONTROL_INTCN);
  t.hour=17; 
  t.min=30;
  t.sec=0;
  t.mday=29;
  t.mon=09;
  t.year=2022;
  DS3231_set(t); 
 
  if(t.hour<13){
    if(t.hour>0){
//       lcd.setCursor(3,0);
//       lcd.print("Good Morning !");
        u8x8.drawString(1,3,"Good Morning !");

  }
  }
   if(t.hour<23){
    if(t.hour>19){
//       lcd.setCursor(4,0);
//       lcd.print("Good Night !");
         u8x8.drawString(2,3,"Good Night !");
    }
  }
   if(t.hour<20){
    if(t.hour>12){
//       lcd.setCursor(2,0);
//       lcd.print("Good Afternoon !");
         u8x8.drawString(2,3,"Good Afternoon !");        
    }
   }
}

void loop(){ 
 DS3231_get(&t);

  u8x8.setFont(u8x8_font_chroma48medium8_r);
//  u8x8.drawString(1,3,"Hello World!");
//  u8x8.drawString(3,3,"Hello World!");
//  u8x8.drawString(5,3,"Hello World!");
//  u8x8.drawString(7,3,"Hello World!");

  u8x8.refreshDisplay();		// only required for SSD1606/7  
  delay(2000);
}