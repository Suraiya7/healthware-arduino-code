/*PIN DEFINATTION:
 * 
 * 
 * SIM808 Config:
 * SIM808  --  Arduino
 * TXD     --  RX1(19)
 * RXD     --  TX1(18)
 * 
 * Pulse Sensor Config:
 * Connect Signal to A8
 * 
 * LM35 (Temperature Sensor) Config:
 * Connect Signal to A9
 * 
 * Accelerometer Config:
 * X -- A10
 * Y -- A11
 * Z -- A12
 * 
 * GSR Config:
 * Connect Signal to A13
 * 
 * 
 * 
 * 
 * 
 */




#include <MCUFRIEND_kbv.h>
#include "pulse_temp.h"
#include "fall_detection.h"


MCUFRIEND_kbv tft;   //Creating object for display






// *** Define Name of Color
#define Black           0x0000      /*   0,   0,   0 */
#define Navy            0x000F      /*   0,   0, 128 */
#define DarkGreen       0x03E0      /*   0, 128,   0 */
#define DarkCyan        0x03EF      /*   0, 128, 128 */
#define Maroon          0x7800      /* 128,   0,   0 */
#define Purple          0x780F      /* 128,   0, 128 */
#define Olive           0x7BE0      /* 128, 128,   0 */
#define LightGrey       0xC618      /* 192, 192, 192 */
#define DarkGrey        0x7BEF      /* 128, 128, 128 */
#define Blue            0x001F      /*   0,   0, 255 */
#define Green           0x07E0      /*   0, 255,   0 */
#define Cyan            0x07FF      /*   0, 255, 255 */
#define Red             0xF800      /* 255,   0,   0 */
#define Magenta         0xF81F      /* 255,   0, 255 */
#define Yellow          0xFFE0      /* 255, 255,   0 */
#define White           0xFFFF      /* 255, 255, 255 */
#define Orange          0xFD20      /* 255, 165,   0 */
#define GreenYellow     0xAFE5      /* 173, 255,  47 */
#define Pink            0xF81F


void setup()
{




  //Screen setup
  tft.reset(); //Reset LCD to begin
  tft.begin(0x6767); //MCUFRIEND Chipset ID on Library
  tft.setRotation(3); // Set Rotation at 0 degress (default)
  tft.fillScreen(DarkGrey); //Set Background Color with BLACK

  
  Serial.begin(9600); //Serial begin at baud 9600
  
  
  pinMode(A8,INPUT);  //setup for pulse sensor


    //******** Initialize sim808 module *************
  
  Serial1.begin(9600);
  while(!sim808.init())
  {
      Serial.print("Sim808 init error\r\n");
      tft.setCursor (40,100);
      tft.setTextSize (2);
      tft.setTextColor (Red,DarkGrey);
      tft.print ("Sim808 init error"); 
      delay(1000);
  }
  delay(2000);




  
 

 

    tft.fillScreen(DarkGrey); //Set Background Color with BLACK

    tft.setCursor (90,30);
    tft.setTextSize (3);
    tft.setTextColor (White,DarkGrey);
    tft.print ("Welcome!");

    tft.setCursor (40,100);
    tft.setTextSize (4);
    tft.setTextColor (LightGrey,DarkGrey);
    tft.print ("HEALTH 3P"); 


    tft.setCursor (40,150);
    tft.setTextSize (1);
    tft.setTextColor (LightGrey,DarkGrey);
    tft.print ("Protection, Prevention, Preservation");


    delay(1000);
    tft.fillScreen(DarkGrey);
    delay(500);



    tft.setCursor (7,208);
    tft.setTextSize (3);
    tft.setTextColor (White,DarkGrey);
    tft.print ("HEALTH 3P"); 
    
    tft.setCursor (55,10);
    tft.setTextSize (1);
    tft.setTextColor (White,DarkGrey);
    tft.print ("PULSE RATE");

    tft.setCursor (215,10);
    tft.setTextSize (1);
    tft.setTextColor (White,DarkGrey);
    tft.print ("TEMPERATURE");

    tft.setCursor (210,118);//emotion index from GSR
    tft.setTextSize (1);
    tft.setTextColor (White,DarkGrey);
    tft.print ("ANXIETY LEVEL");

    tft.setCursor (230,205);//Bluetooth connection status
    tft.setTextSize (1);
    tft.setTextColor (White,DarkGrey);
    tft.print ("..... ");

    tft.setCursor (120,50);
    tft.setTextSize (2);
    tft.setTextColor (Red,DarkGrey);
    tft.print ("BPM");

    tft.setCursor (280,30);
    tft.setTextSize (2);
    tft.setTextColor (White,DarkGrey);
    tft.print ("C");
  
    


//Design Interface (lines)
   tft.fillRect(0,236,320,4,Purple); //bottom line
   tft.fillRect(0,0,320,4,Purple);  //top line
   tft.fillRect(0,0,4,240,Purple);  //left line
   tft.fillRect(316,0,4,240,Purple); //right line
   tft.fillRect(0,197,320,4,Purple);  //horizontal bottom line 
   tft.fillRect(180,0,4,240,Purple);  //vertical line
   tft.fillRect(180,98,140,4,Purple);  //horizontal small line

}


void loop()
{
  //initialising variables
  cel = 0;
  heartpulseBPM = 0;


  fall_detect();  //checking if the person has fallen or not

  pul_temp(); //checking pulse and temperature of user

  //displaying pulse on screen
  tft.fillRect(45,85,75,55,DarkGrey);
  tft.setCursor (50,90);
  tft.setTextSize (6);
  tft.setTextColor (White,DarkGrey);  
  tft.print (heartpulseBPM);

  //displaying temperature on screen
  tft.fillRect(225,45,60,30,DarkGrey);  
  tft.setCursor (230,50);
  tft.setTextSize (3);
  tft.setTextColor (White,DarkGrey);
  tft.print (cel);
    

  //Stress Detection 
  if(heartpulseBPM >80 && cel> 48)
  {
    tft.fillRect(195,145,105,30,DarkGrey);
    tft.setCursor (200,150);
    tft.setTextSize (2);
    tft.setTextColor (White,DarkGrey);
    tft.print ("STRESSED");  
  }
  
  else
  {
    tft.fillRect(195,145,105,30,DarkGrey);
    tft.setCursor (215,150);
    tft.setTextSize (2);
    tft.setTextColor (White,DarkGrey);
    tft.print ("NORMAL");
   }

    //Displaying data in serial
    
    Serial.print("Press 1 for manually triggering sms() ");
    Serial.println(); 
    Serial.print("Pulse : ");  
    Serial.print(heartpulseBPM);
    Serial.println();
    Serial.print("Temperature : ");  
    Serial.print(cel);
    Serial.println();

    Serial.println(Anet);     
   
    delay(1000);
}
