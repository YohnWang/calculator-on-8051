#include<reg51.h>
#include"io.h"
#include"lcd.h"

int main()
{
    char i;
    /*init*/
    input_way(AC_INC,FRAME_STATIC);
	ctrl_dis(OPEN_DIS,OPEN_CURSOR,OPEN_FLASH);
	set_func(LINE_2);
	set_addr(0);
	for(i=0;i<20;i++)
    {
        buffout[i]=' ';
    }
    /*init end*/
	for(;;)
    {
        get_char();
    }
}








