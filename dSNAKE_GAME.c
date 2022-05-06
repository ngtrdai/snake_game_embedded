/*
*   @file dSNAKE_GAME.c
*   @author ngtrdai
*   @date 30/04/2022
*/

#include "./header/dSNAKE_GAME.h"

/// KHAI BÁO KIỂU DỮ LIỆU TRẠNG THÁI
HuongDiChuyen huongDiChuyen = DUNG_YEN;
TrangThai trangThai = CON_SONG;
bool err;
uint8_t diemSo = 0;

/*
* KHAI BÁO RẮN
*/
uint8_t doDaiToiDa = 10;            // ĐỘ DÀI TỐI ĐA CỦA RẮN.
int8_t ranX[10];                    // TOẠ ĐỘ X CỦA RẮN.
int8_t ranY[10];                    // TOẠ ĐỘ Y CUẢ RẮN.
int8_t ranX_prev[10];               // TOẠ ĐỘ X CŨ CỦA RẮN.
int8_t ranY_prev[10];               // TOẠ ĐỘ Y CŨ CỦA RẮN.
uint8_t doDaiRan;                   // ĐỘ DÀI HIỆN TẠI CỦA RẮN.

/*
* KHAI BÁO THỨC ĂN
*/
uint8_t moiX, moiY;                 // TOẠ ĐỘ X, Y CỦA MỒI.

/*
* KHAI BÁO THỜI GIAN XUẤT HIỆN CỦA MỒI VÀ TỐC ĐỘ DI CHUYỂN CỦA RẮN.
*/

/// 5s TẠO VỊ TRÍ NGẪU NHIÊN CHO MỒI.
unsigned long moiTime_prev = 0;
unsigned long moiTime_delay = 5000;

/// TỐC ĐỘ LÀM TƯƠI CỦA RẮN LÀ 250ms.
unsigned long ranTime_prev  = 0;
unsigned long ranTime_delay = 250;

#pragma region CHƯƠNG TRÌNH CHÍNH
int main(){
    dSNAKE_SETUP();
    dSNAKE_KHOI_TAO_RAN();
    while(1){
        unsigned long ranTime_curr = millis();     // BẬT BỘ ĐẾM THỜI GIAN
        switch (trangThai)
        {
            case CON_SONG:
                
                // NẾU ĐỦ THỜI GIAN DELAY THÌ THỰC HIỆN TẠO MỚI MÀN HÌNH TRÒ CHƠI TIẾP THEO.
                if(ranTime_curr - ranTime_prev >= ranTime_delay){
                    dSNAKE_CHUONG_TRINH();
                    ranTime_prev = ranTime_curr;
                }
                break;
            case THANG:
                dSNAKE_XU_LY_THANG_THUA();
                break;
            case THUA:
                dSNAKE_XU_LY_THANG_THUA();
                break;
        }   
    }
    return 0;
}

void dSNAKE_CHUONG_TRINH(){
    if(err == DUNG){
        dSNAKE_DIEU_KHIEN_RAN();
        dSNAKE_VE_MAN_HINH();      
    } else {
        printf("KẾT NỐI MPU6050 THẤT BẠI\n");
        delay(500);
    }
}
#pragma endregion CHƯƠNG TRÌNH CHÍNH

#pragma region CẤU HÌNH

void dSNAKE_SETUP(){
    // Cấu hình GPIO
    wiringPiSetup();
    wiringPiISR(PIN_INT, INT_EDGE_RISING, &dSNAKE_XULYNGAT);

    // Cấu hình MPU6050
    err = MPU6050_INIT(0X09, 0x03, 0x00, 0x00, 0x01, 0x01);

    // Cấu hình LED Ma trận
    dMAX7219_MATRIX_INIT(0, 8000000);
}

void dSNAKE_KHOI_TAO_RAN(){
    doDaiRan = 3;

    ranX[0] = 7;
    ranY[0] = 2;
    ranX[1] = 7;
    ranY[1] = 1;
    ranX[2] = 7;
    ranY[2] = 0;

    for(int i=doDaiRan; i<doDaiToiDa; i++){
        ranX[i] = ranY[i] = -1;
    }
    dSNAKE_TAO_THUC_AN();
}

#pragma endregion CẤU HÌNH

#pragma region HÀM VẼ RẮN VÀ THỨC ĂN

void dSNAKE_VE_RAN(){
    for(int i=0; i<doDaiRan; i++){
        dMAX7219_CLEAR_PIXEL(ranX_prev[i], ranY_prev[i]);
    }
    for(int i=0; i<doDaiRan; i++){
        dMAX7219_SET_PIXEL(ranX[i], ranY[i]);
    }
}

void dSNAKE_VE_THUC_AN(){
    unsigned long moiTime_curr = millis();
    if(moiTime_curr - moiTime_prev >= moiTime_delay){
        moiTime_prev = moiTime_curr;
        dMAX7219_CLEAR_PIXEL(moiX, moiY);
        dSNAKE_TAO_THUC_AN();
    }
    dMAX7219_SET_PIXEL(moiX, moiY);
}

void dSNAKE_VE_MAN_HINH(){
    dSNAKE_VE_RAN();
    dSNAKE_VE_THUC_AN();
}

