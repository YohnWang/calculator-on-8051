#include<reg51.h>
#define KEY_P P1

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
static char keyscan1()
{
    char result=-1,i=100;
    KEY_P=0xf0;
    if(KEY_P!=0xf0)
    {
        delayms(1);
        if(KEY_P!=0xf0)
        {
            switch(KEY_P)
            {
                case 0x70:result=0;break;
                case 0xb0:result=4;break;
                case 0xd0:result=8;break;
                case 0xe0:result=12;break;
                default:result=-1;break;
            }
            KEY_P=0x0f;
            switch(KEY_P)
            {
                case 0x07:result+=0;break;
                case 0x0b:result+=1;break;
                case 0x0d:result+=2;break;
                case 0x0e:result+=3;break;
                default:result=-1;break;
            }
            while(KEY_P!=0x0f && i--)
            {
                delayms(1);
            }
        }
    }
    return result;
}

static char keyscan2()
{
    char result=-1,i=100;
    if(P3!=0xff)
    {
        delayms(1);
        if(P3!=0xff)
        {
            switch(P3)
            {
                case 0xfe:result=16;break;
                case 0xfd:result=17;break;
                case 0xfb:result=18;break;
                case 0xf7:result=19;break;
                case 0xef:result=20;break;
                case 0xdf:result=21;break;
                case 0xbf:result=22;break;
                case 0x7f:result=23;break;
            }
        }
        while(P3!=0xff && i--)
        {
            delayms(1);
        }
    }
    return result;
}
static char keyscan()
{
    char ret;
    ret=keyscan1();
    if(ret!=-1)
        return ret;
    ret=keyscan2();
    if(ret!=-1)
        return ret;
    return ret;
}

char get_key()
{
    char ret;
    char i=keyscan();
    switch(i)
    {
    case 0:ret='1';break;
    case 1:ret='2';break;
    case 2:ret='3';break;
    case 3:ret='+';break;
    case 4:ret='4';break;
    case 5:ret='5';break;
    case 6:ret='6';break;
    case 7:ret='-';break;
    case 8:ret='7';break;
    case 9:ret='8';break;
    case 10:ret='9';break;
    case 11:ret='*';break;
    case 12:ret='$';break;
    case 13:ret='0';break;
    case 14:ret='.';break;
    case 15:ret='/';break;
    case 16:ret='(';break;
    case 17:ret=')';break;
    case 18:ret=-2;break;
    case 19:ret=-3;break;
    case 20:ret=-1;break;
    case 21:ret=-1;break;
    case 22:ret=-1;break;
    case 23:ret=-4;break;
    default:ret=-1;break;
    }
    return ret;
}

