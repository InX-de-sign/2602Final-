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

  bool L = digitalRead(IR_L);
  bool M = digitalRead(IR_M);
  bool R = digitalRead(IR_R);
};
/*For the Logic
  0: White 
  1: Black*/
uint8_t IR::Tracking(){ 
  // switch(task){
    // case default:
      // white black white
    if(L && !M && R)
      return OnTrack;

    // white black black/white white black
    //R_IR on Track 001 & 011 --110/100
    if(((L && M && !R) || (L && !M && !R)) && !task1Flag && !task2Flag){
      return IR_ROnTrack;} 
      //return AllOnTrack;

    // black white white / black black white 
    //L_IR on Track 100 & 110 --011/001
    if( (!L && M && R) || (!L && !M && R)){
      return IR_LOnTrack;}
      //return AllOnTrack;

    // black white black
    //L_IR and R_IR are on Track 101 --010
    if( !L && M && !R){// || (digitalRead(IR_M) && (digitalRead(IR_L)) && (digitalRead(IR_R))))
      return OnTrack;}
      //return AllOnTrack;

    // black black black
    //All on Track 111 --000allwhite stop
    if(!L && !M && !R){
      return SlowOnTrack;}

    // white white white
    //stop at the end: 111 all black
    if(L && M && R){
      return AllOnTrack;}//added stop in the end

    //Task1&2, straight at node2 (only white black black)
    if((L && !M && !R) && (task1Flag==true || task2Flag==true)){
      return OnTrack;}
    //000
    return OnTrack; 
  };

uint8_t IR::Task1(){
  // white black white
  if(L && !M && R)
    return OnTrack;

  // white black black/white white black
  //R_IR on Track 001 & 011 --110/100
  if(((L && M && !R) || (L && !M && !R)) && !task1Flag && !task2Flag){
    return IR_ROnTrack;} 
    //return AllOnTrack;

  // black white white / black black white 
  //L_IR on Track 100 & 110 --011/001
  if( (!L && M && R) || (!L && !M && R)){
    return IR_LOnTrack;}
    //return AllOnTrack;

  // black white black
  //L_IR and R_IR are on Track 101 --010
  if( !L && M && !R){// || (digitalRead(IR_M) && (digitalRead(IR_L)) && (digitalRead(IR_R))))
    return OnTrack;}
    //return AllOnTrack;

  // black black black
  //All on Track 111 --000allwhite stop
  if(!L && !M && !R){
    return SlowOnTrack;}

  // white white white
  //stop at the end: 111 all black
  if(L && M && R){
    return AllOnTrack;}//added stop in the end

  //Task1&2, straight at node2 (only white black black)
  if((L && !M && !R) && task1Flag ){
    return OnTrack;}
  //000
  return OnTrack; 
  };

uint8_t IR::Task2(){
  // white black white
  if(L && !M && R)
    return OnTrack;

  // white black black/white white black
  //R_IR on Track 001 & 011 --110/100
  if(((L && M && !R) || (L && !M && !R)) && !task1Flag && !task2Flag){
    return IR_ROnTrack;} 
    //return AllOnTrack;

  // black white white / black black white 
  //L_IR on Track 100 & 110 --011/001
  if( (!L && M && R) || (!L && !M && R)){
    return IR_LOnTrack;}
    //return AllOnTrack;

  // black white black
  //L_IR and R_IR are on Track 101 --010
  if( !L && M && !R){// || (digitalRead(IR_M) && (digitalRead(IR_L)) && (digitalRead(IR_R))))
    return OnTrack;}
    //return AllOnTrack;

  // black black black
  //All on Track 111 --000allwhite stop
  if(!L && !M && !R){
    return SlowOnTrack;}

  // white white white
  //stop at the end: 111 all black
  if(L && M && R){
    return AllOnTrack;}//added stop in the end

  //Task1&2, straight at node2 (only white black black)
  if((L && !M && !R) && task1Flag ){
    return OnTrack;}
  //000
  return OnTrack; 
  };

  // task3: 10-5-4-7-6/8, with 2-2 traffic light
uint8_t IR::Task3(){
  // white black white
  if(L && !M && R)
    return OnTrack;

  // white black black/white white black
  //R_IR on Track 001 & 011 --110/100
  if((L && M && !R) || (L && !M && !R)){
    return IR_ROnTrack;} 
    //return AllOnTrack;

  // black white white / black black white 
  //L_IR on Track 100 & 110 --011/001
  // node5&4
  if(((!L && M && R) || (!L && !M && R))&&!task3Flag1&&!task3Flag2){
    return IR_LOnTrack;}
    //return AllOnTrack;

  // black white black
  //L_IR and R_IR are on Track 101 --010
  if( !L && M && !R){// || (digitalRead(IR_M) && (digitalRead(IR_L)) && (digitalRead(IR_R))))
    return OnTrack;}
    //return AllOnTrack;

  // black black black
  //All on Track 111 --000allwhite stop
  if((!L && !M && !R) && !task3Flag3_1 && !task3Flag3_2){
    return SlowOnTrack;}

  // at node5: turn left 90 degrees
  if((!L && !M && !R)&&task3Flag1){
    return L_90;}

  // at node4: turn left 45 degrees
  if((!L && !M && R)&&task3Flag1){
    return IR_LOnTrack;}

  // node7_1: turning right for node6
  if((!L && !M && !R) && task3Flag3_1){
    return R_90;}

  // node7_2: turning left for node8
  if((!L && !M && !R) && task3Flag3_2){
    return L_90;}
  //000
  return OnTrack; 
  };
  
uint8_t IR::Task4(){
  // white black white
  if(L && !M && R)
    return OnTrack;

  // white black black/white white black
  //R_IR on Track 001 & 011 --110/100
  if(((L && M && !R) || (L && !M && !R)) && !task4Flag2){
    return IR_ROnTrack;} 
    //return AllOnTrack;

  // black white white / black black white 
  //L_IR on Track 100 & 110 --011/001
  if( (!L && M && R) || (!L && !M && R)){
    return IR_LOnTrack;}
    //return AllOnTrack;

  // black white black
  //L_IR and R_IR are on Track 101 --010
  if(!L && M && !R){// || (digitalRead(IR_M) && (digitalRead(IR_L)) && (digitalRead(IR_R))))
    return OnTrack;}
    //return AllOnTrack;

  // black black black
  //All on Track 111 --000allwhite stop
  if((!L && !M && !R) && !task4Flag1 && !task4Flag3){
    return SlowOnTrack;}

  // white white white
  //stop at the end: 111 all black
  if(L && M && R){
    return AllOnTrack;}//added stop in the end

  // node3: turning left 90 degrees
  if((!L && !M && !R) && task4Flag1){
    return L_90;}
  
  // node4: turning right 135 degrees
  if((L && !M && !R) && task4Flag2){
    return R_135;}

  // node7: walking straight
  if((!L && !M && !R) && task4Flag3){
    return OnTrack;}
  //000
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


