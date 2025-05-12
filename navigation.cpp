#include "navigation.h"
#include "shared_vars.h"
#include "MotorControl.hpp"
#include "LineTracking.hpp"
#include <Arduino.h>  // For Serial

namespace Navigation {
  // task1: 9-2-1
  void handleTask1() {
    //Serial.println("Task1");
    LineTracking::FollowingLine(IR::Task1(), Speed);
    //Serial.println("Executing Case 1");
    if (isInRegion(getTagUID()) == 2) {
      // String currentTag = getTagUID();
      // if (currentTag == "a0406791" || currentTag == "404b6791" || currentTag == "10d26691"||currentTag =="b03f6791"||currentTag =="30406791"||currentTag =="fa798dbc") {
        Serial.println("Executing Case 1");
        task1Flag=true;
      // }
    }

    if(isInRegion(getTagUID()) == 1) {
      task1Flag=false;
      Serial.println("Car shall be stopping");
      LineTracking::stop();
      Exam_State=0;
    }
  }


  void handleTask2() {
    LineTracking::FollowingLine(IR::Task2(), Speed);
    if (isInRegion(getTagUID()) == 2) {
      // String currentTag = getTagUID();
      Serial.println("Executing Case 2");
      // if (currentTag == "a0406791" || currentTag == "404b6791" || currentTag == "10d26691"||currentTag =="b03f6791"||currentTag =="30406791"||currentTag =="fa798dbc") {
        task2Flag=true;
      }

    if(isInRegion(getTagUID()) == 1) {
      task2Flag=false;
      LineTracking::stop();      
      Exam_State=0;
    }
  }


  const uint8_t task3_node6 = 1;
  const uint8_t task3_node8 = 2;

