#include "./header/dMAX7219_Matrix.h"

uint8_t dMAX7219_BUFFER[8];
uint8_t dMAX7219_BUFFER_COLUMN[8];

uint8_t matCuoi[8] = {0x3C,0x42,0x95,0xA1,0xA1,0x95,0x42,0x3C};
uint8_t matBuon[8] = {0x3C,0x42,0xA5,0x91,0x91,0xA5,0x42,0x3C};

void dMAX7219_MATRIX_INIT(int kenhSPI, int tocDoTruyen){
    // Setup SPI
    wiringPiSPISetup(kenhSPI, tocDoTruyen);
    // BẬT chế độ SHUTDOWN
    dMAX7219_SEND_DATA(0x0C, 0x00);
    // Sử dụng tất cả các thanh ghi DIGITS
    dMAX7219_SEND_DATA(0x0B, 0x07);
    // Khởi tạo ban đầu độ sáng tối đa
    dMAX7219_SEND_DATA(0x0A, 0x0F);
    // Tắt chế độ TEST DISPLAY
    dMAX7219_SEND_DATA(0x0F, 0x00);
    // Tắt chế độ ENCODING
    dMAX7219_SEND_DATA(0x09, 0x00);
    // Xoá toàn bộ màn hình
    dMAX7219_CLEAR_DISPLAY();
    // TẮT chế độ SHUTDOWN
    dMAX7219_SEND_DATA(0x0C, 0x01);
}

void dMAX7219_SEND_DATA(uint8_t diaChi, uint8_t giaTri){
    uint8_t data[2];
	data[0] = diaChi;
	data[1] = giaTri;
	wiringPiSPIDataRW(0, data, 2);
}

void dMAX7219_CLEAR_DISPLAY(){
    for(int i = 0; i < 8; i++){
        dMAX7219_BUFFER[i] = 0x00;
    }
    for(int i = 0; i<8 ; i++){
        dMAX7219_SEND_DATA(i+1, dMAX7219_BUFFER[i]);
    }
}

void dMAX7219_FILL_DISPLAY(){
    for(int i = 0; i < 8; i++){
        dMAX7219_BUFFER[i] = 0xff;
    }
    dMAX7219_SEND_DISPLAY();
}

void dMAX7219_SET_PIXEL(uint8_t toaDoX, uint8_t toaDoY){
    dMAX7219_BUFFER[toaDoY] |= (1 << toaDoX);
    dMAX7219_SEND_DISPLAY();
}

void dMAX7219_CLEAR_PIXEL(uint8_t toaDoX, uint8_t toaDoY){
    dMAX7219_BUFFER[toaDoY] &= ~(1 << toaDoX);
    dMAX7219_SEND_DISPLAY();
}

void dMAX7219_SEND_DISPLAY(){
    for(int i = 0; i<8 ; i++){
        dMAX7219_SEND_DATA(i+1, dMAX7219_BUFFER[i]);
    }
}

void dMAX7219_SET_INTENSITY(uint8_t doSang){
    dMAX7219_SEND_DATA(0x0A, doSang);
}

void dMAX7219_SEND_EMOJI(BieuTuong bieuTuong){
    for(int i=0; i<8; i++){
		switch (bieuTuong)
		{
			case bbMatCuoi:
				dMAX7219_SEND_DATA(i+1, matCuoi[i]);
				break;
			case bbMatBuon:
				dMAX7219_SEND_DATA(i+1, matBuon[i]);
				break;
		}   
    }
}