#include"keyboard.h"
#include"lcd.h"
#include"calc.h"
#include<stdio.h>
unsigned char buffin[41];
unsigned char buffout[20];
unsigned char buffin_top=0;

static void in_dis()
{
    //unsigned char i;
    if(buffin_top>15)
    {
        move_chose(MOVE_FRAME,MOVE_LEFT);
        /*
        //change
        set_addr(LINE2_BEGIN+buffin_top-16);
        for(i=0;i<16;i++)
        {
            write_data(buffout[i]);
        }
        set_addr(buffin_top);
        //change end
        */

    }
    write_data(buffin[buffin_top-1]);
}

static void backspace()
{
    //unsigned char i;
    if(buffin_top==0)
        return ;
    if(buffin_top>15)
    {
        move_chose(MOVE_FRAME,MOVE_RIGHT);
        /*
        //change
        set_addr(LINE2_BEGIN+buffin_top-16);
        for(i=0;i<16;i++)
        {
            write_data(buffout[i]);
        }
        set_addr(buffin_top);
        //change end
        */
    }
    --buffin_top;
    set_addr(buffin_top);
    write_data(0x20);
    set_addr(buffin_top);
}


static void operate(char ord)
{
    switch(ord)
    {
    case -2:
        backspace();
        break;
    case -3:
        calc_driver();
        break;
    case -4:
        buffin_top=0;
        clear();
        break;
    default:
        break;
    }
}

void get_char()
{
    char key;
    key=get_key();
    if(key==-1)
        return ;
    if(key>0)
    {
        if(buffin_top<39)
        {
            buffin[buffin_top]=key;
            buffin_top++;
            in_dis();
        }
    }
    else
    {
        operate(key);
    }
}


void printk()
{
    unsigned char i;
    if(buffin_top>15)
        set_addr(LINE2_BEGIN+buffin_top-15);
    else
        set_addr(LINE2_BEGIN);
    for(i=0;i<16;i++)
    {
        write_data(buffout[i]);
    }
    set_addr(buffin_top);
}