#pragma endregion HÀM VẼ RẮN VÀ THỨC ĂN

#pragma region HÀM TẠO THỨC ĂN
void dSNAKE_TAO_THUC_AN(){
    uint8_t moiX_temp, moiY_temp;
    moiX_temp = dSNAKE_TAO_SO_NGAU_NHIEN(0, 7);
    moiY_temp = dSNAKE_TAO_SO_NGAU_NHIEN(0, 7);
    while(dSNAKE_KIEM_TRA_TRUNG_VOI_RAN == DUNG){
        moiX_temp = dSNAKE_TAO_SO_NGAU_NHIEN(0, 7);
        moiY_temp = dSNAKE_TAO_SO_NGAU_NHIEN(0, 7);
    }
    moiX = moiX_temp;
    moiY = moiY_temp;
}

bool dSNAKE_KIEM_TRA_TRUNG_VOI_RAN(uint8_t toaDoX, uint8_t toaDoY){
    for(int i=0; i<doDaiRan - 1; i++){
        if(toaDoX == ranX[i] && toaDoY == ranY[i]){
            return DUNG;
        }
    }
    return SAI;
}
#pragma endregion HÀM TẠO THỨC ĂN

#pragma region XỬ LÝ VÀ ĐIỀU KHIỂN
void dSNAKE_XULYNGAT(){
    struct MPU_ANGLE Value = MPU_REALTIME_VALUE();
    // printf("aX: %f // aY: %f //\n", Value.angleX, Value.angleY);
    if((Value.angleX >= 50) && (Value.angleY > -25 && Value.angleY < 25)){
        huongDiChuyen = PHAI;
    }else if((Value.angleX <= -50) && (Value.angleY > -25 && Value.angleY < 25)){
        huongDiChuyen = TRAI;
    }
    if((Value.angleY >= 50) && (Value.angleX > -25 && Value.angleX < 25)){
        huongDiChuyen = LEN;
    }else if((Value.angleY <= -50) && (Value.angleX > -25 && Value.angleX < 25)){
        huongDiChuyen = XUONG;
    }
    MPU_XOA_CO_NGAT();
}

void dSNAKE_DIEU_KHIEN_RAN(){
    if(huongDiChuyen != DUNG_YEN){
        for(int i = doDaiRan; i>0; i--){
            ranX_prev[i] = ranX[i];
            ranY_prev[i] = ranY[i];
            if((huongDiChuyen == XUONG) && (ranX[0] == 8)){
                ranX[0] = -1;
            } else if((huongDiChuyen ==  LEN) && (ranX[0] == -1)){
                ranX[0] = 8;
            } else {
                ranX[i] = ranX[i-1];
            }
            if((huongDiChuyen == TRAI) && (ranY[0] == -1)){
                ranY[0] = 8;
            } else if((huongDiChuyen == PHAI) && (ranY[0] == 8)){
                ranY[0] = -1;
            } else {
                ranY[i] = ranY[i - 1];
            }
        }
    }    

    switch (huongDiChuyen)
    {
        case TRAI:
            ranY[0] = ranY[0] - 1;
            break;
        case XUONG:
            ranX[0] = ranX[0] + 1;
            break;
        case PHAI:
            ranY[0] = ranY[0] + 1;
            break;
        case LEN:
            ranX[0] = ranX[0] - 1;
    }

    if((ranX[0] == moiX) && (ranY[0] == moiY)){
        doDaiRan++;
        diemSo++;
        printf("ĐIỂM HIỆN TẠI: %d\n", diemSo);
        if(doDaiRan < doDaiToiDa){
            dSNAKE_TAO_THUC_AN();
        }else{
            moiX = moiY = -1;
        }
    }
    dSNAKE_KIEM_TRA_THANG_THUA();
}
#pragma endregion XỬ LÝ VÀ ĐIỀU KHIỂN

#pragma region XỬ LÝ THẮNG THUA

void dSNAKE_KIEM_TRA_THANG_THUA(){
    for(int i = 1; i<doDaiRan; i++){
        if((ranX[0] == ranX[i]) && (ranY[0] == ranY[i])){
            trangThai = THUA;
            printf("BẠN THUA RỒI!!!\n");
        }
    }
    if(doDaiRan == doDaiToiDa){
        trangThai = THANG;
        printf("BẠN ĐÃ CHIẾN THẮNG!!!\n");
    }
}

void dSNAKE_XU_LY_THANG_THUA(){
    trangThai == THANG ? dMAX7219_SEND_EMOJI(bbMatCuoi) : dMAX7219_SEND_EMOJI(bbMatBuon);
    delay(2000);
    dMAX7219_CLEAR_DISPLAY();
    dMAX7219_CLEAR_PIXEL(moiX, moiY);    
    dSNAKE_KHOI_TAO_RAN();
    diemSo = 0;
    trangThai = CON_SONG;
}

#pragma endregion XỬ LÝ THẮNG THUA

#pragma region HÀM PHỤ TRỢ

uint8_t dSNAKE_TAO_SO_NGAU_NHIEN(int min,int max){
    return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}

#pragma endregion HÀM PHỤ TRỢ
