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

#define min_speed 50
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
    float angleX = mpu6050.getAngleX();

    Serial.print("angleX : ");
    Serial.println(angleX);
    //Code P
    if (abs(angleX) < 3) 
    {
        motorController.stopMoving();
    }
    else
    {

        int Kp= 16; // Doan m thay doi dong nay
        float speed=angleX*Kp;
        if (speed>0)
        {
            speed = constrain(speed, min_speed, max_speed);
        }
        else 
        {
            speed = constrain(speed, -max_speed, -min_speed);
        }
        motorController.move(speed);
    }
}