/*
*   @file dMPU6050.c
*   @author ngtrdai
*   @date 27/04/2022
*/

#include "./header/dMPU6050.h"

uint8_t MPU;
mpu6050_Acc_Range ACCEL_RANGE;
mpu6050_Gyro_Range GYRO_RANGE;
struct MPU_ANGLE_ACC MPU_ANGLE_ACC_t;
struct MPU_ANGLE MPU_ANGLE_t;

static bool MPU_CONNECTED = SAI;

unsigned long preInterval;
uint8_t MPU_WAI(){
    uint8_t REG_VALUE = wiringPiI2CReadReg8(MPU, MPU6050_WHO_AM_I);
    return REG_VALUE;
}

bool MPU6050_INIT(uint8_t SMPLRT_DATA, uint8_t CONFIG_DATA, uint8_t GYRO_CONFIG_DATA, uint8_t ACCEL_CONFIG_DATA, uint8_t INT_ENABLE_DATA, uint8_t PWR_MGMT_DATA){
    MPU = wiringPiI2CSetup(MPU6050_I2C_ADDR);
    if(MPU_WAI() == MPU6050_DEVICE_ID){
        MPU_CONNECTED = DUNG;
        wiringPiI2CWriteReg8(MPU, MPU6050_SMPLRT_DIV, SMPLRT_DATA);
        wiringPiI2CWriteReg8(MPU, MPU6050_CONFIG, CONFIG_DATA);
        wiringPiI2CWriteReg8(MPU, MPU6050_GYRO_CONFIG, GYRO_CONFIG_DATA);
        wiringPiI2CWriteReg8(MPU, MPU6050_ACCEL_CONFIG, ACCEL_CONFIG_DATA);
        wiringPiI2CWriteReg8(MPU, MPU6050_INT_ENABLE, INT_ENABLE_DATA);
        wiringPiI2CWriteReg8(MPU, MPU6050_PWR_MGMT_1, PWR_MGMT_DATA);

        ACCEL_RANGE = MPU6050_RANGE_2_G;
        GYRO_RANGE = MPU6050_RANGE_250_DEG;

        MPU_REALTIME_VALUE();
        preInterval = millis();

        MPU_ANGLE_t.angleX = MPU_ANGLE_ACC_t.angleAccX;
        MPU_ANGLE_t.angleY = MPU_ANGLE_ACC_t.angleAccY;
        
    }else{
        MPU_CONNECTED = SAI;
    }
    return MPU_CONNECTED;
}

int16_t MPU_READ_2_REG(uint8_t ADDR_H, uint8_t ADDR_L){
    int16_t DATA, VALUE_REG_H, VALUE_REG_L;
    VALUE_REG_H = wiringPiI2CReadReg8(MPU, ADDR_H);
    VALUE_REG_L = wiringPiI2CReadReg8(MPU, ADDR_L);
    DATA = (VALUE_REG_H << 8) | VALUE_REG_L;
    return DATA;
}

struct MPU_VALUE MPU_READ_VALUE(){
    struct MPU_RAW_VALUE rawValue;
    struct MPU_VALUE Value;
    rawValue.rawAccX = MPU_READ_2_REG(MPU6050_Acc_X, MPU6050_Acc_X + 1);
    rawValue.rawAccY = MPU_READ_2_REG(MPU6050_Acc_Y, MPU6050_Acc_Y + 1);
    rawValue.rawAccZ = MPU_READ_2_REG(MPU6050_Acc_Z, MPU6050_Acc_Z + 1);
    rawValue.rawGyroX = MPU_READ_2_REG(MPU6050_Gyro_X, MPU6050_Gyro_X + 1);
    rawValue.rawGyroY = MPU_READ_2_REG(MPU6050_Gyro_Y, MPU6050_Gyro_Y + 1);
    rawValue.rawGyroZ = MPU_READ_2_REG(MPU6050_Gyro_Z, MPU6050_Gyro_Z + 1);

    float ACCEL_SCALE = 1;
    if (ACCEL_RANGE == MPU6050_RANGE_16_G)  ACCEL_SCALE = 2048.0;
    if (ACCEL_RANGE == MPU6050_RANGE_8_G)   ACCEL_SCALE = 4096.0;
    if (ACCEL_RANGE == MPU6050_RANGE_4_G)   ACCEL_SCALE = 8192.0;
    if (ACCEL_RANGE == MPU6050_RANGE_2_G)   ACCEL_SCALE = 16384.0;
    
    Value.AccX = ((float)rawValue.rawAccX) / ACCEL_SCALE;
    Value.AccY = ((float)rawValue.rawAccY) / ACCEL_SCALE;
    Value.AccZ = ((float)rawValue.rawAccZ) / ACCEL_SCALE;

    float GYRO_SCALE = 1;
    if (GYRO_RANGE == MPU6050_RANGE_250_DEG)    GYRO_SCALE = 131.0;
    if (GYRO_RANGE == MPU6050_RANGE_500_DEG)    GYRO_SCALE = 65.5;
    if (GYRO_RANGE == MPU6050_RANGE_1000_DEG)   GYRO_SCALE = 32.8;
    if (GYRO_RANGE == MPU6050_RANGE_2000_DEG)   GYRO_SCALE = 16.4;

    Value.GyroX = ((float)rawValue.rawGyroX) / GYRO_SCALE;
    Value.GyroY = ((float)rawValue.rawGyroY) / GYRO_SCALE;
    Value.GyroZ = ((float)rawValue.rawGyroZ) / GYRO_SCALE;

    return Value;
}

float wrap(float angle)
{
	while (angle > +180) angle -= 360;
	while (angle < -180) angle += 360;
	return angle;
}

struct MPU_ANGLE  MPU_REALTIME_VALUE(){
    struct MPU_VALUE rawValue = MPU_READ_VALUE();
    struct MPU_ANGLE Value;
    float sgZ = rawValue.AccZ<0 ? -1 : 1;
    MPU_ANGLE_ACC_t.angleAccX = atan2f(rawValue.AccY, sgZ*sqrt(rawValue.AccZ*rawValue.AccZ + rawValue.AccX*rawValue.AccX))*180/M_PI;
    MPU_ANGLE_ACC_t.angleAccY = - atan2f(rawValue.AccX, sqrt(rawValue.AccZ*rawValue.AccZ + rawValue.AccY*rawValue.AccY))*180/M_PI;
    unsigned long Tnew = millis();
    float dt = (Tnew - preInterval) * 0.001;
    preInterval = Tnew;
    MPU_ANGLE_t.angleZ += rawValue.GyroZ*dt;
    Value.angleX = MPU_ANGLE_ACC_t.angleAccX;
    Value.angleY = MPU_ANGLE_ACC_t.angleAccY;
    Value.angleZ = MPU_ANGLE_t.angleZ;
    return Value;
}

void MPU_XOA_CO_NGAT(){
    wiringPiI2CReadReg8(MPU, MPU6050_INT_STATUS);
}