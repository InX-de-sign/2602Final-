#include "esp32-hal-gpio.h"
#include "Sensor.hpp"

bool L=false;
bool M=false;
bool R=false;

/*Initialize all the IR sensor Data Pins*/
void IR::Init(){
  pinMode(IR_L,INPUT);
  pinMode(IR_M,INPUT);
  pinMode(IR_R,INPUT);

  L = digitalRead(IR_L);
  M = digitalRead(IR_M);
  R = digitalRead(IR_R);
};

/*For the Logic
  0: White 
  1: Black*/
uint8_t IR::Tracking(){ 
  // white black white: Motion::Forwards
  if(!L && M && !R)
    return OnTrack;

  // white white white: Motion::Backwards
  if(!L && !M && !R){
    return OutOfTrack;}

  // black black black: Motion::Backwards
  if(L && M && R){
    return OutOfTrack;}

  // black white black: Motion::Backwards
  if(L && !M && R){
    return OutOfTrack;}

  //black black white/black white white: Motion::Leftwards
  if((L && M && !R) || (L && !M && !R)){
    return IR_LOnTrack;}

  //white black black/white white black: Motion::Rightwards
  //for normal line tracking  
  if((!L && M && R) || (!L && !M && R)){
    return IR_ROnTrack;} 

  return AllOnTrack; 
};

uint8_t IR::Task1(){
  //Serial.println("Task1");
  //Init();

  // white black white: Motion::Forwards
  if(!L && M && !R)
    return OnTrack;

  // white white white: Motion::Forwards
  if(!L && !M && !R){
    return OnTrack;}

  // black black black: Motion::Backwards
  if(L && M && R){
    return OutOfTrack;}

  // black white black: Motion::Backwards
  if(L && !M && R){
    return SlowOnTrack;} //OutOfTrack

  //black black white/black white white: Motion::Leftwards
  if((L && M && !R) || (L && !M && !R)){
    Serial.println("IR_LOnTrack:turning left 45 degrees");
    return IR_LOnTrack;}

  //white black black/white white black: Motion::Rightwards
  //for normal line tracking  
  if(((!L && M && R) || (!L && !M && R)) && !task1Flag){
    Serial.println("with !task1Flag - IR_ROnTrack:turning right 45 degrees");
    return IR_ROnTrack;} 
  if((!L && M && R) && task1Flag){
    Serial.println("Task1 Special Case - walking straight at node2");
    return OnTrack;}
  
  return AllOnTrack;
};

uint8_t IR::Task2(){
  // white black white: Motion::Forwards
  if(!L && M && !R)
    return OnTrack;

  // white white white: Motion::Forwards
  if(!L && !M && !R){
    return OnTrack;}

  // black black black: Motion::Backwards
  if(L && M && R){
    return OutOfTrack;}

  // black white black: Motion::Backwards
  if(L && !M && R){
    return SlowOnTrack;} //OutOfTrack

  //black black white/black white white: Motion::Leftwards
  if((L && M && !R) || (L && !M && !R)){
    Serial.println("IR_LOnTrack:turning left 45 degrees");
    return IR_LOnTrack;}

  //white black black/white white black: Motion::Rightwards
  //for normal line tracking  
  if(((!L && M && R) || (!L && !M && R)) && !task2Flag){
    Serial.println("with !task2Flag - IR_ROnTrack:turning right 45 degrees");
    return IR_ROnTrack;} 
  if((!L && M && R) && task2Flag){
    Serial.println("Task1 Special Case - walking straight at node2");
    return OnTrack;}

  return AllOnTrack;
};

// task3: 10-5-4-7-6/8, with 2-2 traffic light
//don't need to deal with node5&node4?
uint8_t IR::Task3(){
  // white black white
  if(!L && M && !R)
    return OnTrack;

  // white white white: Motion::Backwards
  if(!L && !M && !R){
    return OnTrack;}

  // black black black: Motion::Backwards
  if((L && M && R)&&!task3Flag3_1&&!task3Flag3_2){
    return OutOfTrack;}
  // node7_case1: turning right for node6
  if((L && M && R)&&task3Flag3_1&&!task3Flag3_2){
    Serial.println("node7_case1: turning right for node6");
    return R_90;} //R_90 -> IR_ROnTrack
  // node7_case2: turning left for node8
  if((L && M && R)&&task3Flag3_2&&!task3Flag3_1){
    Serial.println("node7_case2: turning left for node8");
    return L_90;} //

  // black white black: Motion::Backwards
  if(L && !M && R){
    return SlowOnTrack;}

  //black black white/black white white: Motion::Leftwards
  if(((L && M && !R) || (L && !M && !R))&&task3Flag1){
    Serial.println("Turning left 90 degrees for node5");
    return L_90;}
  if(((L && M && !R) || (L && !M && !R))&&!task3Flag1){
    Serial.println("IR_LOnTrack:default mode turning 45 degrees, also for node4");
    return IR_LOnTrack;}

  //white black black/white white black: Motion::Rightwards
  if((!L && M && R) || (!L && !M && R)){
    return IR_ROnTrack;} 

    return OnTrack; 
};
  
uint8_t IR::Task4(){
  // white black white: Motion::Forwards
  if(!L && M && !R)
    return OnTrack;

  // white white white: Motion::Backwards
  if(!L && !M && !R){
    return OutOfTrack;}

  // black black black: Motion::Backwards
  if((L && M && R)&&!task4Flag1&&!task4Flag3){
    return OutOfTrack;}
  // node3: turning left 90 degrees
  if((L && M && R)&&task4Flag1&&!task4Flag3){
    return L_90;}
  // node7: walking straight
  if((L && M && R)&&!task4Flag1&&task4Flag3){
    return OnTrack;}

  // black white black: Motion::Backwards
  if(L && !M && R){
    return OutOfTrack;}

  // white black black/white white black
  if(((!L && M && R) || (!L && !M && R)) && !task4Flag2){
    return IR_ROnTrack;} 
  // node4: turning right 135 degrees
  if(((!L && M && R) || (!L && !M && R)) && task4Flag2){
    return R_135;} 

  // black white white / black black white 
  if((L && M && !R) || (L && !M && !R)){
    return IR_LOnTrack;}  

  return OnTrack; 
};


void Ultrasonic::Init(){
  pinMode(Tirg, OUTPUT); // Sets the trigPin as an Output
  pinMode(Echo, INPUT); // Sets the echoPin as an Input
};

float Ultrasonic::GetDistance(){
  // Clears the trigPin
  digitalWrite(Tirg, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(Tirg, HIGH);
  delayMicroseconds(10);
  digitalWrite(Tirg, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  long  duration = pulseIn(Echo, HIGH);
  
  // Calculate the distance (in cm)
  float distance = (duration * SOUND_SPEED/100)/200;
  
  // Prints the distance in the Serial Monitor
  // Serial.print("Distance (cm): ");
  // Serial.println(distance/100);
  return distance;
};


