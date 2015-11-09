
/*
 *  OpenWalk
 *  6478, Informal Robotics
 *  Harvard Graduate School of Design
 *  
 *  Nono Martínez Alonso (@nonoesp)
 *  Enol Vallina
 *  Guillermo Saavedra
 */

/*
 * The MIT License (MIT)
 * 
 * Copyright (c) 2015 Nono Martínez Alonso, Enol Vallina, Guillermo Saavedra
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
*/

#include <Servo.h>

class ServoController {
  public : Servo servo;
  public : int position;
  public : int home;

  public : int goal;

  public : void init() {
    this->goHome();
  }

  public : void goHome() {
    this->position = this->home;
    this->servo.write(home);
  }

  public : void moveTowardsGoal() {
    this->servo.write(this->goal);
  }
};

// Variables
int cycleCount = 0;
int delayTime = 10;

// Servo Controllers
ServoController servoControllerA;

// Home Angles
int homeAngleA = 110;
int homeAngleB = 46;

// Serial connection
char val; // Data received from the serial port

void setup() {
  Serial.begin(9600);

  servoControllerA.servo.attach(9);
  servoControllerA.home = homeAngleA;
  servoControllerA.init();

}

void loop() {
  servoControllerA.goal = 120;
  servoControllerA.moveTowardsGoal();
  delay(3000);
  servoControllerA.goHome();
  delay(3000);
}

/*

void moveServoTowards(Servo servo, int position, double goalAngleStart, double goalAngleEnd, double delayFactor) {

    float goal;
    
    if(isPhaseA) {
      goal = goalAngleStart;
      if(position >= goalAngleStart - 5)
      {
        isPhaseA = false;
      }
    } else {
       goal = goalAngleEnd;
      if(position <= goalAngleEnd + 5) {
        isPhaseA = true;
        cycleCount++;        
      }
    }
    
    // Ease Towards Goal
    double difference = goal - position;
    position += difference*0.8;
    servo.write(position);
    delay(delayTime*delayFactor);    

    // Stop After X Cycles
    if(cycleCount > 2) {
      cycleCount = 0;
      servo.write(centralAngleA);
      delay(10000);
    }    
}
*/


