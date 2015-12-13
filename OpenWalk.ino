
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
 * ServoWrapper Class
 * 
 * A wrapper to interact with the Servo class.
 */

class ServoWrapper {
  public : Servo servo;
  public : double position;
  public : int homeAngle;
  
  public : float duration;
  public : float current;

  public : void init(int _homeAngle) {
    this->homeAngle = _homeAngle;
    this->position = this->homeAngle;
    this->goHome();
    this->duration = 100;
  }

  public : void goHome() {
    this->servo.write(homeAngle);
  }

  public : void move(float from, float to, float steps) {
    float step = (to - from) / (steps * this->duration);
    this->position += step;
  }

  public : void update() {
    this->current++;
    if(this->current > this->duration) {
      this->current = 0;
    }
  }

  public : void log() {
    Serial.print("current: ");
    Serial.print(this->current);
    Serial.print(" position: ");
    Serial.print(this->position);
    Serial.println();       
  }
};

// --------------------------------------------------------

// Variables
int cycleCount = 0;
int delayTime = 10;

// Servo Wrappers
ServoWrapper ServoA;
ServoWrapper ServoB;

// Home Angles
int homeAngleA = 90;
int homeAngleB = 90;

// Serial connection
char val; // Data received from the serial port

void setup() { // This code just runs once

  homeAngleA = 90;
  
  Serial.begin(19200);

  // ServoA
  ServoA.init(homeAngleA);  
  ServoA.servo.attach(9);  
  ServoA.duration = 10000;
}

int index = 0;

void loop() { // This code runs repeteadly

  if(index == 200) {
    index = 0;
    
    ServoA.log();    
  } else {
    index++;
  }

  // Working

  ServoA.update();

  if(ServoA.current <= ServoA.duration * 0.5) { // 50%
    ServoA.move(ServoA.homeAngle, 50.0, 0.5);
  }

  if(ServoA.current > ServoA.duration * 0.5 && // 40%
    ServoA.current <= ServoA.duration * 0.9) {
    ServoA.move(50.0, 30.0, 0.4);    
  }

  if(ServoA.current > ServoA.duration * 0.9 && // 10%
    ServoA.current <= ServoA.duration * 1.0) {
    ServoA.move(30.0, ServoA.homeAngle, 0.1);    
  }  

  // Delay in between movements
  //delay(delayTime*0.2);
  delay(1);
}

