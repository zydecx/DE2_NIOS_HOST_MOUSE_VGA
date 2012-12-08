#include "system.h"
#include "basic_io.h"
#include "VGA.h"
#include "GoBang.h"

//-------------------------------------------------------------------------
void clean_screen()
{
    int ex, ey;
    for (ex=0; ex<VGA_WIDTH; ++ex)
        for (ey=0; ey<VGA_HEIGHT; ++ey)
            Vga_Clr_Pixel(VGA_0_BASE, ex, ey);
}
//-------------------------------------------------------------------------
void gobang_board_display()
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
void reset_piece_record_array()
{
    int ex, ey, ez;
    for (ex = 0; ex < BOARD_CELL_NO; ++ex)
        for (ey = 0; ey < BOARD_CELL_NO; ++ey)
        {
            Piece_Record[ex][ey] = 0;
            for (ez = 0; ez < 8; ++ez)
                Piece_Analysis_Record[ex][ey][ez] = 0;
        }
}
//-------------------------------------------------------------------------
void gobang_game_start()
{
    Set_Pixel_On_Color(1023,1023,1023);
    reset_piece_record_array();
    clean_screen();
    gobang_board_display();
}
//-------------------------------------------------------------------------
void gobang_win_display()
{
    Set_Pixel_On_Color(1023,512,0);
}
//-------------------------------------------------------------------------