  // route: 10-5-4-7-6/8, with 2-2 traffic light
  void handleTask3(uint8_t sub_case) {
    LineTracking::FollowingLine(IR::Task3(), Speed);
    switch (sub_case) {
      case task3_node6: // ending at node6 (left parking lot)
        Serial.println("Task3-Case1"); 
        if (isInRegion(getTagUID()) == 5) {
          // String currentTag = getTagUID();
          Serial.println("node5_turing left 90 degrees");
          task3Flag1=true;

          // //dealing with Intersect2-Traffic Light2
          // if(intersectionLights.intersectionLights[3].state==0){
          //   LineTracking::stop();
          //   if(intersectionLights.intersectionLights[3].state==1){
          //     LineTracking::FollowingLine(IR::Task3(), Speed);
          //   }
          // }
          // if(intersectionLights.intersectionLights[3].state==2){
          //   LineTracking::FollowingLine(IR::Task3(), Speed-30);
          // }
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
          LineTracking::stop();  
        } 
        break; 

      case task3_node8: // ending at node8 (right parking lot)
        Serial.println("Task3-Case2"); 
        if (isInRegion(getTagUID()) == 5) {
          // String currentTag = getTagUID();
          Serial.println("node5_turing left 90 degrees");
          task3Flag1=true;

          // //dealing with Intersect2-Traffic Light2
          // if(intersectionLights.intersectionLights[3].state==0){
          //   LineTracking::stop();
          //   if(intersectionLights.intersectionLights[3].state==1){
          //     LineTracking::FollowingLine(IR::Task3(), Speed);
          //   }
          // }
          // if(intersectionLights.intersectionLights[3].state==2){
          //   LineTracking::FollowingLine(IR::Task3(), Speed-30);
          // }
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
          LineTracking::stop();  
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
    LineTracking::FollowingLine(IR::Task4(), Speed);
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

          // //dealing with Intersect5-Traffic Light1
          // if(intersectionLights.intersectionLights[8].state==0){
          //   LineTracking::stop();
          //   if(intersectionLights.intersectionLights[8].state==1){
          //     LineTracking::FollowingLine(IR::Task3(), Speed);
          //   }
          // }
          // if(intersectionLights.intersectionLights[8].state==2){
          //   LineTracking::FollowingLine(IR::Task3(), Speed-30);
          // }
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

          // //dealing with Intersect5-Traffic Light1
          // if(intersectionLights.intersectionLights[8].state==0){
          //   LineTracking::stop();
          //   if(intersectionLights.intersectionLights[8].state==1){
          //     LineTracking::FollowingLine(IR::Task3(), Speed);
          //   }
          // }
          // if(intersectionLights.intersectionLights[8].state==2){
          //   LineTracking::FollowingLine(IR::Task3(), Speed-30);
          // }
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

  Path OPTIMAL_PATHS[MAX_PATHS] = {
    // Paths from Node 1
    {1, 4, {1, 3, 4}, 3, 12},
    {1, 6, {1, 3, 4, 7, 6}, 5, 27},
    {1, 7, {1, 3, 4, 7}, 4, 19},
    {1, 8, {1, 3, 4, 7, 8}, 5, 24},
    {1, 9, {1, 2, 9}, 3, 30},
    {1, 10, {1, 5, 10}, 3, 37},
    {1, 11, {1, 3, 4, 7, 11}, 5, 35},

    {2, 4, {2, 3, 4}, 3, 15},
    {2, 5, {2, 3, 4, 5}, 4, 26},
    {2, 6, {2, 3, 4, 7, 6}, 5, 30},
    {2, 7, {2, 3, 4, 7}, 4, 22},
    {2, 8, {2, 3, 4, 7, 8}, 5, 27},
    {2, 10, {2, 9, 10}, 3, 40},
    {2, 11, {2, 9, 11}, 3, 36},

    {3, 5, {3, 4, 5}, 3, 16},
    {3, 6, {3, 4, 7, 6}, 4, 20},
    {3, 7, {3, 4, 7}, 3, 12},
    {3, 8, {3, 4, 7, 8}, 4, 17},
    {3, 9, {3, 2, 9}, 3, 26},
    {3, 10, {3, 4, 5, 10}, 4, 30},
    {3, 11, {3, 4, 7, 11}, 4, 28},

    {4, 1, {4, 3, 1}, 3, 12},
    {4, 2, {4, 3, 2}, 3, 15},
    {4, 6, {4, 7, 6}, 3, 15},
    {4, 8, {4, 7, 8}, 3, 12},
    {4, 9, {4, 3, 2, 9}, 4, 31},
    {4, 10, {4, 5, 10}, 3, 25},
    {4, 11, {4, 7, 11}, 3, 23},

    {5, 2, {5, 4, 3, 2}, 4, 26},
    {5, 3, {5, 4, 3}, 3, 16},
    {5, 6, {5, 4, 7, 6}, 4, 26},
    {5, 7, {5, 4, 7}, 3, 18},
    {5, 8, {5, 4, 7, 8}, 4, 23},
    {5, 9, {5, 10, 9}, 3, 38},
    {5, 11, {5, 10, 11}, 3, 34},

    {7, 1, {7, 4, 3, 1}, 4, 19},
    {7, 2, {7, 4, 3, 2}, 4, 22},
    {7, 3, {7, 4, 3}, 3, 12},
    {7, 5, {7, 4, 5}, 3, 18},
    {7, 9, {7, 11, 9}, 3, 36},
    {7, 10, {7, 4, 5, 10}, 4, 32},

    {9, 1, {9, 2, 1}, 3, 30},
    {9, 3, {9, 2, 3}, 3, 26},
    {9, 4, {9, 2, 3, 4}, 4, 31},
    {9, 5, {9, 10, 5}, 3, 38},
    {9, 6, {9, 11, 7, 6}, 4, 44},
    {9, 7, {9, 11, 7}, 3, 36},
    {9, 8, {9, 11, 7, 8}, 4, 41},

    {10, 1, {10, 5, 1}, 3, 37},
    {10, 2, {10, 9, 2}, 3, 40},
    {10, 3, {10, 5, 4, 3}, 4, 30},
    {10, 4, {10, 5, 4}, 3, 25},
    {10, 6, {10, 5, 4, 7, 6}, 5, 40},
    {10, 7, {10, 5, 4, 7}, 4, 32},
    {10, 8, {10, 5, 4, 7, 8}, 5, 37},

    {11, 1, {11, 7, 4, 3, 1}, 5, 35},
    {11, 2, {11, 9, 2}, 3, 36},
    {11, 3, {11, 7, 4, 3}, 4, 28},
    {11, 4, {11, 7, 4}, 3, 23},
    {11, 5, {11, 10, 5}, 3, 34},
    {11, 6, {11, 7, 6}, 3, 24},
    {11, 8, {11, 7, 8}, 3, 21}
  };

  const int NUM_PATHS = sizeof(OPTIMAL_PATHS) / sizeof(Path);

  Path* getOptimalPath(uint8_t start, uint8_t end) {
    for(int i = 0; i < NUM_PATHS; i++) {
      if(OPTIMAL_PATHS[i].start == start && OPTIMAL_PATHS[i].end == end) {
        return &OPTIMAL_PATHS[i];
      }
    } 
    return nullptr;
  }

    void navigatePath(const Path& path) {
        for(uint8_t i = 0; i < path.length - 1; i++) {
            uint8_t current = path.nodes[i];      // Access nodes array
            uint8_t next = path.nodes[i + 1];    // Access nodes array
            
            // Determine which node condition to activate based on current and next node
            String nodeName = "node" + String(current) + "_";
            
            // Find and execute the appropriate node condition
            for(int j = 0; j < TOTAL_NODES_CONDITIONS; j++) {
                if(strstr(ALL_NODE_CONDITIONS[j].name, nodeName.c_str()) != NULL) {
                    // Additional logic to determine exact condition needed
                    ALL_NODE_CONDITIONS[j].action();
                    break;
                }
            }
        }
    }

  // // Example usage function
  // void navigateToNode(uint8_t start, uint8_t end) {
  //     Path path;
  //     if(getOptimalPath(start, end, path)) {
  //         navigatePath(path);
  //     } else {
  //         Serial.println("No path found!");
  //     }
  // }

}


NodeCondition ALL_NODE_CONDITIONS[54] = {
  {false, "node1_1", []() {LineTracking::FollowingLine(8, Speed);}}, // 5-1-3 left
  {false, "node1_2", []() {LineTracking::FollowingLine(1, Speed);}}, // 5-1-2 straight
  {false, "node1_3", []() {LineTracking::FollowingLine(7, Speed);}}, // 3-1-5 right
  {false, "node1_4", []() {LineTracking::FollowingLine(8, Speed);}}, // 3-1-2 left
  {false, "node1_5", []() {LineTracking::FollowingLine(1, Speed);}}, // 2-1-5 straight
  {false, "node1_6", []() {LineTracking::FollowingLine(7, Speed);}}, // 2-1-3 right

  {false, "node2_1", []() {LineTracking::FollowingLine(10, Speed);}}, // 1-2-3 L_135
  {false, "node2_2", []() {LineTracking::FollowingLine(1, Speed);}}, // 1-2-9 straight
  {false, "node2_3", []() {LineTracking::FollowingLine(9, Speed);}}, // 3-2-1 R_135
  {false, "node2_4", []() {LineTracking::FollowingLine(3, Speed);}}, // 3-2-9 L_45
  {false, "node2_5", []() {LineTracking::FollowingLine(1, Speed);}}, // 9-2-1 straight
  {false, "node2_6", []() {LineTracking::FollowingLine(2, Speed);}}, // 9-2-3 R_45

  {false, "node3_1", []() {LineTracking::FollowingLine(8, Speed);}}, // 1-3-4 L_90
  {false, "node3_2", []() {LineTracking::FollowingLine(7, Speed);}}, // 1-3-2 R_90
  {false, "node3_3", []() {LineTracking::FollowingLine(7, Speed);}}, // 4-3-1 R_90
  {false, "node3_4", []() {LineTracking::FollowingLine(1, Speed);}}, // 4-3-2 straight
  {false, "node3_5", []() {LineTracking::FollowingLine(8, Speed);}}, // 2-3-1 L_90
  {false, "node3_6", []() {LineTracking::FollowingLine(1, Speed);}}, // 2-3-4 straight

  {false, "node4_1", []() {LineTracking::FollowingLine(3, Speed);}}, // 5-4-7 L_45
  {false, "node4_2", []() {LineTracking::FollowingLine(1, Speed);}}, // 5-4-3 straight
  {false, "node4_3", []() {LineTracking::FollowingLine(2, Speed);}}, // 7-4-5 R_45
  {false, "node4_4", []() {LineTracking::FollowingLine(9, Speed);}}, // 7-4-3 L_135
  {false, "node4_5", []() {LineTracking::FollowingLine(1, Speed);}}, // 3-4-5 straight
  {false, "node4_6", []() {LineTracking::FollowingLine(9, Speed);}}, // 3-4-7 R_135

  {false, "node5_1", []() {LineTracking::FollowingLine(1, Speed);}}, // 1-5-10 straight
  {false, "node5_2", []() {LineTracking::FollowingLine(7, Speed);}}, // 1-5-4 R_90
  {false, "node5_3", []() {LineTracking::FollowingLine(1, Speed);}}, // 10-5-1 straight
  {false, "node5_4", []() {LineTracking::FollowingLine(8, Speed);}}, // 10-5-4 L_90
  {false, "node5_5", []() {LineTracking::FollowingLine(8, Speed);}}, // 4-5-1 L_90
  {false, "node5_6", []() {LineTracking::FollowingLine(7, Speed);}}, // 4-5-10 R_90

  {false, "node7_1", []() {LineTracking::FollowingLine(8, Speed);}}, // 4-7-8 L_90
  {false, "node7_2", []() {LineTracking::FollowingLine(1, Speed);}}, // 4-7-11 straight
  {false, "node7_3", []() {LineTracking::FollowingLine(7, Speed);}}, // 4-7-6 R_90
  {false, "node7_4", []() {LineTracking::FollowingLine(1, Speed);}}, // 11-7-4 straight
  {false, "node7_5", []() {LineTracking::FollowingLine(7, Speed);}}, // 11-7-8 R_90
  {false, "node7_6", []() {LineTracking::FollowingLine(8, Speed);}}, // 11-7-6 L_90

  {false, "node9_1", []() {LineTracking::FollowingLine(8, Speed);}}, // 2-9-10 L_90
  {false, "node9_2", []() {LineTracking::FollowingLine(1, Speed);}}, // 2-9-11 straight
  {false, "node9_3", []() {LineTracking::FollowingLine(7, Speed);}}, // 10-9-2 R_90
  {false, "node9_4", []() {LineTracking::FollowingLine(8, Speed);}}, // 10-9-11 L_90
  {false, "node9_5", []() {LineTracking::FollowingLine(1, Speed);}}, // 11-9-2 straight
  {false, "node9_6", []() {LineTracking::FollowingLine(7, Speed);}}, // 11-9-10 R_90

  {false, "node10_1", []() {LineTracking::FollowingLine(1, Speed);}}, // 5-10-11 straight
  {false, "node10_2", []() {LineTracking::FollowingLine(7, Speed);}}, // 5-10-9 R_90
  {false, "node10_3", []() {LineTracking::FollowingLine(1, Speed);}}, // 11-10-5 straight
  {false, "node10_4", []() {LineTracking::FollowingLine(8, Speed);}}, // 11-10-9 L_90
  {false, "node10_5", []() {LineTracking::FollowingLine(8, Speed);}}, // 9-10-5 L_90
  {false, "node10_6", []() {LineTracking::FollowingLine(7, Speed);}}, // 9-10-11 R_90

  {false, "node11_1", []() {LineTracking::FollowingLine(8, Speed);}}, // 7-11-10 L_90
  {false, "node11_2", []() {LineTracking::FollowingLine(7, Speed);}}, // 7-11-9 R_90
  {false, "node11_3", []() {LineTracking::FollowingLine(7, Speed);}}, // 10-11-7 R_90
  {false, "node11_4", []() {LineTracking::FollowingLine(1, Speed);}}, // 10-11-9 straight
  {false, "node11_5", []() {LineTracking::FollowingLine(8, Speed);}}, // 9-11-7 L_90
  {false, "node11_6", []() {LineTracking::FollowingLine(1, Speed);}}, // 9-11-10 straight
};

namespace Navigation{
//   enum PathType {
//     P1_4, P1_6, P1_7, P1_8, P1_9, P1_10, P1_11,
//     P2_4, P2_5, P2_6, P2_7, P2_8, P2_10, P2_11,
//     P3_5, P3_6, P3_7, P3_8, P3_9, P3_10, P3_11,
//     P4_1, P4_2, P4_6, P4_8, P4_9, P4_10, P4_11,
//     P5_2, P5_3, P5_6, P5_7, P5_8, P5_9, P5_11,
//     P7_1, P7_2, P7_3, P7_5, P7_9, P7_10,
//     P9_1, P9_3, P9_4, P9_5, P9_6, P9_7, P9_8,
//     P10_1, P10_2, P10_3, P10_4, P10_6, P10_7, P10_8,
//     P11_1, P11_2, P11_3, P11_4, P11_5, P11_6, P11_8
// };

  void handleTask5(uint8_t sub_case){
    PathType pathType = static_cast<PathType>(sub_case);
    switch (pathType) {
        case P1_4: {
            Path* path = getOptimalPath(1, 4);
            if (path) {
                navigatePath(*path);
            }
            break;
        }
        case P1_6: {
            Path* path = getOptimalPath(1, 6);
            if (path) {
                navigatePath(*path);
            }
            break;
        }
        case P1_7: {
            Path* path = getOptimalPath(1, 7);
            if (path) {
                navigatePath(*path);
            }
            break;
        }
        case P1_8: {
            Path* path = getOptimalPath(1, 8);
            if (path) {
                navigatePath(*path);
            }
            break;
        }
        case P1_9: {
            Path* path = getOptimalPath(1, 9);
            if (path) {
                navigatePath(*path);
            }
            break;
        }
        case P1_10: {
            Path* path = getOptimalPath(1, 10);
            if (path) {
                navigatePath(*path);
            }
            break;
        }
        case P1_11: {
            Path* path = getOptimalPath(1, 11);
            if (path) {
                navigatePath(*path);
            }
            break;
        }
        case P2_4: {
            Path* path = getOptimalPath(2, 4);
            if (path) {
                navigatePath(*path);
            }
            break;
        }
        case P2_5: {
            Path* path = getOptimalPath(2, 5);
            if (path) {
                navigatePath(*path);
            }
            break;
        }
        case P2_6: {
            Path* path = getOptimalPath(2, 6);
            if (path) {
                navigatePath(*path);
            }
            break;
        }
        case P2_7: {
            Path* path = getOptimalPath(2, 7);
            if (path) {
                navigatePath(*path);
            }
            break;
        }
        case P2_8: {
            Path* path = getOptimalPath(2, 8);
            if (path) {
                navigatePath(*path);
            }
            break;
        }
        case P2_10: {
            Path* path = getOptimalPath(2, 10);
            if (path) {
                navigatePath(*path);
            }
            break;
        }
        case P2_11: {
            Path* path = getOptimalPath(2, 11);
            if (path) {
                navigatePath(*path);
            }
            break;
        }
        case P3_5: {
            Path* path = getOptimalPath(3, 5);
            if (path) {
                navigatePath(*path);
            }
            break;
        }
        case P3_6: {
            Path* path = getOptimalPath(3, 6);
            if (path) {
                navigatePath(*path);
            }
            break;
        }
        case P3_7: {
            Path* path = getOptimalPath(3, 7);
            if (path) {
                navigatePath(*path);
            }
            break;
        }
        case P3_8: {
            Path* path = getOptimalPath(3, 8);
            if (path) {
                navigatePath(*path);
            }
            break;
        }
        case P3_9: {
            Path* path = getOptimalPath(3, 9);
            if (path) {
                navigatePath(*path);
            }
            break;
        }
        case P3_10: {
            Path* path = getOptimalPath(3, 10);
            if (path) {
                navigatePath(*path);
            }
            break;
        }
        case P3_11: {
            Path* path = getOptimalPath(3, 11);
            if (path) {
                navigatePath(*path);
            }
            break;
        }
        case P4_1: {
            Path* path = getOptimalPath(4, 1);
            if (path) {
                navigatePath(*path);
            }
            break;
        }
        case P4_2: {
            Path* path = getOptimalPath(4, 2);
            if (path) {
                navigatePath(*path);
            }
            break;
        }
        case P4_6: {
            Path* path = getOptimalPath(4, 6);
            if (path) {
                navigatePath(*path);
            }
            break;
        }
        case P4_8: {
            Path* path = getOptimalPath(4, 8);
            if (path) {
                navigatePath(*path);
            }
            break;
        }
        case P4_9: {
            Path* path = getOptimalPath(4, 9);
            if (path) {
                navigatePath(*path);
            }
            break;
        }
        case P4_10: {
            Path* path = getOptimalPath(4, 10);
            if (path) {
                navigatePath(*path);
            }
            break;
        }
        case P4_11: {
            Path* path = getOptimalPath(4, 11);
            if (path) {
                navigatePath(*path);
            }
            break;
        }
        case P5_2: {
            Path* path = getOptimalPath(5, 2);
            if (path) {
                navigatePath(*path);
            }
            break;
        }
        case P5_3: {
            Path* path = getOptimalPath(5, 3);
            if (path) {
                navigatePath(*path);
            }
            break;
        }
        case P5_6: {
            Path* path = getOptimalPath(5, 6);
            if (path) {
                navigatePath(*path);
            }
            break;
        }
        case P5_7: {
            Path* path = getOptimalPath(5, 7);
            if (path) {
                navigatePath(*path);
            }
            break;
        }
        case P5_8: {
            Path* path = getOptimalPath(5, 8);
            if (path) {
                navigatePath(*path);
            }
            break;
        }
        case P5_9: {
            Path* path = getOptimalPath(5, 9);
            if (path) {
                navigatePath(*path);
            }
            break;
        }
        case P5_11: {
            Path* path = getOptimalPath(5, 11);
            if (path) {
                navigatePath(*path);
            }
            break;
        }
        case P7_1: {
            Path* path = getOptimalPath(7, 1);
            if (path) {
                navigatePath(*path);
            }
            break;
        }
        case P7_2: {
            Path* path = getOptimalPath(7, 2);
            if (path) {
                navigatePath(*path);
            }
            break;
        }
        case P7_3: {
            Path* path = getOptimalPath(7, 3);
            if (path) {
                navigatePath(*path);
            }
            break;
        }
        case P7_5: {
            Path* path = getOptimalPath(7, 5);
            if (path) {
                navigatePath(*path);
            }
            break;
        }
        case P7_9: {
            Path* path = getOptimalPath(7, 9);
            if (path) {
                navigatePath(*path);
            }
            break;
        }
        case P7_10: {
            Path* path = getOptimalPath(7, 10);
            if (path) {
                navigatePath(*path);
            }
            break;
        }
        case P9_1: {
            Path* path = getOptimalPath(9, 1);
            if (path) {
                navigatePath(*path);
            }
            break;
        }
        case P9_3: {
            Path* path = getOptimalPath(9, 3);
            if (path) {
                navigatePath(*path);
            }
            break;
        }
        case P9_4: {
            Path* path = getOptimalPath(9, 4);
            if (path) {
                navigatePath(*path);
            }
            break;
        }
        case P9_5: {
            Path* path = getOptimalPath(9, 5);
            if (path) {
                navigatePath(*path);
            }
            break;
        }
        case P9_6: {
            Path* path = getOptimalPath(9, 6);
            if (path) {
                navigatePath(*path);
            }
            break;
        }
        case P9_7: {
            Path* path = getOptimalPath(9, 7);
            if (path) {
                navigatePath(*path);
            }
            break;
        }
        case P9_8: {
            Path* path = getOptimalPath(9, 8);
            if (path) {
                navigatePath(*path);
            }
            break;
        }
        case P10_1: {
            Path* path = getOptimalPath(10, 1);
            if (path) {
                navigatePath(*path);
            }
            break;
        }
        case P10_2: {
            Path* path = getOptimalPath(10, 2);
            if (path) {
                navigatePath(*path);
            }
            break;
        }
        case P10_3: {
            Path* path = getOptimalPath(10, 3);
            if (path) {
                navigatePath(*path);
            }
            break;
        }
        case P10_4: {
            Path* path = getOptimalPath(10, 4);
            if (path) {
                navigatePath(*path);
            }
            break;
        }
        case P10_6: {
            Path* path = getOptimalPath(10, 6);
            if (path) {
                navigatePath(*path);
            }
            break;
        }
        case P10_7: {
            Path* path = getOptimalPath(10, 7);
            if (path) {
                navigatePath(*path);
            }
            break;
        }
        case P10_8: {
            Path* path = getOptimalPath(10, 8);
            if (path) {
                navigatePath(*path);
            }
            break;
        }
        case P11_1: {
            Path* path = getOptimalPath(11, 1);
            if (path) {
                navigatePath(*path);
            }
            break;
        }
        case P11_2: {
            Path* path = getOptimalPath(11, 2);
            if (path) {
                navigatePath(*path);
            }
            break;
        }
        case P11_3: {
            Path* path = getOptimalPath(11, 3);
            if (path) {
                navigatePath(*path);
            }
            break;
        }
        case P11_4: {
            Path* path = getOptimalPath(11, 4);
            if (path) {
                navigatePath(*path);
            }
            break;
        }
        case P11_5: {
            Path* path = getOptimalPath(11, 5);
            if (path) {
                navigatePath(*path);
            }
            break;
        }
        case P11_6: {
            Path* path = getOptimalPath(11, 6);
            if (path) {
                navigatePath(*path);
            }
            break;
        }
        case P11_8: {
            Path* path = getOptimalPath(11, 8);
            if (path) {
                navigatePath(*path);
            }
            break;
        }
        default:
            Serial.println("Invalid path type");
            break;
    }
  }
}