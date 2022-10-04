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

#define min_speed 20
#define max_speed 255

double motorSpeedFactorLeft = 1;
double motorSpeedFactorRight = 1;

LMotorController motorController(ENA, IN1, IN2, ENB, IN3, IN4, motorSpeedFactorLeft, motorSpeedFactorRight);

MPU6050 mpu6050(Wire);

void setup()
{
    Serial.begin(9600);
    Wire.begin();
    mpu6050.begin();
    // mpu6050.calcGyroOffsets(true);
    mpu6050.setGyroOffsets(-2.45, 0.98, 1.06);
}
unsigned long pret = 0;
int Kp = 1, Ki = 1, Kd = 1;
float P, I = 0, D;
float angleX=0, preAngleX, speed;
void loop()
{
    preAngleX = angleX;

    mpu6050.update();
    angleX = mpu6050.getAngleX();

    int dt = millis() - pret;
    pret = millis();

    if ((abs(angleX) < 3) || (abs(angleX) > 75))
    {
        motorController.stopMoving();
    }
    else
    {

        P = Kp * angleX;
        I += Ki * angleX * dt;
        D = Kd * (angleX - preAngleX) / dt;
        speed = P + I + D;
        if (speed > 0)
        {
            speed = constrain(speed, min_speed, max_speed);
        }
        else
        {
            speed = constrain(speed, -max_speed, -min_speed);
        }
        motorController.move(-speed);
    }
}