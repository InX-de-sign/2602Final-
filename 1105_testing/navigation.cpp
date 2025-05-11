#include "navigation.h"
#include "shared_vars.h"
#include "MotorControl.hpp"
#include <Arduino.h>  // For Serial

namespace Navigation {
  // task1: 9-2-1
  void handleTask1() {
    IR::Task1();
    //Serial.println("Executing Case 1");
    if (isInRegion(getTagUID()) == 2) {
      // String currentTag = getTagUID();
      // if (currentTag == "a0406791" || currentTag == "404b6791" || currentTag == "10d26691"||currentTag =="b03f6791"||currentTag =="30406791"||currentTag =="fa798dbc") {
        Serial.println("Executing Case 1");
        task1Flag=true;
        // vTaskDelay(1000);
      // }
    }

    if(isInRegion(getTagUID()) == 1) {
      task1Flag=false;
      Exam_State=0;
    }
  }


  void handleTask2() {
    IR::Task2();
    if (isInRegion(getTagUID()) == 2) {
      String currentTag = getTagUID();
      Serial.println("Executing Case 2");
      if (currentTag == "a0406791" || currentTag == "404b6791" || currentTag == "10d26691"||currentTag =="b03f6791"||currentTag =="30406791"||currentTag =="fa798dbc") {
        task2Flag=true;
      }
    }
    if(isInRegion(getTagUID()) == 1) {
      task2Flag=false;
      Exam_State=0;
    }
  }


  const uint8_t task3_node6 = 1;
  const uint8_t task3_node8 = 2;

  // route: 10-5-4-7-6/8, with 2-2 traffic light
  void handleTask3(uint8_t sub_case) {
    IR::Task3();
    switch (sub_case) {
      case task3_node6: // ending at node6 (left parking lot)
        Serial.println("Task3-Case1"); 
        if (isInRegion(getTagUID()) == 5) {
          // String currentTag = getTagUID();
          Serial.println("node5_turing left 90 degrees");
          task3Flag1=true;
        }
        if (isInRegion(getTagUID()) == 4) {
          // String currentTag = getTagUID();
          Serial.println("node4_turing left 45 degrees");
          task3Flag1=false;
          task3Flag2=true;
        }  
        if (isInRegion(getTagUID()) == 7) {
          // String currentTag = getTagUID();
          Serial.println("node7_turing right 45 degrees");
          task3Flag2=false;
          task3Flag3_1=true;
        }    
        if(isInRegion(getTagUID()) == 6 || Ultrasonic::GetDistance()<=10) {
          task3Flag3_1=false;
          Exam_State=0;
        } 
        break; 

      case task3_node8: // ending at node8 (right parking lot)
        Serial.println("Task3-Case2"); 
        if (isInRegion(getTagUID()) == 5) {
          // String currentTag = getTagUID();
          Serial.println("node5_turing left 90 degrees");
          task3Flag1=true;
        }
        if (isInRegion(getTagUID()) == 4) {
          // String currentTag = getTagUID();
          Serial.println("node4_turing left 45 degrees");
          task3Flag1=false;
          task3Flag2=true;
        }  
        if (isInRegion(getTagUID()) == 7) {
          // String currentTag = getTagUID();
          Serial.println("node7_turing right 45 degrees");
          task3Flag2=false;
          task3Flag3_2=true;
        }    
        if(isInRegion(getTagUID()) == 8 || Ultrasonic::GetDistance()<=10) {
          task3Flag3_2=false;
          Exam_State=0;
        } 
        break; 
      
      default:
        Serial.println("[ERROR] Invalid main case!");
        break;               
    }           
  }


  const uint8_t task4_node1 = 1;
  const uint8_t task4_node4 = 2;

  void handleTask4(uint8_t sub_case) {
    IR::Task4();
    switch (sub_case) {
      //route: 1-3-4-7-11
      case task4_node1: // starting from node1 
        Serial.println("Task4-Case1"); 
        if (isInRegion(getTagUID()) == 3) {
          // String currentTag = getTagUID();
          Serial.println("node3_turing left 90 degrees");
          task4Flag1=true;
        }
        if (isInRegion(getTagUID()) == 4) {
          // String currentTag = getTagUID();
          Serial.println("node4_turing right 135 degrees");
          task4Flag1=false;
          task4Flag2=true;
        }  
        if (isInRegion(getTagUID()) == 7) {
          // String currentTag = getTagUID();
          Serial.println("node7_walking straight");
          task4Flag2=false;
          task4Flag3=true;
        }    
        if(isInRegion(getTagUID()) == 11) {
          task4Flag3=false;
          Exam_State=0;} 
        break; 

      case task4_node4: // starting from node4
        //route: 4-7-11
        Serial.println("Task4-Case2");  
        if (isInRegion(getTagUID()) == 7) {
          // String currentTag = getTagUID();
          Serial.println("node7_walking straight");
          task4Flag2=false;
          task4Flag3=true;
        }    
        if(isInRegion(getTagUID()) == 11) {
          task4Flag3=false;
          Exam_State=0;
        } 
        break; 

      default:
        Serial.println("[ERROR] Invalid main case!");
        break;
         
    }           
  }

  void handleTask5(uint8_t sub_case) {
    switch (sub_case) {
      case 1: Serial.println("Case 3 - Sub 1"); break;
      case 2: Serial.println("Case 3 - Sub 2"); break;
      default: Serial.println("[ERROR] Case 5 invalid sub!");
    }
  } 
}