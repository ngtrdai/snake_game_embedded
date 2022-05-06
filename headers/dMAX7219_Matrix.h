#include <stdio.h>
#include <stdint.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>

typedef enum{
    bbMatCuoi,
    bbMatBuon
} BieuTuong;

void dMAX7219_MATRIX_INIT(int kenhSPI, int tocDoTruyen);
void dMAX7219_SET_PIXEL(uint8_t toaDoX, uint8_t toaDoY);
void dMAX7219_CLEAR_PIXEL(uint8_t toaDoX, uint8_t toaDoY);

void dMAX7219_CLEAR_DISPLAY();
void dMAX7219_FILL_DISPLAY();

void dMAX7219_SEND_DATA(uint8_t diaChi, uint8_t giaTri);
void dMAX7219_SEND_DISPLAY();
void dMAX7219_SET_INTENSITY(uint8_t doSang);
void dMAX7219_SEND_EMOJI(BieuTuong bieuTuong);
