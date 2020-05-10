// Normally, we will be following a line. 
// The maximum speed is turned down to maxpwm for reliability.

void follow_segment(){
    // Get the position of the line.
    read_line();
    
    myPID.Compute();
    
    // Compute the actual motor settings. We never set either motor
    // to a negative value.
    if(power_difference > 0)
      set_motors(maxpwm-(int)power_difference,maxpwm);
    else
      set_motors(maxpwm,maxpwm+(int)power_difference);

    delay(ts);
    // We use the inner two sensors for
    // determining whether there is a line straight ahead.
}
