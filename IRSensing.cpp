#include "esp32-hal-gpio.h"
#include "IRSensing.hpp"

/*Initialize all the IR sensor Data Pins*/
void IR::Init(){
  pinMode(IR_L,INPUT);
  pinMode(IR_M,INPUT);
  pinMode(IR_R,INPUT);
};
/*For the Logic
  0: White 
  1: Black*/

bool IR::OnStartingLine(){
  if(digitalRead(IR_M) && (digitalRead(IR_L)) && (digitalRead(IR_R))){
    return true; 
  }
  else{
    return false;
  }
}

uint8_t IR::Tracking(){ //!light 
  bool L = digitalRead(IR_L);
  bool M = digitalRead(IR_M);
  bool R = digitalRead(IR_R);
  //M_IR on Track 010
  if(!L && M && !R)
    return OnTrack;
    //return AllOnTrack;
  //R_IR on Track 001 & 011
  if((!L && !M && R) || (!L && M && R)){
    return IR_ROnTrack;}  
    //return AllOnTrack;
  //L_IR on Track 100 & 110
  if( (L && !M && !R) || (L && M && !R)){
    return IR_LOnTrack;}
    //return AllOnTrack;
  //L_IR and R_IR are on Track 101 
  if( L && !M && R){// || (digitalRead(IR_M) && (digitalRead(IR_L)) && (digitalRead(IR_R))))
    return IR_LandROnTrack;}
    //return AllOnTrack;
  //All on Track 111
  if(L && M && R){
    return AllOnTrack;}
  
  //000
  return OutOfTrack; 
};

