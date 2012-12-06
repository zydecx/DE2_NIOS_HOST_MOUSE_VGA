#include "system.h"
#include "basic_io.h"
#include "VGA.h"
#include "GOMOKU.h"

//-------------------------------------------------------------------------
void clean_screen()
{
    int ex, ey;
    for (ex=0; ex<VGA_WIDTH; ++ex)
        for (ey=0; ey<VGA_HEIGHT; ++ey)
            Vga_Clr_Pixel(VGA_0_BASE, ex, ey);
}
//-------------------------------------------------------------------------
void gomoku_board_display()
{
   int ex, ey;
   for (ex = 1; ex <= BOARD_CELL_NO; ++ex)
   {
        for (ey = BOARD_TOP_EDGE; ey < BOARD_CELL_NO*BOARD_VER_MARGIN; ey++)
            Vga_Set_Pixel(VGA_0_BASE, ex*BOARD_HOR_MARGIN, ey);
            
        for (ey = BOARD_LEFT_EDGE; ey < BOARD_CELL_NO*BOARD_HOR_MARGIN; ey++)
            Vga_Set_Pixel(VGA_0_BASE, ey, ex*BOARD_VER_MARGIN);
   }
}
//-------------------------------------------------------------------------
//void gomoku_game_start()
//{
//    clean_screen();
//    gomoku_board_display();
//}
//-------------------------------------------------------------------------
