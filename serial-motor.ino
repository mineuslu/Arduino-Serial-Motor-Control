#include "string.h"

#define R1_pwm 3  //SAĞ ÖN
#define R1_IN1 2
#define R1_IN2 4

#define R2_pwm 5
#define R2_IN1 6
#define R2_IN2 7

#define L1_pwm 9
#define L1_IN1 8
#define L1_IN2 11

#define L2_pwm 10
#define L2_IN1 12
#define L2_IN2 13

#define E_STOP_PIN A0

char maindata[7];  // S000CF serial üzerinden göndereceğimiz veri formatı.
char speed_buffer[3];
int speed = 1;
int direction = 0;
int mod = 0;
char c;

void setup() {

  Serial.begin(9600);

  pinMode(R1_pwm, OUTPUT);
  pinMode(R1_IN1, OUTPUT);
  pinMode(R1_IN2, OUTPUT);

  pinMode(R2_pwm, OUTPUT);
  pinMode(R2_IN1, OUTPUT);
  pinMode(R2_IN2, OUTPUT);

  pinMode(L1_pwm, OUTPUT);
  pinMode(L1_IN1, OUTPUT);
  pinMode(L1_IN2, OUTPUT);

  pinMode(L2_pwm, OUTPUT);
  pinMode(L2_IN1, OUTPUT);
  pinMode(L2_IN2, OUTPUT);

  pinMode(E_STOP_PIN, OUTPUT);

  digitalWrite(E_STOP_PIN, HIGH);
}

