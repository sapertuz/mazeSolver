// lets you set the duty cycle, and it uses 8-bit precision: a value of 255 
// corresponds to 100% duty cycle. For example, to get 67% on M1 and 33% on
// M2, you would call
// Example: set_motors(171,84);

void set_motors(int pwml, int pwmr){
  if (pwml<0){
    analogWrite(ENAL,-1*pwml);
    digitalWrite(GIRL,1);
  }else{
    analogWrite(ENAL,pwml);
    digitalWrite(GIRL,0);
  }
  if (pwmr<0){
    analogWrite(ENAR,-1*pwmr);
    digitalWrite(GIRR,1);
  }else{
    analogWrite(ENAR,pwmr);
    digitalWrite(GIRR,0);
  }
}
