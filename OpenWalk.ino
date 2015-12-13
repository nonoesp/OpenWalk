
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
  public : int sweepAngle;
  
  public : float duration;
  public : float current;
  public : String name;

  public : void init(int _sweepAngle, int _homeAngle) {
    this->homeAngle = _homeAngle;
    this->sweepAngle = _sweepAngle;
    this->position = this->sweepAngle;
    this->duration = 100; // Default
  }

  public : void goHome() {
    this->servo.write(homeAngle);
  }

  public : void move(float from, float to, float steps) {
    float step = (to - from) / (steps * this->duration);
    this->position += step;
    this->updateAngle();
  }

  public : int absoluteAngle() {
    return this->position + this->homeAngle;
  }

  public : void updateAngle() {
     this->servo.write(this->absoluteAngle()); 
  }

  public : void update() {
    this->current++;
    if(this->current > this->duration) {
      this->current = 0;
      this->position = this->sweepAngle;
    }
  }

  public : void log() {
    Serial.print(this->name);
    Serial.print(" -- current: ");
    Serial.print(this->current);
    Serial.print(" position: ");
    Serial.print(this->position);
    Serial.print(" absoluteAngle: ");
    Serial.print(this->absoluteAngle());
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
  
  Serial.begin(19200);

  // ServoA (Front)
  ServoA.init(-30, homeAngleA);
  ServoA.name = "Front";  
  ServoA.servo.attach(9);
  ServoA.duration = 10000;

  // ServoB (Rear)
  ServoB.init(30, homeAngleB);
  ServoB.name = "Rear ";  
  ServoB.servo.attach(10);
  ServoB.duration = 10000;
}

void loop() { // This code runs repeteadly

  if(cycleCount == 200) {
    cycleCount = 0;
    
    ServoA.log();
    ServoB.log(); 
  } else {
    cycleCount++;
  }

  // --------------------------------------------
  // ServoA Behavior
  // --------------------------------------------

  ServoA.update();

  if(ServoA.current <= ServoA.duration * 0.5) { // 50%
    ServoA.move(ServoA.sweepAngle, -ServoA.sweepAngle, 0.5);
  }

  if(ServoA.current > ServoA.duration * 0.5 && // 50%
    ServoA.current <= ServoA.duration * 1.0) {
    ServoA.move(-ServoA.sweepAngle, ServoA.sweepAngle, 0.5);    
  }
  
  // --------------------------------------------
  // ServoB Behavior
  // --------------------------------------------

  ServoB.update();

  if(ServoB.current <= ServoB.duration * 0.5) { // 50%
    ServoB.move(ServoB.sweepAngle, -ServoB.sweepAngle, 0.5);
  }

  if(ServoB.current > ServoB.duration * 0.5 && // 50%
    ServoB.current <= ServoB.duration * 1.0) {
    ServoB.move(-ServoB.sweepAngle, ServoB.sweepAngle, 0.5);    
  }

  // --------------------------------------------
  // Delay
  // --------------------------------------------
  
  //delay(delayTime*0.2);
  delay(1);
}

