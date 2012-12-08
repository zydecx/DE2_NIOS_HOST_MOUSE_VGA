
#include "system.h"
#include "basic_io.h"
#include "LCD.h"
#include "Test.h"
#include "sys/alt_irq.h"
#include "VGA.C"
#include "HAL4D13.C"


#include "isa290.h"
#include "reg.h"
#include "buf_man.h"
#include "port.h"
#include "usb.h"
#include "ptd.h"
#include "cheeyu.h"
#include "mouse.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <io.h>
#include <fcntl.h>
#include "mouse.c"
#include "cheeyu.c"
#include "ptd.c"
#include "usb.c"
#include "buf_man.c"
#include "reg.c"
#include "port.c"
#include "GoBang.h"

unsigned int		hc_data;
unsigned int		hc_com;
unsigned int		dc_data;
unsigned int		dc_com;

//extern int Board_Piece_Record[BOARD_CELL_NO][BOARD_CELL_NO]; 

int main(void)
{
  VGA_Ctrl_Reg vga_ctrl_set;
  
  vga_ctrl_set.VGA_Ctrl_Flags.RED_ON    = 1;
  vga_ctrl_set.VGA_Ctrl_Flags.GREEN_ON  = 1;
  vga_ctrl_set.VGA_Ctrl_Flags.BLUE_ON   = 1;
  vga_ctrl_set.VGA_Ctrl_Flags.CURSOR_ON = 1;
  
  Vga_Write_Ctrl(VGA_0_BASE, vga_ctrl_set.Value);
  Set_Pixel_On_Color(1023,1023,1023);
  Set_Pixel_Off_Color(256,256,256);
  Set_Cursor_Color(576,768,0);
  
//  reset_piece_record_array();
//  clean_screen();
//  gobang_board_display();
  gobang_game_start();
//  int ex;
//  for(ex=30;ex<450;ex++)
//  {
//    Vga_Set_Pixel(VGA_0_BASE,40,ex);
//    Vga_Set_Pixel(VGA_0_BASE,80,ex);
//    Vga_Set_Pixel(VGA_0_BASE,120,ex);
//    Vga_Set_Pixel(VGA_0_BASE,160,ex);
//    Vga_Set_Pixel(VGA_0_BASE,200,ex);
//    Vga_Set_Pixel(VGA_0_BASE,240,ex);
//    Vga_Set_Pixel(VGA_0_BASE,280,ex);
//    Vga_Set_Pixel(VGA_0_BASE,320,ex);
//    Vga_Set_Pixel(VGA_0_BASE,360,ex);
//    Vga_Set_Pixel(VGA_0_BASE,400,ex);
//    Vga_Set_Pixel(VGA_0_BASE,440,ex);
//    Vga_Set_Pixel(VGA_0_BASE,480,ex);
//    Vga_Set_Pixel(VGA_0_BASE,520,ex);
//    Vga_Set_Pixel(VGA_0_BASE,560,ex);
//    Vga_Set_Pixel(VGA_0_BASE,600,ex);
//  }
//  
//  int ex2;
//  for(ex2=40;ex2<600;ex2++)
//  {
//    Vga_Set_Pixel(VGA_0_BASE,ex2,30);
//    Vga_Set_Pixel(VGA_0_BASE,ex2,60);
//    Vga_Set_Pixel(VGA_0_BASE,ex2,90);
//    Vga_Set_Pixel(VGA_0_BASE,ex2,120);
//    Vga_Set_Pixel(VGA_0_BASE,ex2,150);
//    Vga_Set_Pixel(VGA_0_BASE,ex2,180);
//    Vga_Set_Pixel(VGA_0_BASE,ex2,210);
//    Vga_Set_Pixel(VGA_0_BASE,ex2,240);
//    Vga_Set_Pixel(VGA_0_BASE,ex2,270);
//    Vga_Set_Pixel(VGA_0_BASE,ex2,300);
//    Vga_Set_Pixel(VGA_0_BASE,ex2,330);
//    Vga_Set_Pixel(VGA_0_BASE,ex2,360);
//    Vga_Set_Pixel(VGA_0_BASE,ex2,390);
//    Vga_Set_Pixel(VGA_0_BASE,ex2,420);
//    Vga_Set_Pixel(VGA_0_BASE,ex2,450);
//  }
  
  LCD_Test();

  w16(HcReset,0x00F6);//reset      
  reset_usb();//config  
  mouse();
  return 0;
}

