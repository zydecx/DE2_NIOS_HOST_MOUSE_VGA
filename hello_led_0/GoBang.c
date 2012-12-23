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
void gobang_instrA_display()
{
    Instr_Array[0] = 1; //Welcome Mode
    Ongame_Array[1] = 1;    //First Round
    int IBox_Width, IBox_Height, IBox_Left, IBox_Top;
    IBox_Width=130; IBox_Height=420; IBox_Left=475; IBox_Top=30;
    gobang_box_fill(IBox_Width, IBox_Height, IBox_Left, IBox_Top);
    gobang_box_outline(IBox_Width, IBox_Height, IBox_Left, IBox_Top); 
    
    int IBCont_Left = 480;
    
    int IBTitle_Left, IBTitle_Top;
    IBTitle_Left=IBCont_Left; IBTitle_Top=45;
    unsigned char text1[] = " 五子棋对战平台";
    gobang_show_text(text1, IBTitle_Left, IBTitle_Top);
//    五-25788,子-30756,棋-21276,游-28470,戏-26076,平-21036,台-24294
//    int text11[]={25788,30756,21276,28470,26076,21036,24294};
//    gobang_show_chinese(text11, IBTitle_Left, IBTitle_Top);

    int IBWelc_Left, IBWelc_Top;
    IBWelc_Left=IBCont_Left; IBWelc_Top=70;
    unsigned char text2[] = "Welcome to Play";
    unsigned char text3[] = " GOBANG GAME!! ";
    unsigned char text4[] = "作者： 褚夫峰";
    unsigned char text5[] = "       尹晨光";
    gobang_show_text(text2, IBWelc_Left, IBWelc_Top);
    gobang_show_text(text3, IBWelc_Left, (IBWelc_Top+25));
    gobang_show_text(text4, IBWelc_Left, (IBWelc_Top+50));
    gobang_show_text(text5, IBWelc_Left, (IBWelc_Top+75));
//    gobang_show_num(75, 480, 160);

    int IBFunc_Left, IBFunc_Top;
    IBFunc_Left=IBCont_Left; IBFunc_Top=175;
    unsigned char text6[] = "功能选择：";
    gobang_show_text(text6, IBFunc_Left, IBFunc_Top);
    
    unsigned char text7[] = "局胜制";
    gobang_show_text(text7, IBFunc_Left, IBFunc_Top+25);
    gobang_draw_circle(6, IBFunc_Left+6, IBFunc_Top+56);
    gobang_clear_circle(4, IBFunc_Left+6, IBFunc_Top+56);
    gobang_draw_circle(2, IBFunc_Left+6, IBFunc_Top+56);
    gobang_show_num(1, IBFunc_Left+18, IBFunc_Top+50);
    gobang_draw_circle(6, IBFunc_Left+46, IBFunc_Top+56);
    gobang_clear_circle(4, IBFunc_Left+46, IBFunc_Top+56);
    gobang_show_num(3, IBFunc_Left+58, IBFunc_Top+50);
    gobang_draw_circle(6, IBFunc_Left+86, IBFunc_Top+56);
    gobang_clear_circle(4, IBFunc_Left+86, IBFunc_Top+56);
    gobang_show_num(5, IBFunc_Left+98, IBFunc_Top+50);
    
    unsigned char text8[] = "是否禁手";
    gobang_show_text(text8, IBFunc_Left, IBFunc_Top+75);
    gobang_draw_circle(6, IBFunc_Left+6, IBFunc_Top+108);
    gobang_clear_circle(4, IBFunc_Left+6, IBFunc_Top+108);
    gobang_draw_circle(2, IBFunc_Left+6, IBFunc_Top+108);
    gobang_show_text("是", IBFunc_Left+18, IBFunc_Top+100);
    gobang_draw_circle(6, IBFunc_Left+66, IBFunc_Top+108);
    gobang_clear_circle(4, IBFunc_Left+66, IBFunc_Top+108);
    gobang_show_text("否", IBFunc_Left+78, IBFunc_Top+100); 
    
    unsigned char text9[] = "对战模式";
    gobang_show_text(text9, IBFunc_Left, IBFunc_Top+125);
    gobang_draw_circle(6, IBFunc_Left+6, IBFunc_Top+158);
    gobang_clear_circle(4, IBFunc_Left+6, IBFunc_Top+158);
    gobang_draw_circle(2, IBFunc_Left+6, IBFunc_Top+158);
    gobang_show_text("人人", IBFunc_Left+18, IBFunc_Top+150);
    gobang_draw_circle(6, IBFunc_Left+66, IBFunc_Top+158);
    gobang_clear_circle(4, IBFunc_Left+66, IBFunc_Top+158);
    gobang_show_text("人机", IBFunc_Left+78, IBFunc_Top+150);
    
    
//    gobang_draw_circle(6, IBFunc_Left+6, IBFunc_Top+183);
//    gobang_clear_circle(4, IBFunc_Left+6, IBFunc_Top+183);
//    gobang_draw_circle(2, IBFunc_Left+6, IBFunc_Top+183);
//    gobang_show_text("先手", IBFunc_Left+18, IBFunc_Top+175);
//    gobang_draw_circle(6, IBFunc_Left+66, IBFunc_Top+183);
//    gobang_clear_circle(4, IBFunc_Left+66, IBFunc_Top+183);
//    gobang_show_text("后手", IBFunc_Left+78, IBFunc_Top+175);
    
    unsigned char text10[] = "开始游戏";
    int IBPlay_Width, IBPlay_Height, IBPlay_Left, IBPlay_Top;
    IBPlay_Width=80; IBPlay_Height=35; IBPlay_Left=IBFunc_Left+15; IBPlay_Top=385;
    gobang_box_fullfill(IBPlay_Width, IBPlay_Height, IBPlay_Left, IBPlay_Top);
    gobang_box_fill(70, IBPlay_Height*4/5, IBPlay_Left+5, IBPlay_Top+3);
    gobang_box_outline(IBPlay_Width, IBPlay_Height, IBPlay_Left, IBPlay_Top); 
    gobang_show_text(text10, IBPlay_Left+8, IBPlay_Top+8);
}
//-------------------------------------------------------------------------
void gobang_instrB_display()
{
    Instr_Array[0] = 2; //On Game Mode
    Ongame_Array[0]=Instr_Array[1]; //how many rounds
    
    int IBox_Width, IBox_Height, IBox_Left, IBox_Top;
    IBox_Width=130; IBox_Height=420; IBox_Left=475; IBox_Top=30;
    gobang_box_fill(IBox_Width, IBox_Height, IBox_Left, IBox_Top);
    gobang_box_outline(IBox_Width, IBox_Height, IBox_Left, IBox_Top);
    
    int IBCont_Left = 480;
    
    int IBTitle_Left, IBTitle_Top;
    IBTitle_Left=IBCont_Left; IBTitle_Top=45;
    unsigned char textA1[] = " 五子棋对战平台";
    gobang_show_text(textA1, IBTitle_Left, IBTitle_Top);

    int IBWelc_Left, IBWelc_Top;
    IBWelc_Left=IBCont_Left; IBWelc_Top=70;
    unsigned char textA2[] = "Welcome to Play";
    unsigned char textA3[] = " GOBANG GAME!! ";
    gobang_show_text(textA2, IBWelc_Left, IBWelc_Top);
    gobang_show_text(textA3, IBWelc_Left, (IBWelc_Top+25));
    
    int IBPiece_Left, IBPiece_Top;
    IBPiece_Left=IBCont_Left; IBPiece_Top=125;
    
    //显示棋子，代表当前由谁执棋
    unsigned char text1[]="黑棋执子";
    unsigned char text2[]="白棋执子";
    int i=1;
    int cur_centerx, cur_centery;
    do{
        cur_centerx = IBPiece_Left+(BOARD_PIECE_RADIUS+2)*(2*i-1);
        cur_centery = IBPiece_Top+BOARD_PIECE_RADIUS;
        if (Ongame_Array[2]==0) //Black is now playing
        {
            gobang_draw_circle(BOARD_PIECE_RADIUS, cur_centerx, cur_centery);
            gobang_clear_circle(BOARD_PIECE_RADIUS*5/6, cur_centerx, cur_centery);
            gobang_show_text(text1, IBPiece_Left, IBPiece_Top+40);
        }
        else    //White is now playing
        {
            gobang_draw_circle(BOARD_PIECE_RADIUS, cur_centerx, cur_centery);
            gobang_show_text(text2, IBPiece_Left, IBPiece_Top+40);
        }
        ++i;
    }
    while(((BOARD_PIECE_RADIUS+2)*2*i<IBox_Width));
//    Ongame_Array[2] = 1 - Ongame_Array[2];  //turn to another user
    
    int IBFunc_Left, IBFunc_Top;
    IBFunc_Left=IBCont_Left; IBFunc_Top=IBPiece_Top+75;//200
    
    //共#局，第#局
    gobang_show_text("共", IBFunc_Left, IBFunc_Top);
    gobang_show_num(Ongame_Array[0], IBFunc_Left+16, IBFunc_Top);
    gobang_show_text("局,", IBFunc_Left+24, IBFunc_Top);
    gobang_show_text("第", IBFunc_Left+56, IBFunc_Top);
    gobang_show_num(Ongame_Array[1], IBFunc_Left+72, IBFunc_Top);
    gobang_show_text("局", IBFunc_Left+80, IBFunc_Top);
    
    
    unsigned char text4[] = "胜负情况：";
    gobang_show_text(text4, IBFunc_Left, IBFunc_Top+25);
    gobang_show_text("黑方", IBFunc_Left, IBFunc_Top+50);
    gobang_show_num(Ongame_Array[3], IBFunc_Left+40, IBFunc_Top+50);
    gobang_show_text("白方", IBFunc_Left+60, IBFunc_Top+50);
    gobang_show_num(Ongame_Array[4], IBFunc_Left+100, IBFunc_Top+50);
    
    int IBPlay_Width, IBPlay_Height, IBPlay_Left, IBPlay_Top;
    unsigned char text5[] = "请求悔棋";
    IBPlay_Width=80; IBPlay_Height=35; IBPlay_Left=IBFunc_Left+15; IBPlay_Top=345;
    gobang_box_fullfill(IBPlay_Width, IBPlay_Height, IBPlay_Left, IBPlay_Top);
    gobang_box_fill(70, IBPlay_Height*4/5, IBPlay_Left+5, IBPlay_Top+3);
    gobang_box_outline(IBPlay_Width, IBPlay_Height, IBPlay_Left, IBPlay_Top); 
    gobang_show_text(text5, IBPlay_Left+8, IBPlay_Top+8);
    
    unsigned char text6[] = "重新开始";
    IBPlay_Width=80; IBPlay_Height=35; IBPlay_Left=IBCont_Left+15; IBPlay_Top=385;
    gobang_box_fullfill(IBPlay_Width, IBPlay_Height, IBPlay_Left, IBPlay_Top);
    gobang_box_fill(70, IBPlay_Height*4/5, IBPlay_Left+5, IBPlay_Top+3);
    gobang_box_outline(IBPlay_Width, IBPlay_Height, IBPlay_Left, IBPlay_Top); 
    gobang_show_text(text6, IBPlay_Left+8, IBPlay_Top+8);
}
//-------------------------------------------------------------------------
void gobang_instrC_display(int winner)
{
    Instr_Array[0] = 3; //One Round Over
    
    int IBox_Width, IBox_Height, IBox_Left, IBox_Top;
    IBox_Width=130; IBox_Height=420; IBox_Left=475; IBox_Top=30;
    gobang_box_fill(IBox_Width, IBox_Height, IBox_Left, IBox_Top);
    gobang_box_outline(IBox_Width, IBox_Height, IBox_Left, IBox_Top);
    
    int IBCont_Left = 480;
    
    int IBTitle_Left, IBTitle_Top;
    IBTitle_Left=IBCont_Left; IBTitle_Top=45;
    unsigned char textA1[] = " 五子棋对战平台";
    gobang_show_text(textA1, IBTitle_Left, IBTitle_Top);

    int IBWelc_Left, IBWelc_Top;
    IBWelc_Left=IBCont_Left; IBWelc_Top=70;
    unsigned char textA2[] = "Welcome to Play";
    unsigned char textA3[] = " GOBANG GAME!! ";
    gobang_show_text(textA2, IBWelc_Left, IBWelc_Top);
    gobang_show_text(textA3, IBWelc_Left, (IBWelc_Top+25));
    
    int IBPiece_Left, IBPiece_Top;
    IBPiece_Left=IBCont_Left; IBPiece_Top=125;
    
    //显示棋子，代表当前棋方获胜
    unsigned char text1[]="恭喜黑棋获胜！";
    unsigned char text2[]="恭喜白棋获胜！";
    int i=1;
    int cur_centerx, cur_centery;
    do{
        cur_centerx = IBPiece_Left+(BOARD_PIECE_RADIUS+2)*(2*i-1);
        cur_centery = IBPiece_Top+BOARD_PIECE_RADIUS;
        if (winner==0) //Black is winning current round
        {
            gobang_draw_circle(BOARD_PIECE_RADIUS, cur_centerx, cur_centery);
            gobang_clear_circle(BOARD_PIECE_RADIUS*5/6, cur_centerx, cur_centery);
            gobang_show_text(text1, IBPiece_Left, IBPiece_Top+40);
        }
        else    //White is winning current round
        {
            gobang_draw_circle(BOARD_PIECE_RADIUS, cur_centerx, cur_centery);
            gobang_show_text(text2, IBPiece_Left, IBPiece_Top+40);
        }
        ++i;
    }
    while(((BOARD_PIECE_RADIUS+2)*2*i<IBox_Width));
    
    int IBFunc_Left, IBFunc_Top;
    IBFunc_Left=IBCont_Left; IBFunc_Top=IBPiece_Top+75;//200
    
    //共#局，第#局
    gobang_show_text("共", IBFunc_Left, IBFunc_Top);
    gobang_show_num(Ongame_Array[0], IBFunc_Left+16, IBFunc_Top);
    gobang_show_text("局,", IBFunc_Left+24, IBFunc_Top);
    gobang_show_text("第", IBFunc_Left+56, IBFunc_Top);
    gobang_show_num(Ongame_Array[1], IBFunc_Left+72, IBFunc_Top);
    gobang_show_text("局", IBFunc_Left+80, IBFunc_Top);
    
    
    unsigned char text4[] = "胜负情况：";
    gobang_show_text(text4, IBFunc_Left, IBFunc_Top+25);
    gobang_show_text("黑方", IBFunc_Left, IBFunc_Top+50);
    gobang_show_num(Ongame_Array[3], IBFunc_Left+40, IBFunc_Top+50);
    gobang_show_text("白方", IBFunc_Left+60, IBFunc_Top+50);
    gobang_show_num(Ongame_Array[4], IBFunc_Left+100, IBFunc_Top+50);
    
    int IBPlay_Width, IBPlay_Height, IBPlay_Left, IBPlay_Top;
    unsigned char text7[] = "棋局回放";
    IBPlay_Width=80; IBPlay_Height=35; IBPlay_Left=IBFunc_Left+15; IBPlay_Top=305;
    gobang_box_fullfill(IBPlay_Width, IBPlay_Height, IBPlay_Left, IBPlay_Top);
    gobang_box_fill(70, IBPlay_Height*4/5, IBPlay_Left+5, IBPlay_Top+3);
    gobang_box_outline(IBPlay_Width, IBPlay_Height, IBPlay_Left, IBPlay_Top); 
    gobang_show_text(text7, IBPlay_Left+8, IBPlay_Top+8);
    
    unsigned char text5[] = "下一回合";
    IBPlay_Width=80; IBPlay_Height=35; IBPlay_Left=IBFunc_Left+15; IBPlay_Top=345;
    gobang_box_fullfill(IBPlay_Width, IBPlay_Height, IBPlay_Left, IBPlay_Top);
    gobang_box_fill(70, IBPlay_Height*4/5, IBPlay_Left+5, IBPlay_Top+3);
    gobang_box_outline(IBPlay_Width, IBPlay_Height, IBPlay_Left, IBPlay_Top); 
    gobang_show_text(text5, IBPlay_Left+8, IBPlay_Top+8);
    
    unsigned char text6[] = "重新开始";
    IBPlay_Width=80; IBPlay_Height=35; IBPlay_Left=IBCont_Left+15; IBPlay_Top=385;
    gobang_box_fullfill(IBPlay_Width, IBPlay_Height, IBPlay_Left, IBPlay_Top);
    gobang_box_fill(70, IBPlay_Height*4/5, IBPlay_Left+5, IBPlay_Top+3);
    gobang_box_outline(IBPlay_Width, IBPlay_Height, IBPlay_Left, IBPlay_Top); 
    gobang_show_text(text6, IBPlay_Left+8, IBPlay_Top+8);
}
//-------------------------------------------------------------------------
void gobang_instrD_display(int winner)
{
    Instr_Array[0] = 4; //Game Over
    
    int IBox_Width, IBox_Height, IBox_Left, IBox_Top;
    IBox_Width=130; IBox_Height=420; IBox_Left=475; IBox_Top=30;
    gobang_box_fill(IBox_Width, IBox_Height, IBox_Left, IBox_Top);
    gobang_box_outline(IBox_Width, IBox_Height, IBox_Left, IBox_Top);
    
    int IBCont_Left = 480;
    
    int IBTitle_Left, IBTitle_Top;
    IBTitle_Left=IBCont_Left; IBTitle_Top=45;
    unsigned char textA1[] = " 五子棋对战平台";
    gobang_show_text(textA1, IBTitle_Left, IBTitle_Top);

    int IBWelc_Left, IBWelc_Top;
    IBWelc_Left=IBCont_Left; IBWelc_Top=70;
    unsigned char textA2[] = "Welcome to Play";
    unsigned char textA3[] = " GOBANG GAME!! ";
    unsigned char textA4[] = "作者： 褚夫峰";
    unsigned char textA5[] = "       尹晨光";
    gobang_show_text(textA2, IBWelc_Left, IBWelc_Top);
    gobang_show_text(textA3, IBWelc_Left, (IBWelc_Top+25));
    gobang_show_text(textA4, IBWelc_Left, (IBWelc_Top+50));
    gobang_show_text(textA5, IBWelc_Left, (IBWelc_Top+75));
    
    
    int i, j;
    for (i=0; i<BOARD_CELL_NO; ++i)
        for (j=0; j<BOARD_CELL_NO; ++j)
        {
            if (winner == 1)
            {
                gobang_draw_circle(BOARD_PIECE_RADIUS, (i*BOARD_HOR_MARGIN+BOARD_LEFT_EDGE), (j*BOARD_VER_MARGIN+BOARD_TOP_EDGE));
            }
            else
            {
                gobang_draw_circle(BOARD_PIECE_RADIUS, (i*BOARD_HOR_MARGIN+BOARD_LEFT_EDGE), (j*BOARD_VER_MARGIN+BOARD_TOP_EDGE));
                gobang_clear_circle(BOARD_PIECE_RADIUS*5/6, (i*BOARD_HOR_MARGIN+BOARD_LEFT_EDGE), (j*BOARD_VER_MARGIN+BOARD_TOP_EDGE));
            }
        }
    int WinMsg_Left, WinMsg_Top, WinMsg_Width, WinMsg_Height;
    WinMsg_Left=155;WinMsg_Top=150;WinMsg_Width=180;WinMsg_Height=120;
    gobang_box_fill(WinMsg_Width, WinMsg_Height, WinMsg_Left, WinMsg_Top);
    gobang_box_outline(WinMsg_Width, WinMsg_Height, WinMsg_Left, WinMsg_Top);
    unsigned char textWin1[] = "********恭喜********";
    unsigned char textWin2[] = "******白方获胜******";
    unsigned char textWin3[] = "******黑方获胜******";
    unsigned char textWin4[] = "***您赢了这轮比赛***";
    unsigned char textWin5[] = "*******很遗憾*******";
    unsigned char textWin6[] = "*****您未能获胜*****";
    if (Instr_Array[3]==0 && Instr_Array[4]!=winner)
    {
        gobang_show_text(textWin1, WinMsg_Left+10, WinMsg_Top+30);
        gobang_show_text(textWin4, WinMsg_Left+10, WinMsg_Top+70);
    }
    if (Instr_Array[3]==0 && Instr_Array[4]==winner)
    {
        gobang_show_text(textWin5, WinMsg_Left+10, WinMsg_Top+30);
        gobang_show_text(textWin6, WinMsg_Left+10, WinMsg_Top+70);
    }
    if (Instr_Array[3]!=0 && winner==0)
    {
        gobang_show_text(textWin1, WinMsg_Left+10, WinMsg_Top+30);
        gobang_show_text(textWin3, WinMsg_Left+10, WinMsg_Top+70);
    }
    if (Instr_Array[3]!=0 && winner==1)
    {
        gobang_show_text(textWin1, WinMsg_Left+10, WinMsg_Top+30);
        gobang_show_text(textWin2, WinMsg_Left+10, WinMsg_Top+70);
    }
    
    int IBFunc_Left, IBFunc_Top;
    IBFunc_Left=IBCont_Left; IBFunc_Top=200;//200
    
    //共#局，第#局
    gobang_show_text("共", IBFunc_Left, IBFunc_Top);
    gobang_show_num(Ongame_Array[0], IBFunc_Left+16, IBFunc_Top);
    gobang_show_text("局,", IBFunc_Left+24, IBFunc_Top);
    gobang_show_text("第", IBFunc_Left+56, IBFunc_Top);
    gobang_show_num(Ongame_Array[1], IBFunc_Left+72, IBFunc_Top);
    gobang_show_text("局", IBFunc_Left+80, IBFunc_Top);
    
    
    unsigned char text4[] = "胜负情况：";
    gobang_show_text(text4, IBFunc_Left, IBFunc_Top+25);
    gobang_show_text("黑方", IBFunc_Left, IBFunc_Top+50);
    gobang_show_num(Ongame_Array[3], IBFunc_Left+40, IBFunc_Top+50);
    gobang_show_text("白方", IBFunc_Left+60, IBFunc_Top+50);
    gobang_show_num(Ongame_Array[4], IBFunc_Left+100, IBFunc_Top+50);
    
    unsigned char text5[] = "^恭喜^恭喜^";
    unsigned char text6[] = "^实在^遗憾^";
    if (Instr_Array[3]==0 && Instr_Array[4]==winner)
    {
        gobang_show_text(text6, IBFunc_Left, IBFunc_Top+100);
        gobang_show_text(text6, IBFunc_Left, IBFunc_Top+125);
    }
    else
    {
        gobang_show_text(text5, IBFunc_Left, IBFunc_Top+100);
        gobang_show_text(text5, IBFunc_Left, IBFunc_Top+125);
    }
    
    unsigned char text7[] = "重新开始";
    int IBPlay_Width, IBPlay_Height, IBPlay_Left, IBPlay_Top;
    IBPlay_Width=80; IBPlay_Height=35; IBPlay_Left=IBCont_Left+15; IBPlay_Top=385;
    gobang_box_fullfill(IBPlay_Width, IBPlay_Height, IBPlay_Left, IBPlay_Top);
    gobang_box_fill(70, IBPlay_Height*4/5, IBPlay_Left+5, IBPlay_Top+3);
    gobang_box_outline(IBPlay_Width, IBPlay_Height, IBPlay_Left, IBPlay_Top); 
    gobang_show_text(text7, IBPlay_Left+8, IBPlay_Top+8);
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
   for (ex = 0; ex < PIECE_HISTORY_NO; ++ex)
        for (ey = 0; ey < 3; ++ey)
            Piece_History[ex][ey] = 0;
}
void reset_game_config_array()
{
    int ex;
    //Instr_Array[5]:0-Mode(Welcome), 1-One Round, 2-Hand-cut, 3-Peer-Peer, 4-User first
    for (ex = 0; ex < INSTR_ARRAY_SIZE; ++ex)
        Instr_Array[ex] = 1;
    //Ongame_Array[5]:0-No. of Rounds, 1-current round, 2-current color(W-1/B-0), 3-B wins rounds, 4-W wins rounds
    for (ex = 0; ex < ONGAME_ARRAY_SIZE; ++ex)
        Ongame_Array[ex] = 0;
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
void gobang_box_fullfill(int width, int height, int posx, int posy)
{
    int ex, ey;
    for (ex=posx; ex<posx+width; ++ex)
        for (ey=posy; ey<posy+height; ++ey)
            Vga_Set_Pixel(VGA_0_BASE, ex, ey);
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
    reset_game_config_array();
    clean_screen();
    gobang_board_display(); 
    gobang_instrA_display();
}
//-------------------------------------------------------------------------
void gobang_game_resume()
{
    Ongame_Array[1]++;  //current round(1 default)
    Ongame_Array[2] = 1 - Ongame_Array[2];
    if (Ongame_Array[1]>Ongame_Array[0])
    {
        Ongame_Array[1]--;
        int winner;
        winner=Ongame_Array[3]>Ongame_Array[4] ? 0 : 1;
        gobang_instrD_display(winner);
    }
    else
    {
        reset_piece_record_array();
        clean_screen();
        gobang_board_display(); 
        gobang_instrB_display();
        
        if (Instr_Array[3]==0 && Instr_Array[4]==Ongame_Array[2]) //Peer-to-PC 
        {
            int CPiece[3];
            gobang_ai_algorithm(CPiece, Ongame_Array[2]);   //computer generate position of piece,
                                                            //Cpiece-to store position, Ongame_Array[2]-current piece color
            gobang_place_piece(CPiece[0], CPiece[1]);
        }
    }
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
unsigned int gobang_click_circle(int radius, int centerx, int centery, int posx, int posy)
{
     if (((posx-centerx)*(posx-centerx)+(posy-centery)*(posy-centery))<=(radius*radius))
        return 1;
     else
        return 0;
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
void gobang_read_instr_state(int posx, int posy)
{
    int IBCont_Left = 480;
    int radius = 6;
    int cr = 4;
    int dr = 2;
    if (Instr_Array[0] == 1)    //welcome mode
    {
        int i, j;
        int IBFunc_Left, IBFunc_Top;
        IBFunc_Left=IBCont_Left; IBFunc_Top=175;
        //局胜制
        int instr_rounds[3][3] = {  {1, IBFunc_Left+6, IBFunc_Top+56},
                                    {3, IBFunc_Left+46, IBFunc_Top+56},
                                    {5, IBFunc_Left+86, IBFunc_Top+56}};
        for (i=0; i<3; ++i)
        {
            if (gobang_click_circle(radius, instr_rounds[i][1], instr_rounds[i][2], posx, posy))
            {
                Instr_Array[1] = instr_rounds[i][0];
                for (j=0; j<3; ++j)
                {
                   gobang_clear_circle(cr, instr_rounds[j][1], instr_rounds[j][2]);
                }
                gobang_draw_circle(dr, instr_rounds[i][1], instr_rounds[i][2]);
                break;
            }
        }
        //是否禁手
        int instr_handcut[2][3] = { {1, IBFunc_Left+6, IBFunc_Top+108},
                                    {0, IBFunc_Left+66, IBFunc_Top+108}};
        for (i=0; i<2; ++i)
        {
            if (gobang_click_circle(radius, instr_handcut[i][1], instr_handcut[i][2], posx, posy))
            {
                Instr_Array[2] = instr_handcut[i][0];
                for (j=0; j<2; ++j)
                {
                   gobang_clear_circle(cr, instr_handcut[j][1], instr_handcut[j][2]);
                }
                gobang_draw_circle(dr, instr_handcut[i][1], instr_handcut[i][2]);
                break;
            }
        }
        //人人/人机
        int instr_pppc[2][3] = { {1, IBFunc_Left+6, IBFunc_Top+158},
                                    {0, IBFunc_Left+66, IBFunc_Top+158}};
        for (i=0; i<2; ++i)
        {
            if (gobang_click_circle(radius, instr_pppc[i][1], instr_pppc[i][2], posx, posy))
            {
                Instr_Array[3] = instr_pppc[i][0];
                for (j=0; j<2; ++j)
                {
                   gobang_clear_circle(cr, instr_pppc[j][1], instr_pppc[j][2]);
                }
                gobang_draw_circle(dr, instr_pppc[i][1], instr_pppc[i][2]);
                
                if (Instr_Array[3]==0)
                {
                    gobang_draw_circle(6, IBFunc_Left+6, IBFunc_Top+183);
                    gobang_clear_circle(4, IBFunc_Left+6, IBFunc_Top+183);
                    gobang_draw_circle(2, IBFunc_Left+6, IBFunc_Top+183);
                    gobang_show_text("先手", IBFunc_Left+18, IBFunc_Top+175);
                    gobang_draw_circle(6, IBFunc_Left+66, IBFunc_Top+183);
                    gobang_clear_circle(4, IBFunc_Left+66, IBFunc_Top+183);
                    gobang_show_text("后手", IBFunc_Left+78, IBFunc_Top+175);
                }
                else
                    gobang_box_fill(120, 20, IBFunc_Left, IBFunc_Top+175);
                
                break;
            }
        }
        //是否先手
        if (Instr_Array[3]==0)
        {
            int instr_ufirst[2][3] = { {1, IBFunc_Left+6, IBFunc_Top+183},
                                       {0, IBFunc_Left+66, IBFunc_Top+183}};
            for (i=0; i<2; ++i)
            {
                if (gobang_click_circle(radius, instr_ufirst[i][1], instr_ufirst[i][2], posx, posy))
                {
                    Instr_Array[4] = instr_ufirst[i][0];
                    for (j=0; j<2; ++j)
                    {
                       gobang_clear_circle(cr, instr_ufirst[j][1], instr_ufirst[j][2]);
                    }
                    gobang_draw_circle(dr, instr_ufirst[i][1], instr_ufirst[i][2]);
                    break;
                }
            }
        }
        //是否开始游戏
        int IBStart_Left, IBStart_Top, IBStart_Right, IBStart_Bottom;
        IBStart_Left=500;IBStart_Top=388;IBStart_Right=570;IBStart_Bottom=416;
        if (posx>IBStart_Left && posx<IBStart_Right && posy>IBStart_Top && posy<IBStart_Bottom)
        {
            gobang_instrB_display();
    
            if (Instr_Array[3]==0 && Instr_Array[4]==0) //Peer-to-PC and computer first(black one)
            {
                int CPiece[3];
                gobang_ai_algorithm(CPiece, Ongame_Array[2]);   //computer generate position of piece,
                                                                //Cpiece-to store position, Ongame_Array[2]-current piece color
                gobang_place_piece(CPiece[0], CPiece[1]);
            }
        }
    }
    else if (Instr_Array[0] == 2)
    {
        //是否悔棋
        int IBStart_Left, IBStart_Top, IBStart_Right, IBStart_Bottom;
        IBStart_Left=500;IBStart_Top=348;IBStart_Right=570;IBStart_Bottom=376;
        if (posx>IBStart_Left && posx<IBStart_Right && posy>IBStart_Top && posy<IBStart_Bottom)
        {
            gobang_game_start();//悔棋处理函数
        }
        //是否退出游戏
        IBStart_Left=500;IBStart_Top=388;IBStart_Right=570;IBStart_Bottom=416;
        if (posx>IBStart_Left && posx<IBStart_Right && posy>IBStart_Top && posy<IBStart_Bottom)
        {
            gobang_game_start();
        }
    }
    else if (Instr_Array[0] == 3)
    {
        //是否回放棋局
        int IBStart_Left, IBStart_Top, IBStart_Right, IBStart_Bottom;
        IBStart_Left=500;IBStart_Top=308;IBStart_Right=570;IBStart_Bottom=336;
        if (posx>IBStart_Left && posx<IBStart_Right && posy>IBStart_Top && posy<IBStart_Bottom)
        {
            gobang_game_start();//回放棋局处理函数
        }
        //是否继续游戏
        IBStart_Left=500;IBStart_Top=348;IBStart_Right=570;IBStart_Bottom=376;
        if (posx>IBStart_Left && posx<IBStart_Right && posy>IBStart_Top && posy<IBStart_Bottom)
        {
            gobang_game_resume();//继续游戏处理函数
        }
        //是否退出游戏
        IBStart_Left=500;IBStart_Top=388;IBStart_Right=570;IBStart_Bottom=416;
        if (posx>IBStart_Left && posx<IBStart_Right && posy>IBStart_Top && posy<IBStart_Bottom)
        {
            gobang_game_start();
        }
    }
    else if (Instr_Array[0] == 4)
    {
        //是否退出游戏
        int IBStart_Left, IBStart_Top, IBStart_Right, IBStart_Bottom;
        IBStart_Left=500;IBStart_Top=388;IBStart_Right=570;IBStart_Bottom=416;
        if (posx>IBStart_Left && posx<IBStart_Right && posy>IBStart_Top && posy<IBStart_Bottom)
        {
            gobang_game_start();
        }
    }
}
//-------------------------------------------------------------------------
void gobang_ai_algorithm(int PiecePos[3], int isWhite)
{
    int ex, ey;
    for (ex=0; ex<BOARD_CELL_NO; ++ex)
        for (ey=0; ey<BOARD_CELL_NO; ++ey)
        {
            if (Piece_Record[ey][ex]==0)
            {
                PiecePos[0] = ex;
                PiecePos[1] = ey;
                PiecePos[2] = isWhite;
                return;
            }
        }
}
//-------------------------------------------------------------------------
unsigned int gobang_place_piece(int pXc, int pYc)
{
    int ii,jj;
    unsigned int isWhite = Ongame_Array[2];
    Piece_History[0][0]++;
    Piece_History[Piece_History[0][0]][0] = pXc;
    Piece_History[Piece_History[0][0]][1] = pYc;
    Piece_History[Piece_History[0][0]][2] = isWhite;
    
    if (isWhite == 1)
    {
        gobang_draw_circle(BOARD_PIECE_RADIUS, (pXc*BOARD_HOR_MARGIN+BOARD_LEFT_EDGE), (pYc*BOARD_VER_MARGIN+BOARD_TOP_EDGE));
    }
    else
    {
        gobang_draw_circle(BOARD_PIECE_RADIUS, (pXc*BOARD_HOR_MARGIN+BOARD_LEFT_EDGE), (pYc*BOARD_VER_MARGIN+BOARD_TOP_EDGE));
        gobang_clear_circle(BOARD_PIECE_RADIUS*5/6, (pXc*BOARD_HOR_MARGIN+BOARD_LEFT_EDGE), (pYc*BOARD_VER_MARGIN+BOARD_TOP_EDGE));
    }
    
    //Start update the piece on board
    Piece_Record[pYc][pXc] = 1-2*isWhite;
    
    ///////////////////////////////////////////////////////////////////
    //         Start update the state of Horzontal direction         //
    //////////////////////////////////////////////////////////////////
    int Series_Start_Point;
    int Series_End_Point;
    //left side
    if (pXc>0 && Piece_Record[pYc][pXc]*Piece_Record[pYc][pXc-1] > 0)
    {
        Series_Start_Point = pXc - abs(Piece_Analysis_Record[pYc][pXc-1][0]);
        Piece_Analysis_Record[pYc][pXc][0] = (1-2*isWhite) + Piece_Analysis_Record[pYc][pXc-1][0];  //how many, 1-black, -1-white
        Piece_Analysis_Record[pYc][pXc][1] = 1 + Piece_Analysis_Record[pYc][pXc-1][1]; //第几个
    }
    else
    {
        Series_Start_Point = pXc;
        Piece_Analysis_Record[pYc][pXc][0] = 1-2*isWhite;  //how many, 1-black, -1-white
    }
    //right side
    if (pXc<BOARD_CELL_NO-1 && Piece_Record[pYc][pXc]*Piece_Record[pYc][pXc+1] > 0)
    {
        Series_End_Point = pXc + abs(Piece_Analysis_Record[pYc][pXc+1][0]);
        Piece_Analysis_Record[pYc][pXc][0] += Piece_Analysis_Record[pYc][pXc+1][0];  //how many, 1-black, -1-white
    }
    else
    {
        Series_End_Point = pXc;
    }
    //decide if the player wins
    if (abs(Piece_Analysis_Record[pYc][pXc][0]) == 5)
    {
        return isWhite;
    }
    //update the horizontal state
    for (ii = Series_Start_Point; ii <= Series_End_Point; ++ii)
    {
        Piece_Analysis_Record[pYc][ii][0] = Piece_Analysis_Record[pYc][pXc][0];
        Piece_Analysis_Record[pYc][ii][1] = ii - Series_Start_Point + 1;
    }
    ///////////////////////////////////////////////////////////////////
    //         Start update the state of Verticle direction          //
    ///////////////////////////////////////////////////////////////////
    //top side
    if (pYc>0 && Piece_Record[pYc][pXc]*Piece_Record[pYc-1][pXc] > 0)
    {
        Series_Start_Point = pYc - abs(Piece_Analysis_Record[pYc-1][pXc][2]);
        Piece_Analysis_Record[pYc][pXc][2] = (1-2*isWhite) + Piece_Analysis_Record[pYc-1][pXc][2];  //how many, 1-black, -1-white
        Piece_Analysis_Record[pYc][pXc][3] = 1 + Piece_Analysis_Record[pYc-1][pXc][3]; //第几个
    }
    else
    {
        Series_Start_Point = pYc;
        Piece_Analysis_Record[pYc][pXc][2] = 1-2*isWhite;  //how many, 1-black, -1-white
    }
    //bottom side
    if (pYc<BOARD_CELL_NO-1 && Piece_Record[pYc][pXc]*Piece_Record[pYc+1][pXc] > 0)
    {
        Series_End_Point = pYc + abs(Piece_Analysis_Record[pYc+1][pXc][2]);
        Piece_Analysis_Record[pYc][pXc][2] += Piece_Analysis_Record[pYc+1][pXc][2];  //how many, 1-black, -1-white
    }
    else
    {
        Series_End_Point = pYc;
    }
    //decide if the player wins
    if (abs(Piece_Analysis_Record[pYc][pXc][2]) == 5)
    {
        return isWhite;
    }
    //update the vertical state
    for (jj = Series_Start_Point; jj <= Series_End_Point; ++jj)
    {
        Piece_Analysis_Record[jj][pXc][2] = Piece_Analysis_Record[pYc][pXc][2];
        Piece_Analysis_Record[jj][pXc][3] = jj - Series_Start_Point + 1;
    }
    ///////////////////////////////////////////////////////////////////
    //         Start update the state of BL-to-TR direction          //
    ///////////////////////////////////////////////////////////////////
    int Series_Start_Point2; //verticle start cordinate
    int Series_Stend_Points; //number of point-series
    //bottom-left side
    if (pXc>0 && pYc<BOARD_CELL_NO-1 && Piece_Record[pYc][pXc]*Piece_Record[pYc+1][pXc-1] > 0)
    {
        Series_Start_Point = pXc - abs(Piece_Analysis_Record[pYc+1][pXc-1][4]);
        Series_Start_Point2 = pYc + abs(Piece_Analysis_Record[pYc+1][pXc-1][4]);
        Piece_Analysis_Record[pYc][pXc][4] = (1-2*isWhite) + Piece_Analysis_Record[pYc+1][pXc-1][4];  //how many, 1-black, -1-white
        Piece_Analysis_Record[pYc][pXc][5] = 1 + Piece_Analysis_Record[pYc+1][pXc-1][5]; //第几个
    }
    else
    {
        Series_Start_Point = pXc;
        Series_Start_Point2 = pYc;
        Piece_Analysis_Record[pYc][pXc][4] = 1-2*isWhite;  //how many, 1-black, -1-white
    }
    //top-right side
    if (pXc<BOARD_CELL_NO-1 && pYc>0 && Piece_Record[pYc][pXc]*Piece_Record[pYc-1][pXc+1] > 0)
    {
        Piece_Analysis_Record[pYc][pXc][4] += Piece_Analysis_Record[pYc-1][pXc+1][4];  //how many, 1-black, -1-white
    }
    Series_Stend_Points = abs(Piece_Analysis_Record[pYc][pXc][4]);
    //decide if the player wins
    if (Series_Stend_Points == 5)
    {
        return isWhite;
    }
    //update the BL-to-TR state
    for (ii = 0; ii < Series_Stend_Points; ++ii)
    {
        Piece_Analysis_Record[Series_Start_Point2-ii][Series_Start_Point+ii][4] = Piece_Analysis_Record[pYc][pXc][4];
        Piece_Analysis_Record[Series_Start_Point2-ii][Series_Start_Point+ii][5] = ii + 1;
    }
    ///////////////////////////////////////////////////////////////////
    //         Start update the state of TL-to-BR direction          //
    ///////////////////////////////////////////////////////////////////
//    int Series_Start_Point2; //verticle start cordinate
//    int Series_Stend_Points; //number of point-series
    //top-left side
    if (pXc>0 && pYc>0 && Piece_Record[pYc][pXc]*Piece_Record[pYc-1][pXc-1] > 0)
    {
        Series_Start_Point = pXc - abs(Piece_Analysis_Record[pYc-1][pXc-1][6]);
        Series_Start_Point2 = pYc - abs(Piece_Analysis_Record[pYc-1][pXc-1][6]);
        Piece_Analysis_Record[pYc][pXc][6] = (1-2*isWhite) + Piece_Analysis_Record[pYc-1][pXc-1][6];  //how many, 1-black, -1-white
        Piece_Analysis_Record[pYc][pXc][7] = 1 + Piece_Analysis_Record[pYc-1][pXc-1][7]; //第几个
    }
    else
    {
        Series_Start_Point = pXc;
        Series_Start_Point2 = pYc;
        Piece_Analysis_Record[pYc][pXc][6] = 1-2*isWhite;  //how many, 1-black, -1-white
    }
    //bottom-right side
    if (pXc<BOARD_CELL_NO-1 && pYc<BOARD_CELL_NO-1 && Piece_Record[pYc][pXc]*Piece_Record[pYc+1][pXc+1] > 0)
    {
        Piece_Analysis_Record[pYc][pXc][6] += Piece_Analysis_Record[pYc+1][pXc+1][6];  //how many, 1-black, -1-white
    }
    Series_Stend_Points = abs(Piece_Analysis_Record[pYc][pXc][6]);
    //decide if the player wins
    if (Series_Stend_Points == 5)
    {
        return isWhite;
    }
    //update the TL-to-BR state
    for (ii = 0; ii < Series_Stend_Points; ++ii)
    {
        Piece_Analysis_Record[Series_Start_Point2+ii][Series_Start_Point+ii][6] = Piece_Analysis_Record[pYc][pXc][6];
        Piece_Analysis_Record[Series_Start_Point2+ii][Series_Start_Point+ii][7] = ii + 1;
    }
    
    ///////////////////////////////////////////////////////////////////
    //          Start check if the hand-cut problem exists           //
    /////////////////////////////////////////////////////////////////// 
    if (Instr_Array[2]==1)
    {
        if (gobang_handcut_check(Piece_Analysis_Record, isWhite, pXc, pYc))
        {
            return 1; //白方获胜
        }
    }
    
    Ongame_Array[2] = 1 - Ongame_Array[2];
    gobang_instrB_display();    //refresh instruction part
    return 2;
}
//-------------------------------------------------------------------------
void gobang_proc_win(int winner)
{
    Ongame_Array[3+winner]++;   //胜场加1
    gobang_instrC_display(winner);
}
//-------------------------------------------------------------------------
//return value of gobang_proc_lclick(), 2-successful, 3-fail, 0-black win, 1-white win
unsigned int gobang_proc_lclick(int posx, int posy)
{
    if (Instr_Array[0]!=2)  return 3;   //start only when user click Start Game
    int pXc, pYc, pXcc, pYcc;
    pXc = (posx-BOARD_LEFT_EDGE) / BOARD_HOR_MARGIN;    
    pXcc = (posx-BOARD_LEFT_EDGE) % BOARD_HOR_MARGIN;
    pYc = (posy-BOARD_TOP_EDGE) / BOARD_VER_MARGIN;
    pYcc = (posy-BOARD_TOP_EDGE) % BOARD_VER_MARGIN;
    if (pXcc > BOARD_HOR_MARGIN/2)
    {
        pXc++;
        pXcc = BOARD_HOR_MARGIN - pXcc;
    }
    if (pYcc > BOARD_VER_MARGIN/2)
    {
        pYc++;
        pYcc = BOARD_VER_MARGIN - pYcc;
    }
    if (posx<BOARD_LEFT_EDGE && (BOARD_LEFT_EDGE-posx)<BOARD_PIECE_OFFSET)
    {
        pXc = 0;
        pXcc = BOARD_LEFT_EDGE-posx;
    }
    if (posy<BOARD_TOP_EDGE && (BOARD_TOP_EDGE-posy)<BOARD_PIECE_OFFSET)
    {
        pYc = 0;
        pYcc = BOARD_TOP_EDGE-posy;
    }
    
    if ((pXcc*pXcc+pYcc*pYcc)>BOARD_PIECE_OFFSET*BOARD_PIECE_OFFSET)    return 3;
    if (pXc < 0 || pYc < 0 || pXc >= BOARD_CELL_NO || pYc >= BOARD_CELL_NO) return 3;
    if (Piece_Record[pYc][pXc] != 0)  return 3;
    //return 0 when B wins, 1 when W wins, 2 otherwise
    int game_status = gobang_place_piece(pXc, pYc);
    if (game_status==2 && Instr_Array[3]==0) //Peer-to-PC
    {
        int CPiece[3];
        gobang_ai_algorithm(CPiece, Ongame_Array[2]);   //computer generate position of piece,
                                                        //Cpiece-to store position, Ongame_Array[2]-current piece color
        game_status = gobang_place_piece(CPiece[0], CPiece[1]);
    }
    
    switch (game_status)
    {
        case 0: 
            gobang_proc_win(0); //黑方胜
            break;
        case 1:
            gobang_proc_win(1); //白方胜
            break;
        case 2:
            break;
        default:
            break;
    }
    return game_status;
}
//-------------------------------------------------------------------------
unsigned int gobang_handcut_check(int piece_record[][BOARD_CELL_NO][8], unsigned int isWhiteMode, int pXc, int pYc)
{
    if (isWhiteMode)    return 0;
    
    int piece_next = 0;
    int piece_next2 = 0;    //for the other cordinate of lean direction
    int hand_cut_three = 0;
    int hand_cut_four = 0;
    int hand_cut_six = 0;
    int handcut_record[8][6];   //8 Directions, 6 Kinds of Handcut
    int i, j;
    for (i=0; i<8; ++i)
        for (j=0; j<6; ++j)
            handcut_record[i][j] = 0;
    ///////////////////////////////////////////////////////////////////
    //         Start check hand-cut of horizontal direction          //
    ///////////////////////////////////////////////////////////////////
    //1-"***"
    if (piece_record[pYc][pXc][0] == 3)
    {
        handcut_record[0][0]++;
        handcut_record[1][0] = -1;
        hand_cut_three++;
    }
    //2-"** *"
    piece_next = pXc - piece_record[pYc][pXc][1] - 1;
    if (piece_next>=0 && piece_record[pYc][pXc][0]*piece_record[pYc][piece_next][0] == 2 )
    {
        handcut_record[0][1]++;
        hand_cut_three++;
    }
    piece_next = pXc + piece_record[pYc][pXc][0] - piece_record[pYc][pXc][1] + 2;
    if (piece_next<BOARD_CELL_NO && piece_record[pYc][pXc][0]*piece_record[pYc][piece_next][0] == 2 )
    {
        handcut_record[1][1]++;
        hand_cut_three++;
    }
    //3-"****"
    if (piece_record[pYc][pXc][0] == 4)
    {
        handcut_record[0][2]++;
        handcut_record[1][2] = -1;
        hand_cut_four++;
    }
    //4-"*** *"
    piece_next = pXc - piece_record[pYc][pXc][1] - 1;
    if (piece_next>=0 && piece_record[pYc][pXc][0]*piece_record[pYc][piece_next][0] == 3 )
    {
        handcut_record[0][3]++;
        hand_cut_four++;
    }
    piece_next = pXc + piece_record[pYc][pXc][0] - piece_record[pYc][pXc][1] + 2;
    if (piece_next<BOARD_CELL_NO && piece_record[pYc][pXc][0]*piece_record[pYc][piece_next][0] == 3 )
    {
        handcut_record[1][3]++;
        hand_cut_four++;
    }
    //5-"** **"
    piece_next = pXc - piece_record[pYc][pXc][1] - 1;
    if (piece_next>=0 && piece_record[pYc][pXc][0] == 2 && piece_record[pYc][piece_next][0] == 2 )
    {
        handcut_record[0][4]++;
        hand_cut_four++;
    }
    piece_next = pXc + piece_record[pYc][pXc][0] - piece_record[pYc][pXc][1] + 2;
    if (piece_next<BOARD_CELL_NO && piece_record[pYc][pXc][0] == 2 && piece_record[pYc][piece_next][0] == 2 )
    {
        handcut_record[1][4]++;
        hand_cut_four++;
    }
    //6-"***...***"
    if (piece_record[pYc][pXc][0] > 5)
    {
        handcut_record[0][5]++;
        handcut_record[1][5] = -1;
        hand_cut_six++;
    }
    //////////////////////////////////////////////////////////////////
    //         Start check hand-cut of verticle direction           //
    ///////////////////////////////////////////////////////////////////
    //1-"***"
    if (piece_record[pYc][pXc][2] == 3)
    {
        handcut_record[2][0]++;
        handcut_record[3][0] = -1;
        hand_cut_three++;
    }
    //2-"** *"
    piece_next = pYc - piece_record[pYc][pXc][3] - 1;
    if (piece_next>=0 && piece_record[pYc][pXc][2]*piece_record[piece_next][pXc][2] == 2 )
    {
        handcut_record[2][1]++;
        hand_cut_three++;
    }
    piece_next = pYc + piece_record[pYc][pXc][2] - piece_record[pYc][pXc][3] + 2;
    if (piece_next<BOARD_CELL_NO && piece_record[pYc][pXc][2]*piece_record[piece_next][pXc][2] == 2 )
    {
        handcut_record[3][1]++;
        hand_cut_three++;
    }
    //3-"****"
    if (piece_record[pYc][pXc][2] == 4)
    {
        handcut_record[2][2]++;
        handcut_record[3][2] = -1;
        hand_cut_four++;
    }
    //4-"*** *"
    piece_next = pYc - piece_record[pYc][pXc][3] - 1;
    if (piece_next>=0 && piece_record[pYc][pXc][2]*piece_record[piece_next][pXc][2] == 3 )
    {
        handcut_record[2][3]++;
        hand_cut_four++;
    }
    piece_next = pYc + piece_record[pYc][pXc][2] - piece_record[pYc][pXc][3] + 2;
    if (piece_next<BOARD_CELL_NO && piece_record[pYc][pXc][2]*piece_record[piece_next][pXc][2] == 3 )
    {
        handcut_record[3][3]++;
        hand_cut_four++;
    }
    //5-"** **"
    piece_next = pYc - piece_record[pYc][pXc][3] - 1;
    if (piece_next>=0 && piece_record[pYc][pXc][2] == 2 && piece_record[piece_next][pXc][2] == 2 )
    {
        handcut_record[2][4]++;
        hand_cut_four++;
    }
    piece_next = pYc + piece_record[pYc][pXc][2] - piece_record[pYc][pXc][3] + 2;
    if (piece_next<BOARD_CELL_NO && piece_record[pYc][pXc][2] == 2 && piece_record[piece_next][pXc][2] == 2 )
    {
        handcut_record[3][4]++;
        hand_cut_four++;
    }
    //6-"***...***"
    if (piece_record[pYc][pXc][2] > 5)
    {
        handcut_record[2][5]++;
        handcut_record[3][5] = -1;
        hand_cut_six++;
    }
    ///////////////////////////////////////////////////////////////////
    //          Start check hand-cut of BL-to-TR direction           //
    ///////////////////////////////////////////////////////////////////
    //1-"***"
    if (piece_record[pYc][pXc][4] == 3)
    {
        handcut_record[4][0]++;
        handcut_record[5][0] = -1;
        hand_cut_three++;
    }
    //2-"** *"
    piece_next = pXc - piece_record[pYc][pXc][5] - 1;
    piece_next2 = pYc +  piece_record[pYc][pXc][5] + 1;
    if (piece_next>=0 && piece_next2<BOARD_CELL_NO && piece_record[pYc][pXc][4]*piece_record[piece_next2][piece_next][4] == 2 )
    {
        handcut_record[4][1]++;
        hand_cut_three++;
    }
    piece_next = pXc + piece_record[pYc][pXc][4] - piece_record[pYc][pXc][5] + 2;
    piece_next2 = pYc - piece_record[pYc][pXc][4] + piece_record[pYc][pXc][5] - 2;
    if (piece_next<BOARD_CELL_NO && piece_next2>=0 && piece_record[pYc][pXc][4]*piece_record[piece_next2][piece_next][4] == 2 )
    {
        handcut_record[5][1]++;
        hand_cut_three++;
    }
    //3-"****"
    if (piece_record[pYc][pXc][4] == 4)
    {
        handcut_record[4][2]++;
        handcut_record[5][2] = -1;
        hand_cut_four++;
    }
    //4-"*** *"
    piece_next = pXc - piece_record[pYc][pXc][5] - 1;
    piece_next2 = pYc +  piece_record[pYc][pXc][5] + 1;
    if (piece_next>=0 && piece_next2<BOARD_CELL_NO && piece_record[pYc][pXc][4]*piece_record[piece_next2][piece_next][4] == 3 )
    {
        handcut_record[4][3]++;
        hand_cut_four++;
    }
    piece_next = pXc + piece_record[pYc][pXc][4] - piece_record[pYc][pXc][5] + 2;
    piece_next2 = pYc - piece_record[pYc][pXc][4] + piece_record[pYc][pXc][5] - 2;
    if (piece_next<BOARD_CELL_NO && piece_next2>=0 && piece_record[pYc][pXc][4]*piece_record[piece_next2][piece_next][4] == 3 )
    {
        handcut_record[5][3]++;
        hand_cut_four++;
    }
    //5-"** **"
    piece_next = pXc - piece_record[pYc][pXc][5] - 1;
    piece_next2 = pYc +  piece_record[pYc][pXc][5] + 1;
    if (piece_next>=0 && piece_next2<BOARD_CELL_NO && piece_record[pYc][pXc][4]==2 && piece_record[piece_next2][piece_next][4] == 2 )
    {
        handcut_record[4][4]++;
        hand_cut_four++;
    }
    piece_next = pXc + piece_record[pYc][pXc][4] - piece_record[pYc][pXc][5] + 2;
    piece_next2 = pYc - piece_record[pYc][pXc][4] + piece_record[pYc][pXc][5] - 2;
    if (piece_next<BOARD_CELL_NO && piece_next2>=0 && piece_record[pYc][pXc][4]==2 && piece_record[piece_next2][piece_next][4] == 2 )
    {
        handcut_record[5][4]++;
        hand_cut_four++;
    }
    //6-"***...***"
    if (piece_record[pYc][pXc][4] > 5)
    {
        handcut_record[4][5]++;
        handcut_record[5][5] = -1;
        hand_cut_six++;
    }
    ///////////////////////////////////////////////////////////////////
    //          Start check hand-cut of TL-to-BR direction           //
    ///////////////////////////////////////////////////////////////////
    //1-"***"
    if (piece_record[pYc][pXc][6] == 3)
    {
        handcut_record[6][0]++;
        handcut_record[7][0] = -1;
        hand_cut_three++;
    }
    //2-"** *"
    piece_next = pXc - piece_record[pYc][pXc][7] - 1;
    piece_next2 = pYc - piece_record[pYc][pXc][7] - 1;
    if (piece_next>=0 && piece_next2>=0 && piece_record[pYc][pXc][6]*piece_record[piece_next2][piece_next][6] == 2 )
    {
        handcut_record[6][1]++;
        hand_cut_three++;
    }
    piece_next = pXc + piece_record[pYc][pXc][6] - piece_record[pYc][pXc][7] + 2;
    piece_next2 = pYc + piece_record[pYc][pXc][6] - piece_record[pYc][pXc][7] + 2;
    if (piece_next<BOARD_CELL_NO && piece_next2<BOARD_CELL_NO && piece_record[pYc][pXc][6]*piece_record[piece_next2][piece_next][6] == 2 )
    {
        handcut_record[7][1]++;
        hand_cut_three++;
    }
    //3-"****"
    if (piece_record[pYc][pXc][6] == 4)
    {
        handcut_record[6][2]++;
        handcut_record[7][2] = -1;
        hand_cut_four++;
    }
    //4-"*** *"
    piece_next = pXc - piece_record[pYc][pXc][7] - 1;
    piece_next2 = pYc - piece_record[pYc][pXc][7] - 1;
    if (piece_next>=0 && piece_next2>=0 && piece_record[pYc][pXc][6]*piece_record[piece_next2][piece_next][6] == 3 )
    {
        handcut_record[6][3]++;
        hand_cut_four++;
    }
    piece_next = pXc + piece_record[pYc][pXc][6] - piece_record[pYc][pXc][7] + 2;
    piece_next2 = pYc + piece_record[pYc][pXc][6] - piece_record[pYc][pXc][7] + 2;
    if (piece_next<BOARD_CELL_NO && piece_next2<BOARD_CELL_NO && piece_record[pYc][pXc][6]*piece_record[piece_next2][piece_next][6] == 3 )
    {
        handcut_record[7][3]++;
        hand_cut_four++;
    }
    //5-"** **"
    piece_next = pXc - piece_record[pYc][pXc][7] - 1;
    piece_next2 = pYc - piece_record[pYc][pXc][7] - 1;
    if (piece_next>=0 && piece_next2>=0 && piece_record[pYc][pXc][6]==2 && piece_record[piece_next2][piece_next][6] == 2 )
    {
        handcut_record[6][4]++;
        hand_cut_four++;
    }
    piece_next = pXc + piece_record[pYc][pXc][6] - piece_record[pYc][pXc][7] + 2;
    piece_next2 = pYc + piece_record[pYc][pXc][6] - piece_record[pYc][pXc][7] + 2;
    if (piece_next<BOARD_CELL_NO && piece_next2<BOARD_CELL_NO && piece_record[pYc][pXc][6]==2 && piece_record[piece_next2][piece_next][6] == 2 )
    {
        handcut_record[7][4]++;
        hand_cut_four++;
    }
    //6-"***...***"
    if (piece_record[pYc][pXc][6] > 5)
    {
        handcut_record[6][5]++;
        handcut_record[7][5] = -1;
        hand_cut_six++;
    }
        
    if (hand_cut_three >= 2 || hand_cut_four >= 2 || hand_cut_six >= 1)
    { 
        gobang_draw_circle(BOARD_PIECE_RADIUS/2, (pXc*BOARD_HOR_MARGIN+BOARD_LEFT_EDGE), (pYc*BOARD_VER_MARGIN+BOARD_TOP_EDGE));
        
        Instr_Array[0] = 0;
        int IBDebug_Left, IBDebug_Top;
        IBDebug_Left=480; IBDebug_Top=170;
        gobang_box_fill(120, 275, IBDebug_Left, IBDebug_Top);       
        gobang_show_text("调试结果：", IBDebug_Left, IBDebug_Top);
        gobang_show_text("pXc=", IBDebug_Left, IBDebug_Top+25); gobang_show_num((pXc+1), IBDebug_Left+40, IBDebug_Top+25);
        gobang_show_text("pYc=", IBDebug_Left+60, IBDebug_Top+25); gobang_show_num((pYc+1), IBDebug_Left+100, IBDebug_Top+25);
        
        gobang_show_text("PIECE_RECORD:", IBDebug_Left, IBDebug_Top+45);
//        int i, j;
        for (i=0; i<4; ++i)
        {
            gobang_show_num(piece_record[pYc][pXc][2*i], (IBDebug_Left+20*i), IBDebug_Top+65);
            gobang_show_num(piece_record[pYc][pXc][2*i+1], (IBDebug_Left+20*i), IBDebug_Top+85);
        }
        gobang_show_text("***************", IBDebug_Left, IBDebug_Top+105);
        for (i=0; i<8; ++i)
            for (j=0; j<6; ++j)
            {
                gobang_show_num(handcut_record[i][j], (IBDebug_Left+20*j), (IBDebug_Top+125+16*i));
            }
        
//        gobang_show_text("3连=", 480, 290); gobang_show_num(hand_cut_three, 540, 290);
//        gobang_show_text("4连=", 480, 310); gobang_show_num(hand_cut_four, 540, 310);
//        gobang_show_text("6连=", 480, 330); gobang_show_num(hand_cut_six, 540, 330);
        
        return 1;
    }
    
    return 0;
}
