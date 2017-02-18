#include<reg51.h>

sbit LCD_EN=P2^7;
sbit LCD_RS=P2^6;
sbit LCD_RW=P2^5;

static void delayms(unsigned char t)
{
    unsigned char i, j;
	for(;t;--t)
    {
        for(i=25;i;--i)
        {
            for(j=40;j;--j){}
        }
    }
}

void write_com(unsigned char com)
{
    LCD_EN=0;
    LCD_RS=0;
    LCD_RW=0;
    P0=com;
    delayms(1);
    LCD_EN=1;
    delayms(5);
    LCD_EN=0;
}
void write_data(unsigned char dat)
{
    LCD_EN=0;
    LCD_RS=1;
    LCD_RW=0;
    P0=dat;
    delayms(1);
    LCD_EN=1;
    delayms(5);
    LCD_EN=0;
}
