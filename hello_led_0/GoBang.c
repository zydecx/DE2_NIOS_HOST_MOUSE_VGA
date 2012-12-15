#include <stdlib.h>
#include <stdio.h>
#include "system.h"
#include "basic_io.h"
#include "VGA.h"
#include "GoBang.h"
#include "HZK16.h"
#include "ASC16.h"

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
        for (ey = BOARD_TOP_EDGE; ey < (BOARD_CELL_NO-1)*BOARD_VER_MARGIN+BOARD_TOP_EDGE; ey++)
            Vga_Set_Pixel(VGA_0_BASE, ((ex-1)*BOARD_HOR_MARGIN+BOARD_LEFT_EDGE), ey);
            
        for (ey = BOARD_LEFT_EDGE; ey < (BOARD_CELL_NO-1)*BOARD_HOR_MARGIN+BOARD_LEFT_EDGE; ey++)
            Vga_Set_Pixel(VGA_0_BASE, ey, ((ex-1)*BOARD_VER_MARGIN+BOARD_TOP_EDGE));
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
void gobang_draw_box(int width, int height, int posx, int posy)
{
    int ex, ey;
    for (ex=posx; ex<posx+width; ++ex)
        for (ey=posy; ey<posy+height; ++ey)
            Vga_Clr_Pixel(VGA_0_BASE, ex, ey);
    for (ex=posx; ex<posx+width; ++ex)
    {
        Vga_Set_Pixel(VGA_0_BASE, ex, posy);
        Vga_Set_Pixel(VGA_0_BASE, ex, (posy+height-1));
    }
    for (ey=posy; ey<posy+height; ++ey)
    {
        Vga_Set_Pixel(VGA_0_BASE, posx, ey);
        Vga_Set_Pixel(VGA_0_BASE, (posx+width-1), ey);
    }
}
//-------------------------------------------------------------------------
void gobang_game_start()
{
    Set_Pixel_On_Color(1023,1023,1023);
    reset_piece_record_array();
    clean_screen();
    gobang_board_display(); 
    
    gobang_draw_box(130, 420, 475, 30); 
    unsigned char text1[] = " 五子棋对战平台";
//    五
//    25788
//    子
//    30756
//    棋
//    21276
//    游
//    28470
//    戏
//    26076
//    平
//    21036
//    台
//    24294
//    int text11[]={25788,30756,21276,28470,26076,21036,24294};
    unsigned char text2[] = "Welcome to Play";
    unsigned char text3[] = " GOBANG GAME!! ";
    unsigned char text4[] = "    VER 1.1    ";
    unsigned char text5[] = "15th, Dec, 2012";
    gobang_show_text(text1, 480, 70);
//    gobang_show_chinese(text11, 480, 70);
    gobang_show_text(text2, 480, 100);
    gobang_show_text(text3, 480, 130);
    gobang_show_text(text4, 480, 210);
    gobang_show_text(text5, 480, 240);
    gobang_show_text(text1, 480, 180);
}
//-------------------------------------------------------------------------
void gobang_win_display(unsigned int isWhite)
{
    if (isWhite == 1)
    {
        gobang_show_text("   白方获胜！  ", 480, 320);
        gobang_show_text("   亮爷二逼！  ", 480, 360);
        Set_Pixel_On_Color(0,1013,408);    //Green
//        Set_Pixel_On_Color(612,816,816);    //Light Blue
    }
    else
    {
        gobang_show_text("   黑方获胜！  ", 480, 320);
        gobang_show_text("   亮爷二逼！  ", 480, 360);
        Set_Pixel_On_Color(1023,408,0);    //Orange
//        Set_Pixel_On_Color(1023,612,408);    //Orange
    }
}
//-------------------------------------------------------------------------
void gobang_show_char(unsigned char* charac, int isASC, int posx, int posy)
{
    int i, j, tposy, tposx;
    tposy = posy;
    tposx = posx;
    if (isASC == 1)
    {
        for (i=0; i<16; ++i)
        {
            for (j=7; j>=0; --j)
            {
                if ((charac[i] >> j) & 0x01)
                {  
                    Vga_Set_Pixel(VGA_0_BASE, tposx, tposy); 
//                    Vga_Set_Pixel(VGA_0_BASE, tposx++, tposy);
                }
                else
                {
                    Vga_Clr_Pixel(VGA_0_BASE, tposx, tposy);
//                    Vga_Clr_Pixel(VGA_0_BASE, tposx++, tposy);
                }
                tposx++;
            }
            tposy++;
            tposx = posx;
        }
    }
    else
    {
        for (i=0; i<32; ++i)
        {
            for (j=7; j>=0; --j)
            {
                if ((charac[i] >> j) & 0x01)
                {  
                    Vga_Set_Pixel(VGA_0_BASE, tposx, tposy); 
//                    Vga_Set_Pixel(VGA_0_BASE, tposx++, tposy);
                }
                else
                {
                    Vga_Clr_Pixel(VGA_0_BASE, tposx, tposy);
//                    Vga_Clr_Pixel(VGA_0_BASE, tposx++, tposy);
                }
                tposx++;
            }
            if ((i%2) == 1)
            {
                tposy++;
                tposx = posx;
            }
        }
    }
}
//-------------------------------------------------------------------------
void gobang_show_text(unsigned char* text, int posx, int posy)
{
    unsigned char char_table[32];
    int i, j, offset, isASC;
    i=0;
    while (i <strlen(text))
    {
        if (text[i] == NULL)
        {
            for (j=0; j<8; ++j)
            {
                Vga_Clr_Pixel(VGA_0_BASE, posx, posy);
                posx++;
            }
            i++;
        }
        else if ((text[i] - 0xa0)<0)
        {
            isASC = 1;
            offset = (text[i] - 0x00) * 16;
            for (j=0; j<16; ++j)
            {
                char_table[j] = ASCII8x16_Table[offset+j];
//                offset++; 
            }
            gobang_show_char(char_table, isASC, posx, posy);
            posx += 8;
            i++;
        }
        else
        {
//            Set_Pixel_On_Color(0,1013,408);
            isASC = 0;
            offset = (((text[i] - 0xa0) - 1) * 94 + ((text[i+1] - 0xa0) - 1))*32;
//            offset = 137536;
            for (j=0; j<32; ++j)
            {
                char_table[j] = GBK2312_8x16_Table[offset+j];
//                offset++; 
            }
            gobang_show_char(char_table, isASC, posx, posy);
            posx += 16;
            i += 2;
        }
    }
}
//-------------------------------------------------------------------------
void gobang_show_chinese(int* text, int posx, int posy)
{
    char char_table[32];
    int i, j, offset, isASC;
    i=0;
    while (i <7)
    {
        isASC = 0;
        offset = (text[i]/6)*32;
        for (j=0; j<32; ++j)
        {
            char_table[j] = GBK2312_8x16_Table[offset+j];
        }
        gobang_show_char(char_table, isASC, posx, posy);
        posx += 16;
        ++i;
    }
}
//-------------------------------------------------------------------------

