
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

/*
 * ServoController Class
 * 
 * A wrapper to interact with the Servo class.
 */

class ServoController {
  public : Servo servo;
  public : double position;
  public : int home;
  public : int goal;
  public : double speed;
  public : bool isGoingUp;
  public : bool shouldEase;

  public : void init() {
    this->goHome();
    isGoingUp = true;
    shouldEase = false;
    speed = 1.0;
  }

  public : void goHome() {
    this->position = this->home;
    this->servo.write(home);
  }

  public : void setGoal(double relativeGoal) {
    this->goal = this->home + relativeGoal;
  }

  public : void moveTowardsGoal() {
    if(shouldEase) {
      double difference = this->goal - this->position;
      this->position += difference*0.1;
      this->servo.write(this->position);      
    } else {
      if(this->position < this->goal) {
        this->position += this->speed;
      } else {
        this->position -= this->speed;;
      }
      this->servo.write(this->position);   
    }
  }

  public : bool reachedGoal() {
    float margin = 0.5;
    if(this->goal < this->position) {
      if(this->goal + margin >= this->position) {
        this->position = this->goal;
        return true;
      }
    } else {
      if(this->goal - margin <= this->position) {
        this->position = this->goal;
        return true;
      }
    }
    return false;
  }
};

// Variables
int cycleCount = 0;
int delayTime = 10;

// Servo Controllers
ServoController servoControllerA;
ServoController servoControllerB;

// Home Angles
int homeAngleA = 90;
int homeAngleB = 46;

// Serial connection
char val; // Data received from the serial port

void setup() { // This code just runs once
  
  Serial.begin(9600);

  // ServoControllerA
  servoControllerA.servo.attach(9);
  servoControllerA.home = homeAngleA;
  servoControllerA.init();
  
  // ServoControllerB
  servoControllerB.servo.attach(10);
  servoControllerB.home = homeAngleB;
  servoControllerB.init();
}

void loop() { // This code runs repeteadly

  Serial.println(servoControllerA.position);
  //Serial.println("A: " + servoControllerA.position + ", B: " + servoControllerB.position);  

if(1 == 1) {
  // ServoControllerA
  if(servoControllerA.isGoingUp) {
    //servoControllerA.goal = 10;
    servoControllerA.setGoal(80.0); // Counterclockwise
    servoControllerA.speed = 0.3;
  } else {
    //servoControllerA.goal = -10;
    servoControllerA.setGoal(-80.0); // Clockwise
    servoControllerA.speed = 0.3;
  }

  if(servoControllerA.reachedGoal()) {
    // Reached goal, changed direction
    servoControllerA.isGoingUp = !servoControllerA.isGoingUp;
    delay(0);
  }

  servoControllerA.moveTowardsGoal();
}

  // Delay in between movements
  delay(delayTime*0.2);
}
