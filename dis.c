#include "dis.h"
#include "Nano100Series.h"
//#include <stdio.h>
#include "font5x7.c"

void LCD_Delay(u32 t){
	
	unsigned int i, j;
	for(i=0;i<t;i++){
		for(j=0;j<3;j++){
			__nop();
		}
	}
	return;
}



void LCD_Init(){
	//done by main.GPIO_Init
	//GPIO_SetMode(PA, BIT7|BIT6|BIT5|BIT4|BIT3, GPIO_PMD_OUTPUT);
	//GPIO_SetMode(PC, BIT7, GPIO_PMD_OUTPUT);
	//PA3 =1;PA4=1;PA5=1;PA6=1;PA7=1;PC7=0;
	
	//0 reset chip
	LCD_RST = 0;
	LCD_Delay(5);
	LCD_RST = 1;
	LCD_Delay(5);
	
	//�Ĵ�����λ
	LCD_Command(0xE2);//0xaf��ʾ����,0xae��ʾ����
	LCD_Delay(1);
	LCD_Command(0xAE);//0xaf��ʾ����,0xae��ʾ����
	LCD_Command(0xA3);//0xa4������ʾ,0xa5ȫ������,0xA3 ?
	LCD_Command(0xA0);//0xa1,��ʾ��������0-127;0xa0,��ʾ��������3-131
	LCD_Command(0xC8);//0xc8�����������(��Ϊ����);0x80�������(��Ϊ����)
	LCD_Command(0xA6);//0xa6������ʾ,0xa7������ʾ
	LCD_Command(0x21);
	LCD_Command(0x81);//�������öԱȶ������ѹV0 
	LCD_Command(0x20);//Ϊ�Աȶȵĵڶ���ָ��,�Աȶȵ�ѹ�ĵȼ�(0x00-0x3f) 
	LCD_Command(0x2F);//�ڲ���Դѡ��(0x28-0x2f,Ӧ��0x2f) 
	LCD_Command(0xAF);//0xaf��ʾ����,0xae��ʾ����
	
	return;
}


void LCD_Command(u8 c){
	
	LCD_RS = 0;//command
	LCD_DE = 0; //0=enable data
	
//	LCD_CLK = 0;
	
	for(u8 i=0;i<8;i++){
		
		LCD_CLK = 0;
		LCD_DAT = (c&0x80)?1:0;
		c <<= 1;
		LCD_CLK = 1;
	}

	LCD_DE = 1; //0=enable data
	
	return;
}

void LCD_Data(u8 c){
	
	LCD_RS = 1;//data
	LCD_DE = 0; //0=enable data
	
//	LCD_CLK = 0;
	
	for(u8 i=0;i<8;i++){
		
		LCD_CLK = 0;
		LCD_DAT = (c&0x80)?1:0;
		c <<= 1;
		LCD_CLK = 1;
	}

	LCD_DE = 1; //0=enable data
	
	return;
}


void LCD_Fill(u8 c){
	
	LCD_Command(0xB0);//ҳ��ַ��0-7��
	LCD_Command(0x10);//�е�ַ��4λ��0-131��
	LCD_Command(0x00);//�е�ַ��4λ��0-131��
	for(u8 i=0;i<128;i++){
		LCD_Data(c);
	}
	
	LCD_Command(0xB1);
	LCD_Command(0x10);
	LCD_Command(0x00);
	for(u8 i=0;i<128;i++){
		LCD_Data(c);
	}
	
	LCD_Command(0xB2);
	LCD_Command(0x10);
	LCD_Command(0x00);
	for(u8 i=0;i<128;i++){
		LCD_Data(c);
	}
	
	LCD_Command(0xB3);
	LCD_Command(0x10);
	LCD_Command(0x00);
	for(u8 i=0;i<128;i++){
		LCD_Data(c);
	}
	
	return;
}

void LCD_Char(char c){
	
//	#define FONT_BIT(c, column, row) \
//  ((font_data[(c)+(column)] & 1<<(7-(row))) != 0)
	
	//LCD_Data(0x00);
	for(u8 i=0;i<5;i++){
		LCD_Data(font_data[c*5+i]);
	}
	LCD_Data(0x00);
	
	return;
}
void LCD_String(char *st, u8 len){
	
	for(u8 i =0;i<len;i++){
		LCD_Char(st[i]);
	}
	
	return;
}

void LCD_setPos(u8 x, u8 y){
	
	LCD_Command(0xB0 + y);
	LCD_Command(0x10);
	LCD_Command(0x00 + x);
	
	return;
}






