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


