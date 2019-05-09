#include <DFRobot_sim808.h>
#include <SoftwareSerial.h>


#define MESSAGE_LENGTH 160
char message[MESSAGE_LENGTH];
char MESSAGE[300];
char lat[12];
char lon[12];

char phone[16]= "9836961390";
//char datetime[24];


DFRobot_SIM808 sim808(&Serial1);//Connect RX,TX,PWR,


void sms()
{
    if( sim808.attachGPS())
    Serial.println("Open the GPS power success");
  else 
    Serial.println("Open the GPS power failure");


     while(!sim808.getGPS())  //obtaining GPS location
    {
      //Serial.println("Getting location....");
    }

   
      Serial.print(sim808.GPSdata.year);
      Serial.print("/");
      Serial.print(sim808.GPSdata.month);
      Serial.print("/");
      Serial.print(sim808.GPSdata.day);
      Serial.print(" ");
      Serial.print(sim808.GPSdata.hour);
      Serial.print(":");
      Serial.print(sim808.GPSdata.minute);
      Serial.print(":");
      Serial.print(sim808.GPSdata.second);
      Serial.print(":");
      Serial.println(sim808.GPSdata.centisecond);
      Serial.print("latitude :");
      Serial.println(sim808.GPSdata.lat);
      Serial.print("longitude :");
      Serial.println(sim808.GPSdata.lon);
      Serial.print("speed_kph :");
      Serial.println(sim808.GPSdata.speed_kph);
      Serial.print("heading :");
      Serial.println(sim808.GPSdata.heading);
      Serial.println();
  
      double la = sim808.GPSdata.lat;
      double lo = sim808.GPSdata.lon;

  
      dtostrf(la, 6, 6, lat); //put float value of la into char array of lat. 6 = number of digits before decimal sign. 2 = number of digits after the decimal sign.
      dtostrf(lo, 6, 6, lon); //put float value of lo into char array of lon

    
      sprintf(MESSAGE, "I'm in danger!!\nLocate me : \nhttp://maps.google.com/maps?q=%s,%s\n", lat, lon);
      
       Serial.println("Sim808 init success");
       Serial.println("Start to send message ...");
       Serial.println(MESSAGE);
       Serial.println(phone);
       sim808.sendSMS(phone,MESSAGE);
       Serial.println("Sent Succesfully");
      //************* Turn off the GPS power ************
      sim808.detachGPS();
}
