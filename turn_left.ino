// function used to turn the robot rigth

void left_sensor(){
/*  set_motors(-maxpwm,-maxpwm);
  delay(10);
  set_motors(0,0);
  delay(2000);
  
  set_motors(maxpwm,maxpwm);
  delay(halftape);
  
  set_motors(-maxpwm,-maxpwm);
  delay(10);
  set_motors(0,0);
  delay(2000);
    
  set_motors(-1*maxpwm,maxpwm);
  delay(spin);

  set_motors(maxpwm,-maxpwm);
  delay(10);
  set_motors(0,0);
  delay(2000);
  
  for(k=1;k<=lilbit;k++){
    follow_segment();
  }
  
  set_motors(-maxpwm,-maxpwm);
  delay(10);
  set_motors(0,0);
  delay(2000); 
*/
  
  set_motors(-1*maxpwm,maxpwm);
  delay(spin);

  for(k=1;k<=lilbit;k++){
    follow_segment();
  }
  
}
