/*
*   @file dMPU6050.h
*   @author ngtrdai
*   @date 27/04/2022
*/

/*
*   Khai báo thư viện.
*/
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
/*
*   Khu vực define giá trị mặc định
*/

typedef enum{
    DUNG,
    SAI
} bool;

#define MPU6050_I2C_ADDR        0x68
#define MPU6050_DEVICE_ID       0x68        // Giá trị mà hàm MPU_WAI() trả về.
#define MPU6050_SEFT_TEST_X     0x0D
#define MPU6050_SEFT_TEST_Y     0x0E
#define MPU6050_SEFT_TEST_Z     0x0F
#define MPU6050_SEFT_TEST_A     0x10
/*
*   Khu vực define giá trị thanh ghi cấu hình MPU6050 
*/
#define MPU6050_SMPLRT_DIV      0x19
#define MPU6050_CONFIG          0x1A
#define MPU6050_GYRO_CONFIG     0x1B
#define MPU6050_ACCEL_CONFIG    0x1C

#define MPU6050_PWR_MGMT_1 0x6B         ///< Primary power/sleep control register
#define MPU6050_PWR_MGMT_2 0x6C         ///< Secondary power/sleep control register
#define MPU6050_INT_ENABLE 0x38         ///< Interrupt enable configuration register
#define MPU6050_INT_STATUS 0x3A
/*
*   Khu vực define giá trị thanh ghi cấu hình GPIO
*/
#define MPU6050_INT_PIN_CONFIG  0x01        // Địa chỉ GPIO nhận xung ngắt.
#define MPU6050_WHO_AM_I        0x75
#define MPU6050_Acc_X           0x3B
#define MPU6050_Acc_Y           0x3D
#define MPU6050_Acc_Z           0x3F
#define MPU6050_Gyro_X          0x43
#define MPU6050_Gyro_Y          0x45
#define MPU6050_Gyro_Z          0x47
/*
*   @brief Cấu hình khoảng lựa chọn của gia tốc kế
*/
typedef enum {
    MPU6050_RANGE_2_G = 0b00,   ///< +/- 2g (Giá trị mặc định)
    MPU6050_RANGE_4_G = 0b01,   ///< +/- 4g
    MPU6050_RANGE_8_G = 0b10,   ///< +/- 8g
    MPU6050_RANGE_16_G = 0b11,  ///< +/- 16g
} mpu6050_Acc_Range;

/*
*   @brief Cấu hình khoảng lựa chọn của con quay hồi chuyển
*/
typedef enum {
    MPU6050_RANGE_250_DEG,      ///< +/- 250 deg/s (Giá trị mặc định)
    MPU6050_RANGE_500_DEG,      ///< +/- 500 deg/s
    MPU6050_RANGE_1000_DEG,     ///< +/- 1000 deg/s
    MPU6050_RANGE_2000_DEG,     ///< +/- 2000 deg/s
} mpu6050_Gyro_Range;

struct MPU_RAW_VALUE {
    int16_t rawAccX;
    int16_t rawAccY;
    int16_t rawAccZ;
    int16_t rawGyroX;
    int16_t rawGyroY;
    int16_t rawGyroZ;
};



struct MPU_VALUE {
    float AccX;
    float AccY;
    float AccZ;
    float GyroX;
    float GyroY;
    float GyroZ;
};



struct MPU_ANGLE_ACC{
    float angleAccX;
    float angleAccY;
    float angleAccZ;
};

struct MPU_ANGLE{
    float angleX;
    float angleY;
    float angleZ;
};

/*
*   HÀM
*/
uint8_t MPU_WAI();
bool MPU6050_INIT(uint8_t SMPLRT_DATA, uint8_t CONFIG_DATA, uint8_t GYRO_CONFIG_DATA, uint8_t ACCEL_CONFIG_DATA, uint8_t INT_ENABLE_DATA, uint8_t PWR_MGMT_DATA);
struct MPU_VALUE MPU_READ_VALUE();
int16_t MPU_READ_2_REG(uint8_t ADDR_H, uint8_t ADDR_L);
struct MPU_ANGLE MPU_REALTIME_VALUE();
void MPU_XOA_CO_NGAT();
/*
*   HÀM SETUP
*/



