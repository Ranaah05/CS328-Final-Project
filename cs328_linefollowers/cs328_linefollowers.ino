//************************************************************
// Line Follower
// File: Project_2.ino
// Purpose: learn how to program line follower 
// Group 5: Elena Raner Audrey
//************************************************************
/*****************************************************************************
Line tracking sensors	LTsensor_l	8	Pin of left line tracking sensor yellow
LTsensor_c	7	Pin of middle line tracking sensor green
LTsensor_r	6	Pin of right line tracking sensor white
*****************************************************************************/

#define MotorPWM_A 4
#define MotorPWM_B 5

#define INA1A 32
#define INA2A 34
// Right Motor Rotation pins
#define INA1B 30
#define INA2B 36


// Line following pins
#define LT_LEFT   8
#define LT_CENTER 7
#define LT_RIGHT  6

int speed = 50;
int adjustspeed = 40; // speed to adjust correction when following line 
int heavy = 25;
void setup() {
  // Initialize Motors
    pinMode(MotorPWM_A, OUTPUT);
    pinMode(MotorPWM_B, OUTPUT);
    pinMode(INA1A, OUTPUT);
    pinMode(INA2A, OUTPUT);
    pinMode(INA1B, OUTPUT);
    pinMode(INA2B, OUTPUT);

  // Initialize Line Sensor pins
  pinMode(LT_LEFT,   INPUT);
  pinMode(LT_CENTER, INPUT);
  pinMode(LT_RIGHT,  INPUT);
}

void loop() {
  int left   = digitalRead(LT_LEFT);
  int center = digitalRead(LT_CENTER);
  int right  = digitalRead(LT_RIGHT);

  // CENTER = 0 means on line
  if (center == 0) {
    forward(speed, speed);  // straight
  }
  else if (left == 0) {
    forward(adjustspeed, speed); // slow left motor → turn left
  }
  else if (right == 0) {
    forward(speed, adjustspeed); // slow right motor → turn right
  }
  else if (left == 0 && center == 1) {
    forward(heavy, speed);        // heavy left correction
  }
  else if (right == 0 && center == 1) {
    forward(speed, heavy);        // heavy right correction
}
  else {
    stopMotors();
  }
}

void forward(int speedA, int speedB) {
  analogWrite(MotorPWM_A, speedA);
  analogWrite(MotorPWM_B, speedB);

  digitalWrite(INA1A, HIGH);
  digitalWrite(INA2A, LOW);
  digitalWrite(INA1B, HIGH);
  digitalWrite(INA2B, LOW);
}

void stopMotors() {
  analogWrite(MotorPWM_A, 0);
  analogWrite(MotorPWM_B, 0);
}