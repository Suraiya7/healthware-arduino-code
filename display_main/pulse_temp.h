int heartpulseBPM;
int val, cel;
int tempPin = A9;


void pul_temp()
{
  

  if(analogRead(A8)>550)
  {
    heartpulseBPM = analogRead(A8)/10;

    

    val = analogRead(tempPin);
    float mv = ( val/1024.0)*5000; 
    cel = mv/10;


  }   
}
