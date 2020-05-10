/*
This takes a sensor reading and returns an estimate of the robot’s position
with respect to the line, as a number between 0 and 2000. A value of 2000 means 
that the line is to the left, value of 1000 means that the line is directly under 
sensors, 2000 means that the line is directly under sensor 2, and so on.
The value returned by read_line() is divided into three possible cases:
◦ 0–1000: the robot is to the right of the line. 
◦ 1000: the robot is centered on the line. 
◦ 1000–2000: the robot is to the left of the line. 
*/

void read_line(){
  float tmp;
  
  s[0]=analogRead(s0);
  s[1]=analogRead(s1);
  s[2]=analogRead(s2);
  s[3]=analogRead(s3);
   
  s[0]=map(s[0],mini0,maxi0,0,100);
  s[1]=map(s[1],mini1,maxi1,0,100);
  s[2]=map(s[2],mini2,maxi2,0,100);
  s[3]=map(s[3],mini3,maxi3,0,100);

  tmp = ((float)s[0]*100 + (float)s[1]*200 + (float)s[2]*300 + (float)s[3]*400)/((float)s[0] + (float)s[1] + (float)s[2] + (float)s[3]);
  
  if (s[1] > 30 && s[2] > 30 && s[3] > 30){                                 //left cross
    tmp = ((float)s[1]*200 + (float)s[2]*300)/((float)s[1] + (float)s[2]);
  }
  if (s[0] > 30 && s[1] > 30 && s[2] > 30){                                 //rigth cross
    tmp = ((float)s[1]*200 + (float)s[2]*300)/((float)s[1] + (float)s[2]);
  }
  if (s[0] > 30 && s[1] > 30 && s[2] > 30 && s[4] > 30){                    //double cross
    tmp = ((float)s[1]*200 + (float)s[2]*300)/((float)s[1] + (float)s[2]);
  }
  if (s[0] < 20 && s[1] < 20 && s[2] < 20 && s[3] < 20){            // white space
    flag = true;
  } 
  if ((tmp > 0) && (!flag)){
    pos = tmp;
  }
}
