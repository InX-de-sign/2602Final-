#include "esp32-hal-ledc.h"
#include "MotorControl.hpp"

/*For fine tune the motor bias*/
uint16_t RightSpeedBias = 0; 
uint16_t LeftSpeedBias = 0;   // 110

/*For extra power to turning Left or Right*/
uint16_t TurnRightExtraSpeed = 0; // 250
uint16_t TurnLeftExtraSpeed = 300;  // 250

// PWM Setting
struct PWM_t
{
  uint32_t freq;
  uint8_t resolution;
  uint32_t dutycycle;
} PWM;

PWM_t PWM_Channel_0 = {2000, 10, 0};
PWM_t PWM_Channel_1 = {2000, 10, 0};
PWM_t PWM_Channel_2 = {2000, 10, 0};
PWM_t PWM_Channel_3 = {2000, 10, 0};
PWM_t PWM_Channel_4 = {50, 10, 0};

void Motor::Init()
{

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

void Servo::Init()
{
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
void Servo::TurnDeg(uint16_t Degree)
{
  uint16_t Dutycycle = (float(Degree) / 90.0f) * 51.2f + 25.0f;
  ledcWrite(Servo_Pin, Dutycycle);
  /*For Debug*/
  // Serial.print("Servo Degree: ");
  // Serial.println(Degree);
  // Serial.print("Dutycycle: ");
  // Serial.println(Dutycycle);
};

void Motor::Moving_Clockwise(uint16_t LeftSpeed,uint16_t RightSpeed, uint8_t Wheel)
{
  if (Wheel == 1)
  {
    ledcWrite(Motor_R_IN1, RightSpeed);
    ledcWrite(Motor_R_IN2, 0);
    // delay(1);
  }
  if (Wheel == 2)
  {
    ledcWrite(Motor_L_IN1, LeftSpeed);
    ledcWrite(Motor_L_IN2, 0);
    // delay(1);
  }
};

void Motor::Moving_AntiClockwise(uint16_t LeftSpeed,uint16_t RightSpeed, uint8_t Wheel)
{
  if (Wheel == LeftWheel) //rightwheel
  {
    ledcWrite(Motor_R_IN1, 0);
    ledcWrite(Motor_R_IN2, RightSpeed);
    // delay(1);
  }

  if (Wheel == LeftWheel) //leftwheel
  {
    ledcWrite(Motor_L_IN1, 0);
    ledcWrite(Motor_L_IN2, LeftSpeed);
    // delay(1);
  }
};

void Motor::Stop()
{
  // Enable Both IN1 and IN2 to HIGH to Stop the Wheel
  ledcWrite(Motor_R_IN1, 1024);
  ledcWrite(Motor_R_IN2, 1024);
  ledcWrite(Motor_L_IN1, 1024);
  ledcWrite(Motor_L_IN2, 1024);
  delay(1);
};

float Motor::RPMtoPWM(float TargetRPM, uint8_t Wheel)
{
  float TargetPWM = 175.0f;
  /*Be Awared of 2 Motor may have a different PWM and RPM ratio*/
  switch (Wheel)
  {
  case LeftWheel:
    /*Find the math relationship
      it's not a linear relationship
      But can make the estimate value by 2 - 3 range and apply linear estimation*/
    // TargetPWM = ((TargetRPM - 400.0f) / 20.0f) * 60.0f; // need to test
    // TargetPWM = (TargetRPM*3.94f-125.5f); // need to test
    if( TargetRPM > 15){
        TargetPWM = (TargetRPM - 15) * 100;}
      
     else if (TargetRPM < 15 && TargetRPM > 5) {
      // TargetPWM = (TargetRPM - 1) * 10;
      TargetPWM = (TargetRPM - 1) * 5.13f;
     }
     return TargetPWM;
     break;
    //TargetPWM = constrain(TargetRPM * 10.0f + 150.0f, 0.0f, 1024.0f);
    // TargetPWM=TargetRPM;



  case RightWheel:
    // TargetPWM = ((TargetRPM - 400.0f) / 20.0f) * 60.0f; // need to test
    // TargetPWM = (abs(TargetRPM)*3.67f-290.5f); // need to test
    // TargetPWM = (TargetRPM*3.67f-290.5f); // need to test //offset=12
    // TargetPWM=TargetRPM;
    if( TargetRPM > 15){
      TargetPWM = (TargetRPM - 15) * 100;}
    else if (TargetRPM < 15 && TargetRPM > 5) {
      TargetPWM = (TargetRPM - 1) * 20;
    }
    return TargetPWM;
    break;
  }
  return TargetPWM;
};

void Motion::Forwards(uint16_t LeftSpeed,uint16_t RightSpeed)
{
  /*If the two Wheels have bias, adjust one of the speed of the Wheel*/
  Motor::Moving_AntiClockwise(LeftSpeed + LeftSpeedBias, RightSpeed + RightSpeedBias, LeftWheel);   
  Motor::Moving_AntiClockwise(LeftSpeed + LeftSpeedBias, RightSpeed + RightSpeedBias, RightWheel);   //
  // Motor::Moving_AntiClockwise(RightSpeed + RightSpeedBias, RightWheel); //-20 -100
  // Fix the Servo Motor to 90 deg all the time
  Servo::TurnDeg(90);
};

void Motion::Backwards(uint16_t LeftSpeed,uint16_t RightSpeed)
{
  /*If the two Wheels have bias, adjust one of the speed of the Wheel*/
  Motor::Moving_Clockwise(LeftSpeed + LeftSpeedBias, RightSpeed + RightSpeedBias,LeftWheel);
  Motor::Moving_Clockwise(LeftSpeed + LeftSpeedBias,RightSpeed + RightSpeedBias, RightWheel); //
  // Fix the Servo Motor to 90 deg all the time
  Servo::TurnDeg(90);
};

void Motion::Leftwards(uint16_t LeftSpeed,uint16_t RightSpeed)
{
  /*If the two Wheels have bias, adjust one of the speed of the Wheel*/
  Motor::Moving_AntiClockwise(LeftSpeed + LeftSpeedBias+TurnLeftExtraSpeed, RightSpeed + RightSpeedBias + TurnRightExtraSpeed+300, RightWheel); //+300
  Motor::Moving_Clockwise(LeftSpeed + LeftSpeedBias + TurnLeftExtraSpeed+300,RightSpeed + RightSpeedBias + TurnRightExtraSpeed, LeftWheel);       //-300
  // Fix the Servo Motor to 135 deg all the time
  Servo::TurnDeg(45);
};

void Motion::Rightwards(uint16_t LeftSpeed,uint16_t RightSpeed)
{
  //Serial.println("Motion::Rightwards");
  /*If the two Wheels have bias, adjust one of the speed of the Wheel*/
  Motor::Moving_Clockwise(LeftSpeed + LeftSpeedBias + TurnLeftExtraSpeed, RightSpeed + RightSpeedBias + TurnRightExtraSpeed-100, RightWheel);   //-100
  Motor::Moving_AntiClockwise(LeftSpeed + LeftSpeedBias + TurnLeftExtraSpeed+100, RightSpeed + RightSpeedBias + TurnRightExtraSpeed,LeftWheel); // 0//100
  // Fix the Servo Motor to 45 deg all the time
  Servo::TurnDeg(135);
}

void Motion::Rightwards_90(uint16_t LeftSpeed,uint16_t RightSpeed)
{
  /*If the two Wheels have bias, adjust one of the speed of the Wheel*/
  Motor::Moving_Clockwise(LeftSpeed + LeftSpeedBias + TurnLeftExtraSpeed,RightSpeed + RightSpeedBias + TurnRightExtraSpeed, RightWheel);   //-100
  Motor::Moving_AntiClockwise(LeftSpeed + LeftSpeedBias + TurnLeftExtraSpeed, RightSpeed + RightSpeedBias + TurnRightExtraSpeed, LeftWheel); // 0//100
  // Fix the Servo Motor to 45 deg all the time
  Servo::TurnDeg(180);
}

void Motion::Leftwards_90(uint16_t LeftSpeed,uint16_t RightSpeed)
{
  /*If the two Wheels have bias, adjust one of the speed of the Wheel*/
  Motor::Moving_AntiClockwise(LeftSpeed + LeftSpeedBias + TurnLeftExtraSpeed,RightSpeed + RightSpeedBias + TurnRightExtraSpeed, RightWheel); //+300
  Motor::Moving_Clockwise(LeftSpeed + LeftSpeedBias + TurnLeftExtraSpeed,RightSpeed + RightSpeedBias + TurnRightExtraSpeed, LeftWheel);       //-300
  // Fix the Servo Motor to 135 deg all the time
  Servo::TurnDeg(0);
}

void Motion::Rightwards_135(uint16_t LeftSpeed,uint16_t RightSpeed)
{
  /*If the two Wheels have bias, adjust one of the speed of the Wheel*/
  Motor::Moving_Clockwise(LeftSpeed + LeftSpeedBias + TurnLeftExtraSpeed,RightSpeed + RightSpeedBias + TurnRightExtraSpeed, RightWheel);   //-100
  Motor::Moving_AntiClockwise(LeftSpeed + LeftSpeedBias + TurnLeftExtraSpeed,RightSpeed + RightSpeedBias + TurnRightExtraSpeed, LeftWheel); // 0//100
  // Fix the Servo Motor to 45 deg all the time
  Servo::TurnDeg(90);
  // Servo::TurnDeg(135);
}

void Motion::Leftwards_135(uint16_t LeftSpeed,uint16_t RightSpeed)
{
  /*If the two Wheels have bias, adjust one of the speed of the Wheel*/
  Motor::Moving_AntiClockwise(LeftSpeed + LeftSpeedBias + TurnLeftExtraSpeed,RightSpeed + RightSpeedBias + TurnRightExtraSpeed, RightWheel); //+300
  Motor::Moving_Clockwise(LeftSpeed + LeftSpeedBias + TurnLeftExtraSpeed,RightSpeed + RightSpeedBias + TurnRightExtraSpeed, LeftWheel);       //-300
  // Fix the Servo Motor to 135 deg all the time
  Servo::TurnDeg(0);
  Servo::TurnDeg(45);
};