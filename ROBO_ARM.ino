#include <Servo.h>


#define speed 1
#define left 4
#define center 5
#define right 6
#define gripper 12

Servo srv[4];
int angles[4] = {90,90,90,90};
int leftEDGE[2] = {70,100};
int centerEDGE[2] = {30,150};
int rightEDGE[2] = {90,130}; 
int gripperEDGE[2] = {75,102};
char buffer [15];
char leftVAL[5],rightVAL[4],centerVAL[4],gripperVAL[4];
boolean stopOk = false;




void leftUpdate () {
  if ( (angles[0] <= leftEDGE[1]) && (angles[0] >= leftEDGE[0]) ) {  
   int t = srv[0].read();

     if (angles[0]>t) {
        srv[0].write(t+1);
     }
     else  {
       srv[0].write(t-1);
     }
   }
}

void centerUpdate () {
  if ( (angles[1] <= centerEDGE[1]) && (angles[1] >= centerEDGE[0]) ) {
   int t = srv[1].read(); 
     if (angles[1]>t) {
        srv[1].write(t+1);
     }
     else  {
       srv[1].write(t-1);
     }
   }
}

void rightUpdate () {
  if ( (angles[2] <= rightEDGE[1]) && (angles[2] >= rightEDGE[0]) ) {
   int t = srv[2].read();

     if (angles[2]>t) {
        srv[2].write(t+1);
     }
     else  {
       srv[2].write(t-1);
     }
   }
}


void gripperUpdate () {
  if ( (angles[3] <= gripperEDGE[1]) && (angles[3] >= gripperEDGE[0]) ) {
   int t = srv[3].read();

     if (angles[3]>t) {
        srv[3].write(t+1);
     }
     else  {
       srv[3].write(t-1);
     }
   }
}

boolean Stop () {
  boolean l =false,c =false,r =false,g =false;
  if (abs(srv[0].read()-angles[0]) <= 5) {l = true;}  
  if (abs(srv[1].read()-angles[1]) <= 5) {c = true;} 
  if (abs(srv[2].read()-angles[2]) <= 5) {r = true;} 
  if (abs(srv[3].read()-angles[3]) <= 5) {g = true;} 
  if (l && c && r && g) {return true;} else {return false;}
}

void portListener () {
    if (Serial.available()) { 
    
     delay(15);
      int i=0; 
     //загоняем прочитанное в буфер
     while( Serial.available() && i< 12) {
        buffer[i++] = Serial.read();
     }
     //закрываем массив
     buffer[i++]='\0';  
   sscanf(buffer, "%[^','],%[^','],%[^','],%s", &leftVAL, &centerVAL, &rightVAL, &gripperVAL);
   leftVAL[3] =  '\0';
   centerVAL[3] =  '\0';
   rightVAL[3] =  '\0';
   gripperVAL[3] =  '\0';
   angles[0] = atoi(leftVAL);
   angles[1] = atoi(centerVAL);
   angles[2] = atoi(rightVAL);
   angles[3] = atoi(gripperVAL);
    stopOk = false;

  }

}



void setup() {
  Serial.begin(9600);  
}

void loop() {
  portListener();
  srv[0].attach(left);
  srv[1].attach(center);
  srv[2].attach(right);
  srv[3].attach(gripper);
  leftUpdate(); 
  centerUpdate();
  rightUpdate();
  gripperUpdate();
  if (Stop() && !stopOk) { Serial.write("1"); stopOk = true; }
  delay(50);
  srv[0].detach();
  srv[1].detach();
  srv[2].detach();
  srv[3].detach();
}
