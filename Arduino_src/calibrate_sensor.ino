/* This function calibrate the analog QTR sensors it use to follow segment
   to recognize white and black
*/
void calibrate_line_sensors(){
  int temp, temp1;

  temp = millis();
  
  set_motors(cal,-1*cal);
  
  do{
    s[0]=analogRead(s0);
    s[1]=analogRead(s1);
    s[2]=analogRead(s2);
    s[3]=analogRead(s3);
    
    if (mini0>s[0])
      mini0=s[0];
    if (mini1>s[1])
      mini1=s[1];
    if (mini2>s[2])
      mini2=s[2];
    if (mini3>s[3])
      mini3=s[3];
    
    if (maxi0<s[0])
      maxi0=s[0];
    if (maxi1<s[1])
      maxi1=s[1];
    if (maxi2<s[2])
      maxi2=s[2];
    if (maxi3<s[3])
      maxi3=s[3];
    
    delay(20);
  }while(digitalRead(QRDL) == true && digitalRead(QRDR) == true);
  temp1 = millis();
  spin = (temp1-temp);
  
  do{ 
    delay(1);
  }while(digitalRead(QRDL) == false || digitalRead(QRDR) == false);
  temp = millis();

  halftape = (temp - temp1)/4;
  spin = spin + (temp - temp1)/2;
  lilbit = (spin)*2/3;
  lilbit = lilbit/ts;
  
  set_motors(-1*cal,cal);
  delay(halftape);
  for (i=1;i<=spin/10;i++){
    s[0]=analogRead(s0);
    s[1]=analogRead(s1);
    s[2]=analogRead(s2);
    s[3]=analogRead(s3);
    
    if (mini0>s[0])
      mini0=s[0];
    if (mini1>s[1])
      mini1=s[1];
    if (mini2>s[2])
      mini2=s[2];
    if (mini3>s[3])
      mini3=s[3];
    
    if (maxi0<s[0])
      maxi0=s[0];
    if (maxi1<s[1])
      maxi1=s[1];
    if (maxi2<s[2])
      maxi2=s[2];
    if (maxi3<s[3])
      maxi3=s[3];
    
    delay(20);
  }
  
  set_motors(cal,-1*cal);
  for (i=1;i<=spin/20;i++){
    s[0]=analogRead(s0);
    s[1]=analogRead(s1);
    s[2]=analogRead(s2);
    s[3]=analogRead(s3);
    
    if (mini0>s[0])
      mini0=s[0];
    if (mini1>s[1])
      mini1=s[1];
    if (mini2>s[2])
      mini2=s[2];
    if (mini3>s[3])
      mini3=s[3];
    
    if (maxi0<s[0])
      maxi0=s[0];
    if (maxi1<s[1])
      maxi1=s[1];
    if (maxi2<s[2])
      maxi2=s[2];
    if (maxi3<s[3])
      maxi3=s[3];
    
    delay(20);
  }

  set_motors(-1*cal,cal);
  delay(10);
  set_motors(0,0);
 
}
