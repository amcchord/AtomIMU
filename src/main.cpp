#include <Arduino.h>
#include "M5Atom.h"


float accX = 0, accY = 0, accZ = 0;
float gyroX = 0, gyroY = 0, gyroZ = 0;
float cX = 0, cY = 0, cZ = 0;
float pitch, roll, yaw;
float temp = 0;
bool IMU6886Flag = false;
int count = 0;

void setup()
{
    M5.begin(true, false, true);
    Serial.begin(9600);

    if (M5.IMU.Init() != 0)
        IMU6886Flag = false;
    else
        IMU6886Flag = true;

    delay(2000);
    M5.IMU.CalibrateGyro(3);
}

void loop()
{

    if (IMU6886Flag == true)
    {
        M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ);
        M5.IMU.getAccelData(&accX, &accY, &accZ);
        M5.IMU.getAhrsData(&pitch, &roll, &yaw);
        M5.IMU.getCalibData(&cX, &cY, &cZ);
        M5.IMU.getTempData(&temp);

        Serial.printf("%.2f,%.2f,%.2f -- %.2f,%.2f,%.2f\r\n", pitch, roll, yaw, gyroX, gyroY, gyroZ);
        count++;
    }

    delay(50);
    M5.update();
}