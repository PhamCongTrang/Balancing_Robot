#include <Arduino.h>
//#include "PID_v1.h"
#include "LMotorController.h"
#include "I2Cdev.h"
#include "MPU6050_tockn.h"
#include "Wire.h"

#define ENA 10
#define IN1 6
#define IN2 7
#define IN3 4
#define IN4 9
#define ENB 11

#define min_speed 250
#define max_speed 255

double motorSpeedFactorLeft = 1;
double motorSpeedFactorRight = 1;

LMotorController motorController(ENA, IN1, IN2, ENB, IN3, IN4, motorSpeedFactorLeft, motorSpeedFactorRight);

MPU6050 mpu6050(Wire);

long timer = 0;

void setup()
{
    Serial.begin(9600);
    Wire.begin();
    mpu6050.begin();
    // mpu6050.calcGyroOffsets(true);
    mpu6050.setGyroOffsets(-2.45, 0.98, 1.06);
}

void loop()
{
    mpu6050.update();
    float AccY = mpu6050.getAccY();

    Serial.print("accY : ");
    Serial.println(AccY);

    // if (abs(AccY) > 0.8)
    // {
    //     motorController.stopMoving();
    // } else if  (AccY < -0.1)
    // {
    //     motorController.FullspeedBackward();
    // }
    // else if (AccY > 0.1)
    // {
    //     motorController.FullspeedForward();
    // }
    // else
    // {
    //     motorController.stopMoving();
    // }

    int direction = 255;
    int speed = (-direction) * AccY;
    if (speed < 0)
        speed = constrain(speed, -max_speed, -min_speed);
    else
        speed = constrain(speed, min_speed, max_speed);

    if (abs(AccY) > 0.8)
    {
        motorController.stopMoving();
    }
    else if (AccY < -0.1)
    {
        motorController.move(speed);
    }
    else if (AccY > 0.1)
    {
        motorController.move(speed);
    }
    else
    {
        motorController.stopMoving();
    }

    // if(millis() - timer > 1000) {
    //     timer = millis();
    // }
}