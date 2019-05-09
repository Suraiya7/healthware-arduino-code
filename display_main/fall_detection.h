#include<Math.h>
#include "send_sms.h"


//Pin defination for accelerometer
const int xpin = A10;                  // x-axis of the accelerometer
const int ypin = A11;                  // y-axis
const int zpin = A12;                  // z-axis (only on 3-axis models)
float xZero = 328;       //callibrate  values jkun level thake 
float yZero = 328;  //callibrate  values jkun level thake 
float zZero = 328;  //callibrate  values jkun level thake 
float Xval, Yval, Zval,Anet;  

void fall_detect() 
{
  
  Xval = (analogRead(xpin)- xZero)/102; 
  Yval = (analogRead(ypin) - yZero)/102; 
  Zval = (analogRead(zpin) - zZero)/102; 

  Anet = sqrt(sq(Xval) + sq(Yval) + sq(Zval)); // net acc calc.
   
        


    
    
      int state = Serial.parseInt();
      if (state == 1)
      {
   
      sms();
      }
/*
  if(Anet>1)//fall er por acc barbe abar onktai.. tora connect kore koto jore porle fall mone hoe tr seta ekbar phele dheke value ta sei bhabe bosas
  {           
     Serial.println("Fall detected");
     Serial.println(Anet);
     sms();
  }
  
  */ 
}
