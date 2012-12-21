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
void gobang_instr_display()
{
    gobang_box_fill(130, 420, 475, 30);
    gobang_box_outline(130, 420, 475, 30);  
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
//    gobang_show_num(75, 480, 160);
    gobang_show_text(text2, 480, 100);
    gobang_show_text(text3, 480, 130);
//    gobang_show_text(text4, 480, 210);
//    gobang_show_text(text5, 480, 240);
//    gobang_show_text(text1, 480, 180);
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
void gobang_box_fill(int width, int height, int posx, int posy)
{
    int ex, ey;
    for (ex=posx; ex<posx+width; ++ex)
        for (ey=posy; ey<posy+height; ++ey)
            Vga_Clr_Pixel(VGA_0_BASE, ex, ey);
}
//-------------------------------------------------------------------------
void gobang_box_outline(int width, int height, int posx, int posy)
{
    int ex, ey;
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
    gobang_instr_display();
}
//-------------------------------------------------------------------------
void gobang_win_display(unsigned int isWhite)
{
    if (isWhite == 1)
    {
//        gobang_show_text("   白方获胜！  ", 480, 360);
//        gobang_show_text("   亮爷二逼！  ", 480, 400);
        Set_Pixel_On_Color(0,1013,408);    //Green
//        Set_Pixel_On_Color(612,816,816);    //Light Blue
    }
    else
    {
//        gobang_show_text("   黑方获胜！  ", 480, 360);
//        gobang_show_text("   亮爷二逼！  ", 480, 400);
        Set_Pixel_On_Color(1023,408,0);    //Orange
//        Set_Pixel_On_Color(1023,612,408);    //Orange
    }
}
//-------------------------------------------------------------------------
void gobang_draw_circle(int radius, int posx, int posy)
{
    int ii, jj;
    for (ii=-radius; ii<(radius+1); ++ii)
    {
        for (jj=-radius; jj<(radius+1); ++jj)
        {   
            if ((ii*ii+jj*jj)>(radius*radius+1))    continue;
            Vga_Set_Pixel(VGA_0_BASE, (posx+ii), (posy+jj));
        }
    }
}
//-------------------------------------------------------------------------
void gobang_clear_circle(int radius, int posx, int posy)
{
    int ii, jj;
    for (ii=-radius; ii<(radius+1); ++ii)
    {
        for (jj=-radius; jj<(radius+1); ++jj)
        {   
            if ((ii*ii+jj*jj)>(radius*radius+1))    continue;
            Vga_Clr_Pixel(VGA_0_BASE, (posx+ii), (posy+jj));
        }
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
    while (i < strlen(text))
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
void gobang_show_num(int num, int posx, int posy)
{
    int i, num_div, num_mod;
    int tnum[20];
    int tnum_size = 0;
    
    if (num < 0)
    {
        num = -num;
        gobang_show_text("-", (posx-8), posy);
    }
    
    num_div = num / 10;
    num_mod = num % 10;
    while (num_div > 0)
    {
        tnum[tnum_size] = num_mod;
        tnum_size++;
        num_mod = num_div % 10;
        num_div = num_div / 10;
    };
    tnum[tnum_size] = num_mod;
    tnum_size++;
    for (i=(tnum_size-1); i>=0; --i)
    {
        unsigned char cnum[] = "0";
        cnum[0] += tnum[i];
        gobang_show_text(cnum, posx, posy);
        posx += 8;
    }
}
//-------------------------------------------------------------------------
unsigned int gobang_handcut_check(int piece_record[][BOARD_CELL_NO][8], unsigned int isWhiteMode, int posx, int posy)
{
    if (isWhiteMode)    return 0;
    
    int piece_next = 0;
    int piece_next2 = 0;    //for the other cordinate of lean direction
    int hand_cut_three = 0;
    int hand_cut_four = 0;
    int hand_cut_six = 0;
    int handcut_record[8][6] = {0};   //8 Directions, 6 Kinds of Handcut
    int i, j;
    for (i=0; i<8; ++i)
        for (j=0; j<6; ++j)
            handcut_record[i][j] = 0;
    ///////////////////////////////////////////////////////////////////
    //         Start check hand-cut of horizontal direction          //
    ///////////////////////////////////////////////////////////////////
    //1-"***"
    if (piece_record[posy][posx][0] == 3)
    {
        handcut_record[0][0]++;
        handcut_record[1][0] = -1;
        hand_cut_three++;
    }
    //2-"** *"
    piece_next = posx - piece_record[posy][posx][1] - 1;
    if (piece_next>=0 && piece_record[posy][posx][0]*piece_record[posy][piece_next][0] == 2 )
    {
        handcut_record[0][1]++;
        hand_cut_three++;
    }
    piece_next = posx + piece_record[posy][posx][0] - piece_record[posy][posx][1] + 2;
    if (piece_next<BOARD_CELL_NO && piece_record[posy][posx][0]*piece_record[posy][piece_next][0] == 2 )
    {
        handcut_record[1][1]++;
        hand_cut_three++;
    }
    //3-"****"
    if (piece_record[posy][posx][0] == 4)
    {
        handcut_record[0][2]++;
        handcut_record[1][2] = -1;
        hand_cut_four++;
    }
    //4-"*** *"
    piece_next = posx - piece_record[posy][posx][1] - 1;
    if (piece_next>=0 && piece_record[posy][posx][0]*piece_record[posy][piece_next][0] == 3 )
    {
        handcut_record[0][3]++;
        hand_cut_four++;
    }
    piece_next = posx + piece_record[posy][posx][0] - piece_record[posy][posx][1] + 2;
    if (piece_next<BOARD_CELL_NO && piece_record[posy][posx][0]*piece_record[posy][piece_next][0] == 3 )
    {
        handcut_record[1][3]++;
        hand_cut_four++;
    }
    //5-"** **"
    piece_next = posx - piece_record[posy][posx][1] - 1;
    if (piece_next>=0 && piece_record[posy][posx][0] == 2 && piece_record[posy][piece_next][0] == 2 )
    {
        handcut_record[0][4]++;
        hand_cut_four++;
    }
    piece_next = posx + piece_record[posy][posx][0] - piece_record[posy][posx][1] + 2;
    if (piece_next<BOARD_CELL_NO && piece_record[posy][posx][0] == 2 && piece_record[posy][piece_next][0] == 2 )
    {
        handcut_record[1][4]++;
        hand_cut_four++;
    }
    //6-"***...***"
    if (piece_record[posy][posx][0] > 5)
    {
        handcut_record[0][5]++;
        handcut_record[1][5] = -1;
        hand_cut_six++;
    }
    //////////////////////////////////////////////////////////////////
    //         Start check hand-cut of verticle direction           //
    ///////////////////////////////////////////////////////////////////
    //1-"***"
    if (piece_record[posy][posx][2] == 3)
    {
        handcut_record[2][0]++;
        handcut_record[3][0] = -1;
        hand_cut_three++;
    }
    //2-"** *"
    piece_next = posy - piece_record[posy][posx][3] - 1;
    if (piece_next>=0 && piece_record[posy][posx][2]*piece_record[piece_next][posx][2] == 2 )
    {
        handcut_record[2][1]++;
        hand_cut_three++;
    }
    piece_next = posy + piece_record[posy][posx][2] - piece_record[posy][posx][3] + 2;
    if (piece_next<BOARD_CELL_NO && piece_record[posy][posx][2]*piece_record[piece_next][posx][2] == 2 )
    {
        handcut_record[3][1]++;
        hand_cut_three++;
    }
    //3-"****"
    if (piece_record[posy][posx][2] == 4)
    {
        handcut_record[2][2]++;
        handcut_record[3][2] = -1;
        hand_cut_four++;
    }
    //4-"*** *"
    piece_next = posy - piece_record[posy][posx][3] - 1;
    if (piece_next>=0 && piece_record[posy][posx][2]*piece_record[piece_next][posx][2] == 3 )
    {
        handcut_record[2][3]++;
        hand_cut_four++;
    }
    piece_next = posy + piece_record[posy][posx][2] - piece_record[posy][posx][3] + 2;
    if (piece_next<BOARD_CELL_NO && piece_record[posy][posx][2]*piece_record[piece_next][posx][2] == 3 )
    {
        handcut_record[3][3]++;
        hand_cut_four++;
    }
    //5-"** **"
    piece_next = posy - piece_record[posy][posx][3] - 1;
    if (piece_next>=0 && piece_record[posy][posx][2] == 2 && piece_record[piece_next][posx][2] == 2 )
    {
        handcut_record[2][4]++;
        hand_cut_four++;
    }
    piece_next = posy + piece_record[posy][posx][2] - piece_record[posy][posx][3] + 2;
    if (piece_next<BOARD_CELL_NO && piece_record[posy][posx][2] == 2 && piece_record[piece_next][posx][2] == 2 )
    {
        handcut_record[3][4]++;
        hand_cut_four++;
    }
    //6-"***...***"
    if (piece_record[posy][posx][2] > 5)
    {
        handcut_record[2][5]++;
        handcut_record[3][5] = -1;
        hand_cut_six++;
    }
    ///////////////////////////////////////////////////////////////////
    //          Start check hand-cut of BL-to-TR direction           //
    ///////////////////////////////////////////////////////////////////
    //1-"***"
    if (piece_record[posy][posx][4] == 3)
    {
        handcut_record[4][0]++;
        handcut_record[5][0] = -1;
        hand_cut_three++;
    }
    //2-"** *"
    piece_next = posx - piece_record[posy][posx][5] - 1;
    piece_next2 = posy +  piece_record[posy][posx][5] + 1;
    if (piece_next>=0 && piece_next2<BOARD_CELL_NO && piece_record[posy][posx][4]*piece_record[piece_next2][piece_next][4] == 2 )
    {
        handcut_record[4][1]++;
        hand_cut_three++;
    }
    piece_next = posx + piece_record[posy][posx][4] - piece_record[posy][posx][5] + 2;
    piece_next2 = posy - piece_record[posy][posx][4] + piece_record[posy][posx][5] - 2;
    if (piece_next<BOARD_CELL_NO && piece_next2>=0 && piece_record[posy][posx][4]*piece_record[piece_next2][piece_next][4] == 2 )
    {
        handcut_record[5][1]++;
        hand_cut_three++;
    }
    //3-"****"
    if (piece_record[posy][posx][4] == 4)
    {
        handcut_record[4][2]++;
        handcut_record[5][2] = -1;
        hand_cut_four++;
    }
    //4-"*** *"
    piece_next = posx - piece_record[posy][posx][5] - 1;
    piece_next2 = posy +  piece_record[posy][posx][5] + 1;
    if (piece_next>=0 && piece_next2<BOARD_CELL_NO && piece_record[posy][posx][4]*piece_record[piece_next2][piece_next][4] == 3 )
    {
        handcut_record[4][3]++;
        hand_cut_four++;
    }
    piece_next = posx + piece_record[posy][posx][4] - piece_record[posy][posx][5] + 2;
    piece_next2 = posy - piece_record[posy][posx][4] + piece_record[posy][posx][5] - 2;
    if (piece_next<BOARD_CELL_NO && piece_next2>=0 && piece_record[posy][posx][4]*piece_record[piece_next2][piece_next][4] == 3 )
    {
        handcut_record[5][3]++;
        hand_cut_four++;
    }
    //5-"** **"
    piece_next = posx - piece_record[posy][posx][5] - 1;
    piece_next2 = posy +  piece_record[posy][posx][5] + 1;
    if (piece_next>=0 && piece_next2<BOARD_CELL_NO && piece_record[posy][posx][4]==2 && piece_record[piece_next2][piece_next][4] == 2 )
    {
        handcut_record[4][4]++;
        hand_cut_four++;
    }
    piece_next = posx + piece_record[posy][posx][4] - piece_record[posy][posx][5] + 2;
    piece_next2 = posy - piece_record[posy][posx][4] + piece_record[posy][posx][5] - 2;
    if (piece_next<BOARD_CELL_NO && piece_next2>=0 && piece_record[posy][posx][4]==2 && piece_record[piece_next2][piece_next][4] == 2 )
    {
        handcut_record[5][4]++;
        hand_cut_four++;
    }
    //6-"***...***"
    if (piece_record[posy][posx][4] > 5)
    {
        handcut_record[4][5]++;
        handcut_record[5][5] = -1;
        hand_cut_six++;
    }
    ///////////////////////////////////////////////////////////////////
    //          Start check hand-cut of TL-to-BR direction           //
    ///////////////////////////////////////////////////////////////////
    //1-"***"
    if (piece_record[posy][posx][6] == 3)
    {
        handcut_record[6][0]++;
        handcut_record[7][0] = -1;
        hand_cut_three++;
    }
    //2-"** *"
    piece_next = posx - piece_record[posy][posx][7] - 1;
    piece_next2 = posy - piece_record[posy][posx][7] - 1;
    if (piece_next>=0 && piece_next2>=0 && piece_record[posy][posx][6]*piece_record[piece_next2][piece_next][6] == 2 )
    {
        handcut_record[6][1]++;
        hand_cut_three++;
    }
    piece_next = posx + piece_record[posy][posx][6] - piece_record[posy][posx][7] + 2;
    piece_next2 = posy + piece_record[posy][posx][6] - piece_record[posy][posx][7] + 2;
    if (piece_next<BOARD_CELL_NO && piece_next2<BOARD_CELL_NO && piece_record[posy][posx][6]*piece_record[piece_next2][piece_next][6] == 2 )
    {
        handcut_record[7][1]++;
        hand_cut_three++;
    }
    //3-"****"
    if (piece_record[posy][posx][6] == 4)
    {
        handcut_record[6][2]++;
        handcut_record[7][2] = -1;
        hand_cut_four++;
    }
    //4-"*** *"
    piece_next = posx - piece_record[posy][posx][7] - 1;
    piece_next2 = posy - piece_record[posy][posx][7] - 1;
    if (piece_next>=0 && piece_next2>=0 && piece_record[posy][posx][6]*piece_record[piece_next2][piece_next][6] == 3 )
    {
        handcut_record[6][3]++;
        hand_cut_four++;
    }
    piece_next = posx + piece_record[posy][posx][6] - piece_record[posy][posx][7] + 2;
    piece_next2 = posy + piece_record[posy][posx][6] - piece_record[posy][posx][7] + 2;
    if (piece_next<BOARD_CELL_NO && piece_next2<BOARD_CELL_NO && piece_record[posy][posx][6]*piece_record[piece_next2][piece_next][6] == 3 )
    {
        handcut_record[7][3]++;
        hand_cut_four++;
    }
    //5-"** **"
    piece_next = posx - piece_record[posy][posx][7] - 1;
    piece_next2 = posy - piece_record[posy][posx][7] - 1;
    if (piece_next>=0 && piece_next2>=0 && piece_record[posy][posx][6]==2 && piece_record[piece_next2][piece_next][6] == 2 )
    {
        handcut_record[6][4]++;
        hand_cut_four++;
    }
    piece_next = posx + piece_record[posy][posx][6] - piece_record[posy][posx][7] + 2;
    piece_next2 = posy + piece_record[posy][posx][6] - piece_record[posy][posx][7] + 2;
    if (piece_next<BOARD_CELL_NO && piece_next2<BOARD_CELL_NO && piece_record[posy][posx][6]==2 && piece_record[piece_next2][piece_next][6] == 2 )
    {
        handcut_record[7][4]++;
        hand_cut_four++;
    }
    //6-"***...***"
    if (piece_record[posy][posx][6] > 5)
    {
        handcut_record[6][5]++;
        handcut_record[7][5] = -1;
        hand_cut_six++;
    }
        
    if (hand_cut_three >= 2 || hand_cut_four >= 2 || hand_cut_six >= 1)
    { 
        gobang_draw_circle(BOARD_PIECE_RADIUS/2, (posx*BOARD_HOR_MARGIN+BOARD_LEFT_EDGE), (posy*BOARD_VER_MARGIN+BOARD_TOP_EDGE));
               
        gobang_show_text("调试结果：", 480, 150);
        gobang_show_text("pXc=", 480, 180); gobang_show_num((posx+1), 520, 180);
        gobang_show_text("pYc=", 540, 180); gobang_show_num((posy+1), 580, 180);
        
        gobang_show_text("PIECE_RECORD:", 480, 200);
//        int i, j;
        for (i=0; i<4; ++i)
        {
            gobang_show_num(piece_record[posy][posx][2*i], (480+20*i), 220);
            gobang_show_num(piece_record[posy][posx][2*i+1], (480+20*i), 240);
        }
        gobang_show_text("***************", 480, 260);
        for (i=0; i<8; ++i)
            for (j=0; j<6; ++j)
            {
                gobang_show_num(handcut_record[i][j], (480+20*j), (280+20*i));
            }
        
//        gobang_show_text("3连=", 480, 290); gobang_show_num(hand_cut_three, 540, 290);
//        gobang_show_text("4连=", 480, 310); gobang_show_num(hand_cut_four, 540, 310);
//        gobang_show_text("6连=", 480, 330); gobang_show_num(hand_cut_six, 540, 330);
        
        return 1;
    }
    
    return 0;
}
