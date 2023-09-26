#include <Servo.h>

#define S0 2
#define S1 3
#define S2 4
#define S3 5
#define sensorOut 6

Servo topServo;
Servo bottomServo;

int frequency = 0;
int color = 0;

void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  
  // Setting frequency-scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  
  topServo.attach(7);
  bottomServo.attach(8);
  
  Serial.begin(9600);
}

void loop() {
  color = readColor();
  
  if (color != 0) {
    topServo.write(115);
    delay(500);
  
    for (int i = 115; i > 65; i--) {
      topServo.write(i);
      delay(2);
    }
  
    delay(500);
  
    switch (color) {
      case 1:
        bottomServo.write(50);
        break;
      case 2:
        bottomServo.write(75);
        break;
      case 3:
        bottomServo.write(100);
        break;
      case 4:
        bottomServo.write(125);
        break;
      case 5:
        bottomServo.write(150);
        break;
      case 6:
        bottomServo.write(175);
        break;
    }
  
    delay(300);
  
    for (int i = 65; i > 29; i--) {
      topServo.write(i);
      delay(2);
    }
  
    delay(200);
  
    for (int i = 29; i < 115; i++) {
      topServo.write(i);
      delay(2);
    }
  
    delay(500);
  }
}

// Custom Function - readColor()
int readColor() {
  // Setting red filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int R = frequency;
  
  // Setting Green filtered photodiodes to be read
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int G = frequency;
  
  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int B = frequency;
  
  if (R >= 130 && R <= 170 && G >= 160 && G <= 200 && B >= 140 && B <= 160) {
    return 1;  // Red
  }
  else if (R >= 140 && R <= 180 && G >= 150 && G <= 190 && B >= 135 && B <= 155) {
    return 2;  // Green
  }
  else if (R >= 160 && R <= 200 && G >= 170 && G <= 190 && B >= 120 && B <= 140) {
    return 3;  // Blue
  }
  else if (R >= 130 && R <= 170 && G >= 150 && G <= 190 && B >= 140 && B <= 160) {
    return 4;  // Orange
  }
  else if (R >= 160 && R <= 200 && G >= 170 && G <= 220 && B >= 120 && B <= 170) {
    return 5;  // Purple
  }
  else if (R >= 120 && R <= 160 && G >= 140 && G <= 170 && B >= 130 && B <= 150) {
    return 6;  // Yellow
  }

  return 0;
}
