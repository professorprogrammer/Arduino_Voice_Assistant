#include<Servo.h>
Servo head;
Servo l_hand;
Servo r_hand;
// define sonar sensor's pins
int trig = 4;
int echo = 5;
// received data
byte val = "";
void setup() {
 // put your setup code here, to run once:
 head.attach(2);
 l_hand.attach(3);
 r_hand.attach(4);
 Serial.begin(9600); // for communicating via serial port with Python
}
void standby(){
 // all motors to these positions
 head.write(0);
 int r_pos = 30;
 int l_pos = map(r_pos, 0, 180, 180, 0);
 l_hand.write(l_pos);
 r_hand.write(r_pos);
}
void hi(){
 // all motors to these positions
 head.write(90);
 int i = 0;
 for(i=30; i<= 170; i++){
   r_hand.write(i);
   delay(5);
 }
 for(i=170; i>= 100; i--){
   r_hand.write(i);
   delay(5);
 }
 for(i=100; i<= 170; i++){
   r_hand.write(i);
   delay(5);
 }
 for(i=170; i>= 30; i--){
   r_hand.write(i);
   delay(5);
 }
 standby();
}
void hands_up(){
 // do this on every command (nothing much just move hands a bit)
 //head.write(150);
 //delay(300);
 //head.write(90);
 int i = 0;
 for(i=30; i<= 170; i++){
   int r_pos = i;
   int l_pos = map(r_pos, 0, 180, 180, 0);
   l_hand.write(l_pos);
   r_hand.write(r_pos);
   delay(5);
 }
 delay(600);
 for(i=170; i>= 30; i--){
   int r_pos = i;
   int l_pos = map(r_pos, 0, 180, 180, 0);
   l_hand.write(l_pos);
   r_hand.write(r_pos);
   delay(5);
 }
}



void look_left(){
 // rotate hed to left
 head.write(90);
}

void double_punch(){
 // do a punch
 int i = 0;
 for(i=30; i>= 0; i--){
     int r_pos = i;
     int l_pos = map(r_pos, 0, 180, 180, 0);
     l_hand.write(l_pos);
     r_hand.write(r_pos);
     delay(5);
     }
 delay(2000);
 int r_pos = 80;
 int l_pos = map(r_pos, 0, 180, 180, 0);
 l_hand.write(l_pos);
 r_hand.write(r_pos);
 delay(500);
 standby();
}
void r_upper_cut(){
 // make right upper-cut
 int i = 0;
 for(i=30; i<= 170; i++){
   int r_pos = i;
   int l_pos = map(r_pos, 0, 180, 180, 0);
   l_hand.write(l_pos);
   r_hand.write(r_pos);
   delay(5);
 }
 for(int count=0; count<=4; count++){
   int i = 0;
   for(i=170; i>= 60; i--){
     r_hand.write(i);
     delay(1);
     }
   for(i=60; i<= 170; i++){
     r_hand.write(i);
     delay(1);
     }
   }
  standby();
  delay(100);
}
void smash(){
 // smash things
 int i = 0;
 for(i=30; i<= 170; i++){
   int r_pos = i;
   int l_pos = map(r_pos, 0, 180, 180, 0);
   l_hand.write(l_pos);
   r_hand.write(r_pos);
   delay(5);
 }
 delay(2000);
 for(i=170; i>= 0; i--){
   int r_pos = i;
   int l_pos = map(r_pos, 0, 180, 180, 0);
   l_hand.write(l_pos);
   r_hand.write(r_pos);
   delay(1);
 }
 delay(300);
 int r_pos = 180;
 int l_pos = map(r_pos, 0, 180, 180, 0);
 l_hand.write(l_pos);
 r_hand.write(r_pos);
 delay(1000);
 standby();
}

void loop() {
 // put your main code here, to run repeatedly:
 standby();
 while(Serial.available() > 0)  //look for serial data available or not
 {
   val = Serial.read();        //read the serial value
   if(val == 'h'){
     // do hi
      hi();
   }
   if(val == 'p'){
     // do hi
      double_punch();
   }
   if(val == 'u'){
     hands_up();
     delay(500);
   }
   if(val == 'l'){
     standby();
     look_left();
     delay(500);
   }
   if(val == 'U'){
     // uppercut
     r_upper_cut();
     delay(500);
   }
   if(val == 's'){
     smash();
     delay(500);
   }


 }
}