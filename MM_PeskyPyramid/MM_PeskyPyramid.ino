#include "LedControl.h"
//#include "char.h"
#include "left_side_0.h"
#include "right_side_0.h"
#include "left_side_1.h"
#include "right_side_1.h"
#include "left_side_2.h"
#include "right_side_2.h"
#include "left_side_3.h"
#include "right_side_3.h"

// Define pins Right
#define P_DIN_RIGHT 5
#define P_CLK_RIGHT 4
#define P_CS_RIGHT  6

// Define pins Left
#define P_DIN_LEFT 8
#define P_CLK_LEFT 9
#define P_CS_LEFT  7

#define HALL_0  A0
#define HALL_1  A1

// Display
#define DISP_1 1

//  State machine
int stateMachine = 0;

// Dedine and Create LED matrix Left and Right
LedControl lcRight=LedControl(P_DIN_RIGHT,P_CLK_RIGHT,P_CS_RIGHT,DISP_1);
LedControl lcLeft=LedControl(P_DIN_LEFT,P_CLK_LEFT,P_CS_LEFT,DISP_1);

unsigned long delaytime=300;


// Left image display
void displayImageRight(const byte* image) { 
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      lcRight.setLed(0, i, j, bitRead((image[i]), 7 - j));
    }
   }
}
//Light image display
void displayImageLeft(const byte* image) { 
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      lcLeft.setLed(0, i, j, bitRead((image[i]), 7 - j));
    }
   }
}

void setup() {
    /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lcRight.shutdown(0,false);
  lcLeft.shutdown(0,false);
  /* Set the brightness to a medium values */
  lcRight.setIntensity(0,8);
  lcLeft.setIntensity(0,8);
  /* and clear the display */
  lcRight.clearDisplay(0);
  lcLeft.clearDisplay(0);

  pinMode(HALL_0, INPUT_PULLUP);
  pinMode(HALL_1, INPUT_PULLUP);
  Serial.begin(9600);

}


  
int i = 0;
int tDelay = 2000;



void loop() { 
  //image lengths for left and right MUST be the same
  int hallZero = !digitalRead(HALL_0);
  int hallOne = !digitalRead(HALL_1) << 1;

  // Create a small state machine 
  // 0 = normal, no magents
  // 1 = Hall 0 Magnet present
  // 2 = Hall 1 Magnet present
  // 3 = Hall 0 & 1 present

  stateMachine = hallZero + hallOne;

  Serial.print("hallZero = ");
  Serial.print(hallZero);
  Serial.print("\t hallOne = ");
  Serial.print(hallOne);
  Serial.print("\t output = ");
  Serial.println(stateMachine);
  
  switch (stateMachine){
    case 1:
      tDelay = 2000;
      if(IMAGES_LEFT_STATE0_LEN==IMAGES_RIGHT_STATE0_LEN){
        displayImageLeft(IMAGES_LEFT_STATE0[i]);
        displayImageRight(IMAGES_RIGHT_STATE0[i]);
   
        if (++i >= IMAGES_LEFT_STATE0_LEN ) {
          i = 0;
        }    
      }
    break;

    case 0:
      tDelay = 200;
      if(IMAGES_LEFT_STATE1_LEN==IMAGES_RIGHT_STATE1_LEN){
        displayImageLeft(IMAGES_LEFT_STATE1[i]);
        displayImageRight(IMAGES_RIGHT_STATE1[i]);
   
        if (++i >= IMAGES_LEFT_STATE1_LEN ) {
          i = 0;
        }    
      }
    break;

    case 2:
      tDelay = 2000;
      if(IMAGES_LEFT_STATE2_LEN==IMAGES_RIGHT_STATE2_LEN){
        displayImageLeft(IMAGES_LEFT_STATE2[i]);
        displayImageRight(IMAGES_RIGHT_STATE2[i]);
 
        if (++i >= IMAGES_LEFT_STATE2_LEN ) {
          i = 0;
        }    
      }
    break;

    case 3:
      tDelay = 2000;
      if(IMAGES_LEFT_STATE3_LEN==IMAGES_RIGHT_STATE3_LEN){
        displayImageLeft(IMAGES_LEFT_STATE3[i]);
        displayImageRight(IMAGES_RIGHT_STATE3[i]);
   
        if (++i >= IMAGES_LEFT_STATE3_LEN ) {
          i = 0;
        }    
      }
    break;
  }
 
  delay(tDelay);
}