void loop() {


  if (Serial.available()) {
     c = Serial.read();

    if (c == 'S' || c == 'E' || c == 'D' || c == 'R') {

      while (Serial.available() < 5)
        ;
    }

    if (c == 'E') {
      analogWrite(R1_pwm, 0);
      analogWrite(R2_pwm, 0);
      analogWrite(L1_pwm, 0);
      analogWrite(L2_pwm, 0);
      digitalWrite(E_STOP_PIN, LOW);
    }

    else digitalWrite(E_STOP_PIN, HIGH);



    for (int i = 0; i < 5; i++) {
      maindata[i] = Serial.read();
    }
    maindata[5] = '\0';




    direction = maindata[0] - '0';  // doğrudan integer değerini bulmak için '0' ın ASCII değeri çıkartılır.
    speed_buffer[0] = maindata[1];
    speed_buffer[1] = maindata[2];
    speed_buffer[2] = '\0';

    speed = atoi(speed_buffer);         // burada ise üstteki yöntemden farklı olarak hız verisinin elemanları bir buffer içine alınıp
    speed = map(speed, 0, 99, 0, 255);  // atoi ile ASCII to integer dönüşümü yapılır

    Serial.print("Direction: ");
    Serial.print(direction);
    Serial.print(" Speed: ");
    Serial.println(speed);

  }

  if (c == 'S') {

    if (direction == 0) {

      digitalWrite(R1_IN1, LOW);
      digitalWrite(R1_IN2, HIGH);
      analogWrite(R1_pwm, speed);

      digitalWrite(R2_IN1, LOW);
      digitalWrite(R2_IN2, HIGH);
      analogWrite(R2_pwm, speed);

      digitalWrite(L1_IN1, HIGH);
      digitalWrite(L1_IN2, LOW);
      analogWrite(L1_pwm, speed);

      digitalWrite(L2_IN1, HIGH);
      digitalWrite(L2_IN2, LOW);
      analogWrite(L2_pwm, speed);
    }

    else if (direction == 1) {
      digitalWrite(R1_IN1, HIGH);
      digitalWrite(R1_IN2, LOW);
      analogWrite(R1_pwm, speed);

      digitalWrite(R2_IN1, HIGH);
      digitalWrite(R2_IN2, LOW);
      analogWrite(R2_pwm, speed);

      digitalWrite(L1_IN1, LOW);
      digitalWrite(L1_IN2, HIGH);
      analogWrite(L1_pwm, speed);

      digitalWrite(L2_IN1, LOW);
      digitalWrite(L2_IN2, HIGH);
      analogWrite(L2_pwm, speed);

    }

    else if (direction == 2) {
      digitalWrite(R1_IN1, HIGH);
      digitalWrite(R1_IN2, LOW);
      analogWrite(R1_pwm, speed);

      digitalWrite(R2_IN1, LOW);
      digitalWrite(R2_IN2, HIGH);
      analogWrite(R2_pwm, speed);

      digitalWrite(L1_IN1, LOW);
      digitalWrite(L1_IN2, HIGH);
      analogWrite(L1_pwm, speed);

      digitalWrite(L2_IN1, HIGH);
      digitalWrite(L2_IN2, LOW);
      analogWrite(L2_pwm, speed);

    }

    else if (direction == 3) {
      digitalWrite(R1_IN1, LOW);
      digitalWrite(R1_IN2, HIGH);
      analogWrite(R1_pwm, speed);

      digitalWrite(R2_IN1, HIGH);
      digitalWrite(R2_IN2, LOW);
      analogWrite(R2_pwm, speed);

      digitalWrite(L1_IN1, HIGH);
      digitalWrite(L1_IN2, LOW);
      analogWrite(L1_pwm, speed);

      digitalWrite(L2_IN1, LOW);
      digitalWrite(L2_IN2, HIGH);
      analogWrite(L2_pwm, speed);
    }
  }

  if (c == 'D') {

    if (direction == 0) {

      digitalWrite(R1_IN1, LOW);
      digitalWrite(R1_IN2, HIGH);
      analogWrite(R1_pwm, speed);

      digitalWrite(L2_IN1, LOW);
      digitalWrite(L2_IN2, HIGH);
      analogWrite(L2_pwm, speed);

      digitalWrite(R2_IN1, HIGH);
      digitalWrite(R2_IN2, LOW);
      analogWrite(R2_pwm, 0);

      digitalWrite(L1_IN1, HIGH);
      digitalWrite(L1_IN2, LOW);
      analogWrite(L1_pwm, 0);
    }

    else if (direction == 1) {
      digitalWrite(R1_IN1, HIGH);
      digitalWrite(R1_IN2, LOW);
      analogWrite(R1_pwm, speed);

      digitalWrite(L2_IN1, LOW);
      digitalWrite(L2_IN2, HIGH);
      analogWrite(L2_pwm, speed);

      digitalWrite(R2_IN1, HIGH);
      digitalWrite(R2_IN2, LOW);
      analogWrite(R2_pwm, 0);

      digitalWrite(L1_IN1, HIGH);
      digitalWrite(L1_IN2, LOW);
      analogWrite(L1_pwm, 0);

    }


    else if (direction == 2) {

      digitalWrite(R2_IN1, LOW);
      digitalWrite(R2_IN2, HIGH);
      analogWrite(R2_pwm, speed);

      digitalWrite(L1_IN1, HIGH);
      digitalWrite(L1_IN2, LOW);
      analogWrite(L1_pwm, speed);

      digitalWrite(R1_IN1, HIGH);
      digitalWrite(R1_IN2, LOW);
      analogWrite(R1_pwm, 0);

      digitalWrite(L2_IN1, HIGH);
      digitalWrite(L2_IN2, LOW);
      analogWrite(L2_pwm, 0);

    }

    else if (direction == 3) {

      digitalWrite(R2_IN1, HIGH);
      digitalWrite(R2_IN2, LOW);
      analogWrite(R2_pwm, speed);

      digitalWrite(L1_IN1, LOW);
      digitalWrite(L1_IN2, HIGH);
      analogWrite(L1_pwm, speed);

      digitalWrite(R1_IN1, HIGH);
      digitalWrite(R1_IN2, LOW);
      analogWrite(R1_pwm, 0);

      digitalWrite(L2_IN1, HIGH);
      digitalWrite(L2_IN2, LOW);
      analogWrite(L2_pwm, 0);
    }
  }

  if (c == 'R') {


    if (direction == 0) {

      digitalWrite(R1_IN1, LOW);
      digitalWrite(R1_IN2, HIGH);
      analogWrite(R1_pwm, speed);

      digitalWrite(R2_IN1, LOW);
      digitalWrite(R2_IN2, HIGH);
      analogWrite(R2_pwm, speed);

      digitalWrite(L1_IN1, LOW);
      digitalWrite(L1_IN2, HIGH);
      analogWrite(L1_pwm, speed);

      digitalWrite(L2_IN1, LOW);
      digitalWrite(L2_IN2, HIGH);
      analogWrite(L2_pwm, speed);
    }

    else if (direction == 1) {
      digitalWrite(R1_IN1, HIGH);
      digitalWrite(R1_IN2, LOW);
      analogWrite(R1_pwm, speed);

      digitalWrite(R2_IN1, HIGH);
      digitalWrite(R2_IN2, LOW);
      analogWrite(R2_pwm, speed);

      digitalWrite(L1_IN1, HIGH);
      digitalWrite(L1_IN2, LOW);
      analogWrite(L1_pwm, speed);

      digitalWrite(L2_IN1, HIGH);
      digitalWrite(L2_IN2, LOW);
      analogWrite(L2_pwm, speed);
    }
  }
}
