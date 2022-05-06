/*
*   @file dSNAKE_GAME.h
*   @author ngtrdai
*   @date 30/04/2022
*/

/*
*   @REGION KHAI BÁO THƯ VIỆN
*/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <wiringPi.h>
#include "dMPU6050.h"
#include "dMAX7219_Matrix.h"

/*
*   @REGION KHAI BÁO IO
*/
#define PIN_INT     0

/*
*   @REGION KHAI BÁO KIỂU DỮ LIỆU
*/

/// HƯỚNG DI CHUYỂN CỦA RẮN.
typedef enum{
    DUNG_YEN,
    PHAI,
    TRAI,
    LEN,
    XUONG
}HuongDiChuyen;

/// KIỂU DỮ LIỆU THỂ HIỆN TRẠNG THÁI CỦA NGƯỜI CHƠI.
typedef enum{
    CON_SONG,
    THANG,
    THUA
}TrangThai;
/*
*   @REGION HÀM KHỞI TẠO CHƯƠNG TRÌNH
*/
void dSNAKE_SETUP();
void dSNAKE_XULYNGAT();
void dSNAKE_CHUONG_TRINH();

/*
*   @REGION HÀM PHỤ TRỢ
*/
uint8_t dSNAKE_TAO_SO_NGAU_NHIEN(int min, int max);

/*
*   @REGION HÀM CHO GAME RẮN SĂN MỒI
*/
/// KHỞI TẠO VỊ TRÍ ĐẦU CỦA RẮN VÀ THỨC ĂN.
void dSNAKE_KHOI_TAO_RAN();
void dSNAKE_TAO_THUC_AN();

/// HÀM KIỂM TRA THỨC ĂN TRÙNG VỚI THÂN RẮN.
bool dSNAKE_KIEM_TRA_TRUNG_VOI_RAN(uint8_t toaDoX, uint8_t toaDoY);

/// HÀM VẼ RẮN VÀ THỨC ĂN.
void dSNAKE_VE_RAN();
void dSNAKE_VE_THUC_AN();

/// VẼ RA MỘT FRAME.
void dSNAKE_VE_MAN_HINH();

/// HÀM ĐIỀU KHIỂN THUẬT TOÁN DI CHUYỂN CỦA RẮN.
void dSNAKE_DIEU_KHIEN_RAN();

/// HÀM KIỂM TRA NGƯỜI CHƠI THẮNG HAY THUA.
void dSNAKE_KIEM_TRA_THANG_THUA();
void dSNAKE_XU_LY_THANG_THUA();
