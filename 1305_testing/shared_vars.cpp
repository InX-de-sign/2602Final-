#include "shared_vars.h"

/*Exam Firebase Data*/
volatile uint16_t Speed = 110; //only one speed, from lab5; applicable to LineTracking, MotorControl funcions
volatile int Exam_State = 0;  // 0 = Stopped || 1 = Started || 2 = Paused
volatile int Demo_time = 0;   // Time in seconds
volatile int Start_point = 0;
volatile int End_point = 0;
volatile int Task = 0;

// global config
bool Using_testing_field = true;

// Define the atomic flag (default: false)
std::atomic<bool> task1Flag(false);
std::atomic<bool> endTask1(false);

std::atomic<bool> task2Flag(false);
std::atomic<bool> endTask2(false);

std::atomic<bool> task3Flag1(false);
std::atomic<bool> task3Flag2(false);
std::atomic<bool> task3Flag3_1(false);
std::atomic<bool> task3Flag3_2(false);
std::atomic<bool> endTask3(false);

std::atomic<bool> task4Flag1(false);
std::atomic<bool> task4Flag2(false);
std::atomic<bool> task4Flag3(false);
std::atomic<bool> endTask4(false);

std::atomic<bool> task5Flag(false);
std::atomic<bool> endTask5(false);