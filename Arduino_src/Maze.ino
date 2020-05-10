#include <PID_v1.h>

#define s3 A0
#define s1 A3
#define s2 A2
#define s0 A1
#define QRDR 7
#define QRDL 4
#define BUZZ 11
#define ENAL 5
#define ENAR 6
#define GIRL 13
#define GIRR 12

#define C  523
#define CS  524
#define D  587
#define DS  622
#define E  659
#define FA  698
#define FS  740
#define G  784
#define GS  830
#define A  880
#define AS  932
#define B  988

const unsigned int ini_notes[] = {660,660,660,510,660,770,380};
const unsigned int ini_beat[] = {100,100,100,100,100,100,100};
const unsigned int ini_mute[] ={150,300,300,100,300,550,575};

const unsigned int fin_notes[] = {G,C,E,G,C,E,C,G, GS,CS,FA,GS,CS,GS, AS,DS,G,AS,DS,G,DS, DS,DS,DS, C};
const unsigned int fin_beat[] = {100,100,100,100,100,100,100,150,100, 100,100,100,100,100,100,100,150,100, 100,100,100,100,100,100,100,150, 40,40,40, 150};

const int maxpwm = 255; // the maximum speed
const int cal=200;

int path[100], path_step = 0;

int i, x, k, ts = 50, spin = 40, halftape=100, lilbit=20, s[4];

bool flag = false;

double pos, sp=250, power_difference;
int mini0=1023, maxi0=0, mini1=1023, maxi1=0, mini2=1023, maxi2=0, mini3=1023, maxi3=0;

//Specify the links and initial tuning parameters
PID myPID(&pos, &power_difference, &sp, 10, 5, 1, DIRECT);

void setup() {
  // put your setup code here, to run once:
  pinMode(ENAR,OUTPUT);
  pinMode(ENAL,OUTPUT);
  pinMode(GIRR,OUTPUT);
  pinMode(GIRL,OUTPUT);
  pinMode(BUZZ,OUTPUT);
  pinMode(QRDL,INPUT);
  pinMode(QRDR,INPUT);

  digitalWrite(BUZZ, LOW);

  //set and turn the PID on
  myPID.SetOutputLimits(-maxpwm, maxpwm);
  myPID.SetMode(AUTOMATIC);
  myPID.SetSampleTime(50); 

  Serial.begin(9600);
  delay(2000);
  //start music
  /*for (int note = 0; note < 7; note++) {
    tone(BUZZ, ini_notes[note], ini_beat[note]);
    delay(ini_mute[note]);
  }*/

  calibrate_line_sensors();
  Serial.print(mini0);
  Serial.print("\t");
  Serial.println(maxi0);
  Serial.print(mini1);
  Serial.print("\t");
  Serial.println(maxi1);
  Serial.print(mini2);
  Serial.print("\t");
  Serial.println(maxi2);
  Serial.print(mini3);
  Serial.print("\t");
  Serial.println(maxi3);

  
  //delay(3000);
}

void loop() {

  // follow black line 
  follow_segment();
  
  if (digitalRead(QRDR)==false){ // cross section, go rigth
    read_line();
    if (!flag){
      digitalWrite(BUZZ, HIGH);
      delay(halftape);
      digitalWrite(BUZZ, LOW);
      set_motors(maxpwm,maxpwm);
      delay(halftape);
      rigth_sensor();
    }
  }
    
  if (flag){                            // white space
    
    flag = false;
    set_motors(maxpwm,maxpwm);
    bool l, r;
    for (i=1;i<lilbit;i++){             // advance a little bit or until turn l/r is found
        delay(ts);
        l = !digitalRead(QRDL);
        r = !digitalRead(QRDR);
        if (l || r){
          digitalWrite(BUZZ, HIGH);
          delay(halftape);
          digitalWrite(BUZZ, LOW);
          l = l | !digitalRead(QRDL);
          r = r | !digitalRead(QRDR);
          if ((l && r) || r){       
            rigth_sensor();             // turn rigth
          }else{
            left_sensor();              // turn left
          }
          break;
        }
    }
    
    if (i == lilbit){
      read_line();
      if (flag){
        flag = false;
        digitalWrite(BUZZ, HIGH);
        delay(halftape);
        digitalWrite(BUZZ, LOW);
        turn_around();
      }else{
        int cont = 0;
        do {
          cont++;
          follow_segment();
        }while(!flag && cont < lilbit);
        if (flag){
          flag = false;
          set_motors(-maxpwm,-maxpwm);
          set_motors(0,0);
          //FINISH music
  /*        for (int note = 0; note < 27; note++) {
            tone(BUZZ, fin_notes[note], fin_beat[note]);
          }
 */         while(1);
        }
      }
      
    }
  }
/*  read_line();
  Serial.print(s[0]);
  Serial.print(",");
  Serial.print(s[1]);
  Serial.print(",");
  Serial.print(s[2]);
  Serial.print(",");
  Serial.println(s[3]);
  //Serial.print(power_difference);
  //Serial.print('\t');
  Serial.println(pos);
  delay(100);
  */
  flag = false;
}

