#include "esp32-hal-ledc.h"

#include "MotorControl.hpp"

/*For fine tune the motor bias*/
uint16_t RightSpeedBias      = 0; //100
uint16_t LeftSpeedBias       = 0; //100

/*For extra power to turning Left or Right*/
uint16_t TurnRightExtraSpeed = 225; //250
uint16_t TurnLeftExtraSpeed  = 225; //250

//PWM Setting 
struct PWM_t{ 
uint32_t freq ;
uint8_t resolution; 
uint32_t dutycycle;
} PWM;

PWM_t PWM_Channel_0 = { 2000, 10, 0 };
PWM_t PWM_Channel_1 = { 2000, 10, 0 };
PWM_t PWM_Channel_2 = { 2000, 10, 0 };
PWM_t PWM_Channel_3 = { 2000, 10, 0 };
PWM_t PWM_Channel_4 = { 50, 10, 0 };


void Motor::Init(){

  /*Initialize & attach the Pins to the PWM Channels*/
  ledcAttachChannel(Motor_R_IN1, PWM_Channel_0.freq, PWM_Channel_0.resolution, PWM_CH0);
  ledcAttachChannel(Motor_R_IN2, PWM_Channel_1.freq, PWM_Channel_1.resolution, PWM_CH1);
  ledcAttachChannel(Motor_L_IN1, PWM_Channel_2.freq, PWM_Channel_2.resolution, PWM_CH2);
  ledcAttachChannel(Motor_L_IN2, PWM_Channel_3.freq, PWM_Channel_3.resolution, PWM_CH3);


  /*Initialize the PWM DutyCycle to 0% */
  ledcWrite(Motor_R_IN1, 0);
  ledcWrite(Motor_R_IN2, 0);
  ledcWrite(Motor_L_IN2, 0);
  ledcWrite(Motor_L_IN2, 0);
  
  /*Debug Message*/
  Serial.println("PWM Channel and DutyCycle for Motors Initialized.");

};

void Servo::Init(){
  /*Initialize & attach the Pins to the PWM Channels*/
  ledcAttachChannel(Servo_Pin, PWM_Channel_4.freq, PWM_Channel_4.resolution, PWM_CH4);


  /*Initialize the PWM DutyCycle to 0% */
  ledcWrite(Servo_Pin, 0);

  /*Debug Message*/
  Serial.println("Servo Motor Initialized.");
}
/*For SG90 Servo Motor
  PWM         --> 50Hz  (20ms)
  Dutycycle   --> 1-2ms (5-10%)*/
void Servo::TrunDeg(uint16_t Degree){
  uint16_t Dutycycle = (float(Degree) / 90.0f) * 51.2f + 25.0f ;
  ledcWrite(Servo_Pin, Dutycycle);
  /*For Debug*/
  // Serial.print("Servo Degree: ");
  // Serial.println(Degree);
  // Serial.print("Dutycycle: ");
  // Serial.println(Dutycycle);
};

void Motor::Moving_Clockwise(uint16_t Speed, uint8_t Wheel){
  if(Wheel == 1 ){
    ledcWrite(Motor_R_IN1, Speed);
    ledcWrite(Motor_R_IN2, 0);
    //delay(1);
  }
  if(Wheel == 2){
    ledcWrite(Motor_L_IN1, Speed);
    ledcWrite(Motor_L_IN2, 0);
    //delay(1);
  }
};

void Motor::Moving_AntiClockwise(uint16_t Speed, uint8_t Wheel){
  if(Wheel == 1 ){
    ledcWrite(Motor_R_IN1, 0);
    ledcWrite(Motor_R_IN2, Speed);
    //delay(1);
  }

  if(Wheel == 2){
    ledcWrite(Motor_L_IN1, 0);
    ledcWrite(Motor_L_IN2, Speed);
    //delay(1);
  }
};

void Motor::Stop(){
  //Enable Both IN1 and IN2 to HIGH to Stop the Wheel 
    ledcWrite(Motor_R_IN1, 1024);
    ledcWrite(Motor_R_IN2, 1024);
    ledcWrite(Motor_L_IN1, 1024);
    ledcWrite(Motor_L_IN2, 1024);
    delay(1);
  
};

void Motion::Forwards(uint16_t Speed){
  /*If the two Wheels have bias, adjust one of the speed of the Wheel*/
  Motor::Moving_AntiClockwise(Speed + LeftSpeedBias, LeftWheel);//
  Motor::Moving_AntiClockwise(Speed + RightSpeedBias, RightWheel); //-20 -100

  //Fix the Servo Motor to 90 deg all the time
  Servo::TrunDeg(90);
};

void Motion::Backwards(uint16_t Speed){
  /*If the two Wheels have bias, adjust one of the speed of the Wheel*/
  Motor::Moving_Clockwise(Speed + LeftSpeedBias, LeftWheel);
  Motor::Moving_Clockwise(Speed + RightSpeedBias-50, RightWheel);//

  //Fix the Servo Motor to 90 deg all the time
  Servo::TrunDeg(90);
};  

void Motion::Rightwards(uint16_t Speed){
  /*If the two Wheels have bias, adjust one of the speed of the Wheel*/
  Motor::Moving_AntiClockwise(Speed + RightSpeedBias + TurnRightExtraSpeed, RightWheel );//+300
  Motor::Moving_Clockwise(Speed + LeftSpeedBias + TurnRightExtraSpeed, LeftWheel);//-300

  //Fix the Servo Motor to 135 deg all the time
  Servo::TrunDeg(45);
  
};

void Motion::Leftwards(uint16_t Speed){
  /*If the two Wheels have bias, adjust one of the speed of the Wheel*/
  Motor::Moving_Clockwise(Speed + RightSpeedBias + TurnLeftExtraSpeed+100, RightWheel);//-100
  Motor::Moving_AntiClockwise(Speed + LeftSpeedBias + TurnLeftExtraSpeed+500, LeftWheel);//0//100

  //Fix the Servo Motor to 45 deg all the time
  Servo::TrunDeg(135);
};