#ifndef SHARED_VARS_H
#define SHARED_VARS_H

#include <Arduino.h>
#include <atomic>

// Shared global variables
extern volatile int Exam_State;
extern volatile int Task;
extern volatile int Start_point;
extern volatile int End_point;
extern volatile int Demo_time;   // Time in seconds

extern bool Using_testing_field;

// Shared RFID functions
extern String getTagUID();
extern int isInRegion(const String &rfid);

// Thread-safe boolean flag for triggering tasks in Sensor.cpp
extern std::atomic<bool> task1Flag;
extern std::atomic<bool> task2Flag;

extern std::atomic<bool> task3Flag1;
extern std::atomic<bool> task3Flag2;
extern std::atomic<bool> task3Flag3_1;
extern std::atomic<bool> task3Flag3_2;

extern std::atomic<bool> task4Flag1;
extern std::atomic<bool> task4Flag2;
extern std::atomic<bool> task4Flag3;

extern std::atomic<bool> task5Flag;

#endif