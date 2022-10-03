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

void setup()
{
    Serial.begin(9600);
    Wire.begin();
    mpu6050.begin();
    // mpu6050.calcGyroOffsets(true);
    mpu6050.setGyroOffsets(-2.45, 0.98, 1.06);
}
unsigned int pret=0; // robot chay duoc 65s
int Kp= 16, Ki=10, Kd =0;
float P, I, D;
void loop()
{
    preAngleX = angleX;

    mpu6050.update();
    float angleX = mpu6050.getAngleX();

    dt = milis() - pret;
    pret = milis();

    if (abs(angleX) < 3) 
    {
        motorController.stopMoving();
    }
    else
    {
        
        P = Kp*angleX;
        I += Ki*angleX*dt;
        D = Kd*(angleX - preAngleX)/dt;
        speed = P + I + D;
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