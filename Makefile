#Biên dịch chương trình SNAKEGAME - ngtrdai
SOURCE_SNAKE = dSNAKE_GAME.c dMPU6050.c dMAX7219_Matrix.c
CC =  gcc
SOURCE_LIB = -lm -lwiringPi

build: $(SOURCE_SNAKE)
	$(CC) $? -o run $(SOURCE_LIB)