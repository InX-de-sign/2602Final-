#include "Pinout.hpp"
#include "esp32-hal-ledc.h"



/*Pre-Set Data*/

/*Task 3: Simple Blinking Testing Code
  Task 4: Motor Driver Testing Code
  Task 5: Line Tracking Task*/
volatile uint8_t  Task  = 5 ; 

/*You can change the Speed of the Motor*/
volatile uint16_t Speed = 175; // 0 -1024


/*Starting Point Counter*/
volatile bool Start = true; 

/*DO NOT Chnage the code below*/
/*----------------------------------------------------*/
void setup() {
// put your setup code here, to run once:
Serial.begin(115200);
Serial.println("---------Initializing...---------");
//Set up PWM Channel for Motor
Motor::Init();
Serial.println("Wheel Motors Initialized");

//Set up PWM Channel for Servo Motor
Servo::Init();
Serial.println("Servo Motor Initialized");

//Initialize IR Sensor
IR::Init();
Serial.println("IR Sensor Initialized");

//Init LED GPIO Pin 
pinMode(LED1, OUTPUT);
Serial.println("LED GPIO Pin Initialized");

//All the device initialized
Serial.println("---------Initialized---------");
delay(100);

}

/*LED Blinking Function
  To ensure there is visualization that the program is running*/
void blinking(){
  digitalWrite(LED1, HIGH);
  delay(400);
  digitalWrite(LED1, LOW);
  delay(100);
}



void loop() {
/*When the car is on the starting line*/
while(Start && Task !=3){
  if(IR::OnStartingLine()){
    Start = false;  
   Motion::Forwards(400);
   delay(1500);
  }
  else
   Motor::Stop();
}
/*----------------------------------------------------*/
  /*Change the code below*/
  if(Task == 4){
    Serial.println("Moving Forwards...");
    Motion::Forwards(float(Speed+100)); //Speed*0.5f
    delay(500);

    Serial.println("Car Stops...");
    Motor::Stop();
    delay(500);

    /*Make the car turn right for 90 deg */
    Serial.println("Moving Rightwards...");
    Motion::Rightwards(Speed);  
    delay(500);  //Change the duration of delay 

    Serial.println("Car Stops...");
    Motor::Stop();
    delay(500);

    /*Make the car turn left for 90 deg */
    Serial.println("Moving Leftwards...");
    Motion::Leftwards(Speed);
    delay(500);  //Change the duration of delay

    Serial.println("Car Stops...");
    Motor::Stop();
    delay(500);

    Serial.println("Moving Backwards...");
    Motion::Backwards(Speed + 100 );
    delay(500);

    Serial.println("Car Stops...");
    Motor::Stop();
    delay(500);
  }
/*----------------------------------------------------*/
/*DO NOT Chnage the code below*/
  if(Task >=5){
  //Include the Line Tracking Function
  LineTracking::FollowingLine(IR::Tracking(), Speed);
  }

  if(Task < 5)
  blinking();
/*DO NOT Chnage the code above*/
/*----------------------------------------------------*/
}



