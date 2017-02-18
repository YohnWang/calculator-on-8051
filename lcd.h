#ifndef LCD_H
#define LCD_H

extern void write_com(unsigned char com);
extern void write_data(unsigned char dat);

#define CLEAR  (0x01)
#define HOMING (0x02)
#define clear() write_com(CLEAR)
#define home()  write_com(HOMING)

#define SET_INPUT (0x04)
#define AC_INC    (0x02)
#define AC_DEC    (0x00)
#define FRAME_MOVE (0x01)
#define FRAME_STATIC (0x00)
#define input_way(ac,fr) write_com(SET_INPUT|ac|fr)

#define CTRL_DIS (0x08)
#define OPEN_DIS (0x04)
#define CLOSE_DIS (0x00)
#define OPEN_CURSOR (0x02)
#define CLOSE_CURSOR (0x00)
#define OPEN_FLASH  (0x01)
#define CLOSE_FLASH (0x00)
#define ctrl_dis(d,c,b) write_com(CTRL_DIS|d|c|b)

#define MOVE_CHOSE (0x10)
#define MOVE_FRAME (0x08)
#define MOVE_CURSOR (0x00)
#define MOVE_RIGHT (0x04)
#define MOVE_LEFT (0x00)
#define move_chose(sc,rl) write_com(MOVE_CHOSE|sc|rl)

#define SET_FUNC (0x20)
#define DATA_INF_8 (0x10)
#define DATA_INF_4 (0x00)
#define LINE_2     (0x08)
#define LINE_1     (0x00)
#define F_FUNC     (0x00)
#define set_func(line) write_com(SET_FUNC|DATA_INF_8|line)

#define SET_ADDR (0x80)
#define LINE1_BEGIN (0x00)
#define LINE2_BEGIN (0x40)
#define set_addr(addr) write_com(SET_ADDR|(addr))






// ‰»Î∑Ω Ω
//#define
//#define input_way(is_ac_add,is_frame_move) write_com(0x)


#endif
