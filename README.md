# SNAKE GAME IN EMBEDDED - RẮN SĂN MỒI VỚI MPU6050
***Note: Đây chỉ là trò chơi tác giả làm với mục đích sở thích cá nhân.***

## Giới thiệu
Source code này là một bài tập trên lớp, ***đề bài yêu cầu*** sử dụng RASPBERRY PI và MPU6050, MATRIX LED 8x8. Vì thế mọi người đừng hỏi sao lại dùng RPi để làm một trò chơi đơn giản thế này.

## Thiết lập phần cứng
### MPU6050
| **MPU6050 PIN** | **RASPBERRYPI PIN** |
|-----------------|---------------------|
| VCC             | 3.3V hoặc 5.0V      |
| GND             | 0V                  |
| SCL             | SCL (GPIO.3)        |
| SDA             | SDA (GPIO.2)        |
| ADO             | 0V                  |
| INT             | GPIO.0              |
### Matrix led 8x8
| **MAX7219 MATRIX LED 8x8 PIN** | **RASPBERRYPI PIN** |
|--------------------------------|---------------------|
| VCC                            | 3.3V hoặc 5.0V      |
| GND                            | 0V                  |
| DIN                            | MOSI (GPIO.10)      |
| CLK                            | SCLK (GPIO.11)      |
| CS                             | CE0 (GPIO.8)        |
## Biên dịch code và chạy chương trình
```
  # Biên dịch code
  make hoặc make build
  
  # Chạy chương trình
  ./run
```
