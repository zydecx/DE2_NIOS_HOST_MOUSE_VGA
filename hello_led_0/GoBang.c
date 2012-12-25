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
    
    gobang_instrB_ondisplay();
//    Ongame_Array[2] = 1 - Ongame_Array[2];  //turn to another user
    
    int IBFunc_Left, IBFunc_Top;
    IBFunc_Left=IBCont_Left; IBFunc_Top=IBPiece_Top+100;//200
    
    //本局：先手执黑
    if (Instr_Array[3]==0 && Instr_Array[4]==Ongame_Array[1]%2)
        gobang_show_text("本局：用户执黑", IBFunc_Left, IBFunc_Top-25);
    else if (Instr_Array[3]==0 && Instr_Array[4]!=Ongame_Array[1]%2)
        gobang_show_text("本局：电脑执黑", IBFunc_Left, IBFunc_Top-25);
    else if (Ongame_Array[1]%2 == 1)
        gobang_show_text("本局：先手执黑", IBFunc_Left, IBFunc_Top-25);
    else
        gobang_show_text("本局：后手执黑", IBFunc_Left, IBFunc_Top-25);
        
    //共#局，第#局
    gobang_show_text("共", IBFunc_Left, IBFunc_Top);
    gobang_show_num(Ongame_Array[0], IBFunc_Left+16, IBFunc_Top);
    gobang_show_text("局,", IBFunc_Left+24, IBFunc_Top);
    gobang_show_text("第", IBFunc_Left+56, IBFunc_Top);
    gobang_show_num(Ongame_Array[1], IBFunc_Left+72, IBFunc_Top);
    gobang_show_text("局", IBFunc_Left+80, IBFunc_Top);
    
    unsigned char text4[] = "胜负情况：";
    gobang_show_text(text4, IBFunc_Left, IBFunc_Top+25);
    if (Instr_Array[3]==0 && Instr_Array[4]==1)
    {
        gobang_show_text("用户", IBFunc_Left, IBFunc_Top+50);
        gobang_show_text("电脑", IBFunc_Left+60, IBFunc_Top+50);
    }
    else if (Instr_Array[3]==0 && Instr_Array[4]==0)
    {
        gobang_show_text("电脑", IBFunc_Left, IBFunc_Top+50);
        gobang_show_text("用户", IBFunc_Left+60, IBFunc_Top+50);
    }
    else
    {
        gobang_show_text("先手", IBFunc_Left, IBFunc_Top+50);
        gobang_show_text("后手", IBFunc_Left+60, IBFunc_Top+50);
    }
    gobang_show_num(Ongame_Array[3], IBFunc_Left+40, IBFunc_Top+50);
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
void gobang_instrB_ondisplay()
{
    int IBox_Width, IBCont_Left, IBPiece_Left, IBPiece_Top;
    IBox_Width=130;IBCont_Left=480;IBPiece_Left=IBCont_Left; IBPiece_Top=125;
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
    IBFunc_Left=IBCont_Left; IBFunc_Top=IBPiece_Top+100;//200
    
    //本局：先手执黑
    if (Instr_Array[3]==0 && Instr_Array[4]==Ongame_Array[1]%2)
        gobang_show_text("本局：用户执黑", IBFunc_Left, IBFunc_Top-25);
    else if (Instr_Array[3]==0 && Instr_Array[4]!=Ongame_Array[1]%2)
        gobang_show_text("本局：电脑执黑", IBFunc_Left, IBFunc_Top-25);
    else if (Ongame_Array[1]%2 == 1)
        gobang_show_text("本局：先手执黑", IBFunc_Left, IBFunc_Top-25);
    else
        gobang_show_text("本局：后手执黑", IBFunc_Left, IBFunc_Top-25);
    
    //共#局，第#局
    gobang_show_text("共", IBFunc_Left, IBFunc_Top);
    gobang_show_num(Ongame_Array[0], IBFunc_Left+16, IBFunc_Top);
    gobang_show_text("局,", IBFunc_Left+24, IBFunc_Top);
    gobang_show_text("第", IBFunc_Left+56, IBFunc_Top);
    gobang_show_num(Ongame_Array[1], IBFunc_Left+72, IBFunc_Top);
    gobang_show_text("局", IBFunc_Left+80, IBFunc_Top);
    
    
    unsigned char text4[] = "胜负情况：";
    gobang_show_text(text4, IBFunc_Left, IBFunc_Top+25);
    if (Instr_Array[3]==0 && Instr_Array[4]==1)
    {
        gobang_show_text("用户", IBFunc_Left, IBFunc_Top+50);
        gobang_show_text("电脑", IBFunc_Left+60, IBFunc_Top+50);
    }
    else if (Instr_Array[3]==0 && Instr_Array[4]==0)
    {
        gobang_show_text("电脑", IBFunc_Left, IBFunc_Top+50);
        gobang_show_text("用户", IBFunc_Left+60, IBFunc_Top+50);
    }
    else
    {
        gobang_show_text("先手", IBFunc_Left, IBFunc_Top+50);
        gobang_show_text("后手", IBFunc_Left+60, IBFunc_Top+50);
    }
    gobang_show_num(Ongame_Array[3], IBFunc_Left+40, IBFunc_Top+50);
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
void gobang_instrD_display(int winner)  //winner:0-先手;1-后手
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
    unsigned char textWin2[] = "******后手获胜******";
    unsigned char textWin3[] = "******先手获胜******";
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
    if (Instr_Array[3]==0 && Instr_Array[4]==1)
    {
        gobang_show_text("用户", IBFunc_Left, IBFunc_Top+50);
        gobang_show_text("电脑", IBFunc_Left+60, IBFunc_Top+50);
    }
    else if (Instr_Array[3]==0 && Instr_Array[4]==0)
    {
        gobang_show_text("电脑", IBFunc_Left, IBFunc_Top+50);
        gobang_show_text("用户", IBFunc_Left+60, IBFunc_Top+50);
    }
    else
    {
        gobang_show_text("先手", IBFunc_Left, IBFunc_Top+50);
        gobang_show_text("后手", IBFunc_Left+60, IBFunc_Top+50);
    }
    gobang_show_num(Ongame_Array[3], IBFunc_Left+40, IBFunc_Top+50);
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
   for (ex = 0; ex < AI_SEARCH_REGION; ++ex)
        AI_Region[ex] = 7;
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
    Ongame_Array[2] = 0;
    Piece_History[0][1] = 0;Piece_History[0][2] = 0;    //return from replay function
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
        
        if (Instr_Array[3]==0 && Instr_Array[4]!=(Ongame_Array[1]%2)) //Peer-to-PC 
        {
            int CPiece[3];
            gobang_proc_ai(CPiece, Ongame_Array[2]);   //computer generate position of piece,
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
void gobang_draw_piece(int pXc, int pYc, int isWhite)
{
    if (isWhite == 1)
    {
        gobang_draw_circle(BOARD_PIECE_RADIUS, (pXc*BOARD_HOR_MARGIN+BOARD_LEFT_EDGE), (pYc*BOARD_VER_MARGIN+BOARD_TOP_EDGE));
    }
    else
    {
        gobang_draw_circle(BOARD_PIECE_RADIUS, (pXc*BOARD_HOR_MARGIN+BOARD_LEFT_EDGE), (pYc*BOARD_VER_MARGIN+BOARD_TOP_EDGE));
        gobang_clear_circle(BOARD_PIECE_RADIUS*5/6, (pXc*BOARD_HOR_MARGIN+BOARD_LEFT_EDGE), (pYc*BOARD_VER_MARGIN+BOARD_TOP_EDGE));
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
                gobang_proc_ai(CPiece, Ongame_Array[2]);   //computer generate position of piece,
                                                                //Cpiece-to store position, Ongame_Array[2]-current piece color
                gobang_place_piece(CPiece[0], CPiece[1]);
            }
        }
    }
    else if (Instr_Array[0] == 2)
    {
        //是否悔棋
        int IBStart_Left, IBStart_Top, IBStart_Right, IBStart_Bottom;
        if (Ongame_Array[5]==0)
        {
            IBStart_Left=500;IBStart_Top=348;IBStart_Right=570;IBStart_Bottom=376;
            if (posx>IBStart_Left && posx<IBStart_Right && posy>IBStart_Top && posy<IBStart_Bottom)
            {
                gobang_roll_back();//悔棋处理函数
            }
        }
        else
        {
            IBStart_Left=483;IBStart_Top=325;IBStart_Right=517;IBStart_Bottom=353;
            if (posx>IBStart_Left && posx<IBStart_Right && posy>IBStart_Top && posy<IBStart_Bottom)
            {
                Ongame_Array[5] = 2;    //同意
                gobang_roll_back();//悔棋处理函数
            }
            IBStart_Left=540;IBStart_Top=325;IBStart_Right=574;IBStart_Bottom=353;
            if (posx>IBStart_Left && posx<IBStart_Right && posy>IBStart_Top && posy<IBStart_Bottom)
            {
                Ongame_Array[5] = 3;    //不同意
                gobang_roll_back();//悔棋处理函数
            }
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
            gobang_replay_game();//回放棋局处理函数
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
void gobang_roll_back()    //悔棋处理函数
{
    int IBPlay_Width, IBPlay_Height, IBPlay_Left, IBPlay_Top;
    if (Instr_Array[3] == 1 && Ongame_Array[5] == 0)
    {
        Ongame_Array[5] = 1;
        IBPlay_Width=40; IBPlay_Height=35; IBPlay_Left=480; IBPlay_Top=305;
        gobang_box_fill(120, 75, IBPlay_Left, IBPlay_Top);
        unsigned char text1[] = "对手请求悔棋？";
        gobang_show_text(text1, IBPlay_Left, IBPlay_Top);
        
        gobang_box_fullfill(IBPlay_Width, IBPlay_Height, IBPlay_Left, IBPlay_Top+20);
        gobang_box_fill(34, IBPlay_Height*4/5, IBPlay_Left+3, IBPlay_Top+23);
        gobang_box_outline(IBPlay_Width, IBPlay_Height, IBPlay_Left, IBPlay_Top+20); 
        gobang_show_text("同意", IBPlay_Left+4, IBPlay_Top+28);
        gobang_box_fullfill(IBPlay_Width, IBPlay_Height, IBPlay_Left+60, IBPlay_Top+20);
        gobang_box_fill(34, IBPlay_Height*4/5, IBPlay_Left+63, IBPlay_Top+23);
        gobang_box_outline(IBPlay_Width, IBPlay_Height, IBPlay_Left+60, IBPlay_Top+20); 
        gobang_show_text("拒绝", IBPlay_Left+64, IBPlay_Top+28);
        return;
    }
    else  //其他模式
    {
        IBPlay_Left=480; IBPlay_Top=305;
        gobang_box_fill(120, 75, IBPlay_Left, IBPlay_Top);
        unsigned char text2[] = "请求悔棋";
        IBPlay_Width=80; IBPlay_Height=35; IBPlay_Left=480+15; IBPlay_Top=345;
        gobang_box_fullfill(IBPlay_Width, IBPlay_Height, IBPlay_Left, IBPlay_Top);
        gobang_box_fill(70, IBPlay_Height*4/5, IBPlay_Left+5, IBPlay_Top+3);
        gobang_box_outline(IBPlay_Width, IBPlay_Height, IBPlay_Left, IBPlay_Top); 
        gobang_show_text(text2, IBPlay_Left+8, IBPlay_Top+8);
    }
    
    //对方不同意，或悔棋范围越界
    if ((Instr_Array[3]==1 && Ongame_Array[5]==3) || ((Piece_History[0][0]-2)<0))
    {
        Ongame_Array[5] = 0;
        return;
    }
    //人机模式或人人模式下对方已同意
    gobang_box_fill(474, 480, 0, 0);
    gobang_board_display();
    
    int phis_size = Piece_History[0][0] - 2;
    int i, j;
    int phis[PIECE_HISTORY_NO][3];
    for (i=0; i<=phis_size; ++i)
        for (j=0; j<3; ++j)
            phis[i][j] = Piece_History[i][j];
    reset_piece_record_array();
    
    if (phis_size==0)
    {
        gobang_instrB_ondisplay();
    }
    else
    {
        for (i=1; i<=phis_size; ++i)
        {
            Ongame_Array[2] = phis[i][2];
            gobang_place_piece(phis[i][0], phis[i][1]);
        }
    }
    Ongame_Array[5] = 0;
}
//-------------------------------------------------------------------------
void gobang_replay_game()  //回放处理函数 
{
    int IBFunc_Left, IBPlay_Width, IBPlay_Height, IBPlay_Left, IBPlay_Top;
    IBFunc_Left=480;IBPlay_Width=80;IBPlay_Height=35;IBPlay_Left=IBFunc_Left+15;IBPlay_Top=305;
    if (Piece_History[0][1] == 0)   //operate this function for the first time
    {
        Piece_History[0][1] = 1;    //set to replay state
        Piece_History[0][2]++;
        
        gobang_box_fill(70, IBPlay_Height*4/5, IBPlay_Left+5, IBPlay_Top+3);
        gobang_show_text(" 下一步", IBPlay_Left+8, IBPlay_Top+8);
        
//        clean_screen();
//        gobang_box_fill((INSTR_BORDER-1), (BOARD_VER_MARGIN-5), 0, 0);
        gobang_box_fill(474, 480, 0, 0);
        gobang_board_display();
        
        gobang_draw_piece(Piece_History[Piece_History[0][2]][0], Piece_History[Piece_History[0][2]][1], Piece_History[Piece_History[0][2]][2]);
    }
    else
    {
        Piece_History[0][2]++;
        gobang_draw_piece(Piece_History[Piece_History[0][2]][0], Piece_History[Piece_History[0][2]][1], Piece_History[Piece_History[0][2]][2]);
        
        if (Piece_History[0][2]>=Piece_History[0][0])
        {
            gobang_box_fill(70, IBPlay_Height*4/5, IBPlay_Left+5, IBPlay_Top+3);
            gobang_show_text("棋局回放", IBPlay_Left+8, IBPlay_Top+8);
            Piece_History[0][1] = 0;    //reset state
            Piece_History[0][2] = 0;
        }
    }
}
//-------------------------------------------------------------------------
void gobang_proc_ai(int PiecePos[3], int isWhite)
{
//    int ex, ey;
//    for (ex=0; ex<BOARD_CELL_NO; ++ex)
//        for (ey=0; ey<BOARD_CELL_NO; ++ey)
//        {
//            if (Piece_Record[ey][ex]==0)
//            {
//                PiecePos[0] = ex;
//                PiecePos[1] = ey;
//                PiecePos[2] = isWhite;
//                return;
//            }
//        }
    int opti_pos[2];
    while(gobang_opti_score(opti_pos, isWhite) == -1)
    {
        AI_Region[0] = (AI_Region[0]-2)>=0 ? (AI_Region[0]-2) : 0;
        AI_Region[1] = (AI_Region[1]+2)<BOARD_CELL_NO ? (AI_Region[1]+2) : (BOARD_CELL_NO-1);
        AI_Region[2] = (AI_Region[2]-2)>=0 ? (AI_Region[2]-1) : 0;
        AI_Region[3] = (AI_Region[3]+2)<BOARD_CELL_NO ? (AI_Region[3]+2) : (BOARD_CELL_NO-1); 
    }
    PiecePos[0] = opti_pos[0];
    PiecePos[1] = opti_pos[1];
    PiecePos[2] = isWhite;
}
//-------------------------------------------------------------------------
int gobang_opti_score(int pos[2], int isWhite)
{
    int optipx, optipy, optiscore;
    optipx = optipy = -1;
    optiscore = -10000;
    int ex, ey, ez;
    int ai_alys_array[BOARD_CELL_NO][BOARD_CELL_NO][2];
    int alys_recrd[BOARD_CELL_NO][BOARD_CELL_NO][8];
    int ps_recrd[BOARD_CELL_NO][BOARD_CELL_NO];
    for (ex=0; ex<BOARD_CELL_NO; ++ex)
        for (ey=0; ey<BOARD_CELL_NO; ++ey)
        {
            ps_recrd[ex][ey] = Piece_Record[ex][ey];
            for (ez=0; ez<8; ++ez)
                alys_recrd[ex][ey][ez] = Piece_Analysis_Record[ex][ey][ez];
        }
    
    for (ex=AI_Region[0]; ex<=AI_Region[1]; ++ex)
        for (ey=AI_Region[2]; ey<=AI_Region[3]; ++ey)
        {
            if (Piece_Record[ey][ex]!=0)
            {
                ai_alys_array[ey][ex][0] = -10;
                ai_alys_array[ey][ex][1] = -10;
                continue;
            }    
            else
            {
                int ex1, ey1, ez1;
                for (ex1=0; ex1<BOARD_CELL_NO; ++ex1)
                    for (ey1=0; ey1<BOARD_CELL_NO; ++ey1)
                    {
                        ps_recrd[ex1][ey1] = Piece_Record[ex1][ey1];
                        for (ez1=0; ez1<8; ++ez1)
                            alys_recrd[ex1][ey1][ez1] = Piece_Analysis_Record[ex1][ey1][ez1];
                    }
                ps_recrd[ey][ex] = 1-2*isWhite;
                if (gobang_update_state(alys_recrd,ps_recrd, ex, ey, isWhite)==(1-isWhite))
                    ai_alys_array[ey][ex][0] = -10;  //当造成对方获胜,则舍弃该方案
                else
                {
                    ai_alys_array[ey][ex][0] = gobang_get_score(alys_recrd,ps_recrd,ex, ey, isWhite);
                }
                for (ex1=0; ex1<BOARD_CELL_NO; ++ex1)
                    for (ey1=0; ey1<BOARD_CELL_NO; ++ey1)
                    {
                        ps_recrd[ex1][ey1] = Piece_Record[ex1][ey1];
                        for (ez1=0; ez1<8; ++ez1)
                            alys_recrd[ex1][ey1][ez1] = Piece_Analysis_Record[ex1][ey1][ez1];
                    }
                ps_recrd[ey][ex] = 1-2*(1-isWhite);
                if (gobang_update_state(alys_recrd,ps_recrd, ex, ey, (1-isWhite))==isWhite)
                    ai_alys_array[ey][ex][1] = -10;  //当造成对方获胜,则舍弃该方案
                else
                {
                    ai_alys_array[ey][ex][1] = gobang_get_score(alys_recrd,ps_recrd,ex, ey, (1-isWhite));
                }
                ps_recrd[ey][ex] = 0;
            }
            
            if (ai_alys_array[ey][ex][0]>=optiscore)
            {
                optipx = ex;
                optipy = ey;
                optiscore = ai_alys_array[ey][ex][0];
            }
            if (ai_alys_array[ey][ex][1]>=optiscore)
            {
                optipx = ex;
                optipy = ey;
                optiscore = ai_alys_array[ey][ex][1];
            }
        }
   
   if (optipx==-1  || optipy==-1)
   {
        for (ex=0; ex<BOARD_CELL_NO; ++ex)
            for (ey=0; ey<BOARD_CELL_NO; ++ey)
            {
                if (Piece_Record[ey][ex]==0)
                {
                    optipx = ex;
                    optipy = ey;
                    break;
                }
            }
   }
   pos[0] = optipx; pos[1] = optipy;
   return optiscore;
}
//-------------------------------------------------------------------------
int gobang_ai_algorithm(int pXc, int pYc, int isWhite)
{
    int total_score=0;
    int ex, ey, ez;
    int alys_recrd[BOARD_CELL_NO][BOARD_CELL_NO][8];
    int ps_recrd[BOARD_CELL_NO][BOARD_CELL_NO];
    for (ex=0; ex<BOARD_CELL_NO; ++ex)
        for (ey=0; ey<BOARD_CELL_NO; ++ey)
        {
            ps_recrd[ex][ey] = Piece_Record[ex][ey];
            for (ez=0; ez<8; ++ez)
                alys_recrd[ex][ey][ez] = Piece_Analysis_Record[ex][ey][ez];
        }
    ps_recrd[pYc][pXc] = 1-2*isWhite;
    if (gobang_update_state(alys_recrd,ps_recrd, pXc, pYc, isWhite)==(1-isWhite))
        return -1;  //当造成对方获胜,则舍弃该方案
    total_score += gobang_get_score(alys_recrd,ps_recrd,pXc, pYc, isWhite);
    ps_recrd[pYc][pXc] = 0;
    return total_score;
}
//-------------------------------------------------------------------------
int gobang_get_score(int alys_recrd[][BOARD_CELL_NO][8], int ps_recrd[][BOARD_CELL_NO],int pXc, int pYc, int isWhite)
{
    int i;
    int pm1, pn1, pm2, pn2, pm3, pn3;
    pm1=0;pn1=0;pm2=0;pn2=0;pm3=0;pn3=0;
    int total_score = 0;
    int type_recrd[14];
    int type_weigh[14]={4,5,3,13,11,12,16,10,60,52,60,50,6000,10000};
    for (i=0; i<14; ++i) {type_recrd[i]=0;}
/*
    棋型名称       棋型模式         估值
    成五           AAAAA            10000
    活四           ?AAAA?           6000
    死四 A         AAAA?             50
    死四 B         AAA?A             60
    死四 C         AA?AA             52
    活三           ??AAA??           60
    死三 A         AAA??             10
    死三 B         ?A?AA?            16
    死三 C         A??AA             12
    死三 D         A?A?A             11
    活二           ???AA???          13
    死二 A         AA???             3
    死二 B         ??A?A??           5
    死二 C         ?A??A?            4
 * */
    //成5
    //type_recrd[13]
    if (abs(alys_recrd[pYc][pXc][0])>=5) {type_recrd[13]++;}
    if (abs(alys_recrd[pYc][pXc][2])>=5) {type_recrd[13]++;}
    if (abs(alys_recrd[pYc][pXc][4])>=5) {type_recrd[13]++;}
    if (abs(alys_recrd[pYc][pXc][6])>=5) {type_recrd[13]++;}
    //4
    //"****"
    //type_recrd[12],type_recrd[11]
    //horizontal direction
    pm1 = pXc-alys_recrd[pYc][pXc][1];
    pm2 = pXc-alys_recrd[pYc][pXc][1]+abs(alys_recrd[pYc][pXc][0])+1;
    pn1 = pn2 = pYc;
    if (abs(alys_recrd[pYc][pXc][0])==4 && pm1>=0 && pm2<BOARD_CELL_NO && (ps_recrd[pn1][pm1]+ps_recrd[pn2][pm2])==0)
    {type_recrd[12]++;}
    else if (abs(alys_recrd[pYc][pXc][0])==4 && 
        ((pm1>=0 && pm2<BOARD_CELL_NO && ps_recrd[pn1][pm1]*ps_recrd[pn2][pm2]==0)||
        (pm1>=0 && pm2>=BOARD_CELL_NO && ps_recrd[pn1][pm1]==0)||
        (pm1<0 && pm2<BOARD_CELL_NO && ps_recrd[pn2][pm2]==0)) )
    {type_recrd[11]++;}
    //verticle direction
    pn1 = pYc-alys_recrd[pYc][pXc][3];
    pn2 = pYc-alys_recrd[pYc][pXc][3]+abs(alys_recrd[pYc][pXc][2])+1;
    pm1 = pm2 = pXc;
    if (abs(alys_recrd[pYc][pXc][2])==4 && pn1>=0 && pn2<BOARD_CELL_NO && (ps_recrd[pn1][pm1]+ps_recrd[pn2][pm2])==0)
    {type_recrd[12]++;}
    else if (abs(alys_recrd[pYc][pXc][2])==4 && 
        ((pn1>=0 && pn2<BOARD_CELL_NO && ps_recrd[pn1][pm1]*ps_recrd[pn2][pm2]==0)||
        (pn1>=0 && pn2>=BOARD_CELL_NO && ps_recrd[pn1][pm1]==0)||
        (pn1<0 && pn2<BOARD_CELL_NO && ps_recrd[pn2][pm2]==0)) )
    {type_recrd[11]++;}
    //BL-to-TR direction
    pm1 = pXc-alys_recrd[pYc][pXc][5];
    pn1 = pYc+alys_recrd[pYc][pXc][5];
    pm2 = pXc-alys_recrd[pYc][pXc][5]+abs(alys_recrd[pYc][pXc][4])+1;
    pn2 = pYc+alys_recrd[pYc][pXc][5]-abs(alys_recrd[pYc][pXc][4])-1;
    if (abs(alys_recrd[pYc][pXc][4])==4 && pm1>=0 && pn1<BOARD_CELL_NO && pm2<BOARD_CELL_NO && pn2>=0 && (ps_recrd[pn1][pm1]+ps_recrd[pn2][pm2])==0)
    {type_recrd[12]++;}
    else if (abs(alys_recrd[pYc][pXc][4])==4 && 
        ((pm1>=0 && pn1<BOARD_CELL_NO && pm2<BOARD_CELL_NO && pn2>=0 && ps_recrd[pn1][pm1]*ps_recrd[pn2][pm2]==0)||
        (pm1>=0 && pn1<BOARD_CELL_NO && (pm2>=BOARD_CELL_NO || pn2<0) && ps_recrd[pn1][pm1]==0)||
        ((pm1<0 || pn1>=BOARD_CELL_NO) && pm2<BOARD_CELL_NO && pn2>=0 && ps_recrd[pn2][pm2]==0)) )
    {type_recrd[11]++;}
    //TL-to-BR direction
    pm1 = pXc-alys_recrd[pYc][pXc][7];
    pn1 = pYc-alys_recrd[pYc][pXc][7];
    pm2 = pXc-alys_recrd[pYc][pXc][7]+abs(alys_recrd[pYc][pXc][6])+1;
    pn2 = pYc-alys_recrd[pYc][pXc][7]+alys_recrd[pYc][pXc][7]+1;
    if (abs(alys_recrd[pYc][pXc][6])==4 && pm1>=0 && pn1>=0 && pm2<BOARD_CELL_NO && pn2<BOARD_CELL_NO && (ps_recrd[pn1][pm1]+ps_recrd[pn2][pm2])==0)
    {type_recrd[12]++;}
    else if (abs(alys_recrd[pYc][pXc][6])==4 && 
        ((pm1>=0 && pn1>=0 && pm2<BOARD_CELL_NO && pn2<BOARD_CELL_NO && ps_recrd[pn1][pm1]*ps_recrd[pn2][pm2]==0)||
        (pm1>=0 && pn1>=0 && (pm2>=BOARD_CELL_NO || pn2>=BOARD_CELL_NO) && ps_recrd[pn1][pm1])||
        ((pm1<0 || pn1<0) && pm2<BOARD_CELL_NO && pn2<BOARD_CELL_NO && ps_recrd[pn2][pm2]==0)) )
    {type_recrd[11]++;}
    
    //4
    //"*** *"
    //type_recrd[10]
    // horizontal direction 
    pm1 = pXc-alys_recrd[pYc][pXc][1]-1;
    pm2 = pXc-alys_recrd[pYc][pXc][1]+abs(alys_recrd[pYc][pXc][0])+1;
    pn1 = pn2 = pYc;
    if (pm1>=0 && alys_recrd[pYc][pXc][0]*alys_recrd[pn1][pm1][0]==3 && ps_recrd[pn1][pm1+1]==0)
    {type_recrd[10]++;}
    pm1 = pXc-alys_recrd[pYc][pXc][1]+abs(alys_recrd[pYc][pXc][0])+2;
    pm2 = pXc-alys_recrd[pYc][pXc][1];
    pn1 = pn2 = pYc;
    if (pm1<BOARD_CELL_NO && alys_recrd[pYc][pXc][0]*alys_recrd[pn1][pm1][0]==3 && ps_recrd[pn1][pm1-1]==0)
    {type_recrd[10]++;}
    // vertical direction 
    pn1 = pYc-alys_recrd[pYc][pXc][3]-1;
    pn2 = pYc-alys_recrd[pYc][pXc][3]+abs(alys_recrd[pYc][pXc][2])+1;
    pm1 = pm2 = pXc;
    if (pn1>=0 && alys_recrd[pYc][pXc][2]*alys_recrd[pn1][pm1][2]==3 && ps_recrd[pn1+1][pm1]==0)
    {type_recrd[10]++;}
    pn1 = pYc-alys_recrd[pYc][pXc][3]+abs(alys_recrd[pYc][pXc][2])+2;
    pn2 = pYc-alys_recrd[pYc][pXc][3];
    pm1 = pm2 = pXc;
    if (pn1<BOARD_CELL_NO && alys_recrd[pYc][pXc][2]*alys_recrd[pn1][pm1][2]==3 && ps_recrd[pn1-1][pm1]==0)
    {type_recrd[10]++;}
    //BL-to-TR direction
    pm1 = pXc-alys_recrd[pYc][pXc][5]-1;
    pn1 = pYc+alys_recrd[pYc][pXc][5]+1;
    pm2 = pXc-alys_recrd[pYc][pXc][5]+abs(alys_recrd[pYc][pXc][4])+1;
    pn2 = pYc+alys_recrd[pYc][pXc][5]-abs(alys_recrd[pYc][pXc][4])-1;
    if (pm1>=0 && pn1<BOARD_CELL_NO && alys_recrd[pYc][pXc][4]*alys_recrd[pn1][pm1][4]==3 && ps_recrd[pn1-1][pm1+1]==0 )
    {type_recrd[10]++;}
    pm1 = pXc-alys_recrd[pYc][pXc][5]+abs(alys_recrd[pYc][pXc][4])+2;
    pn1 = pYc+alys_recrd[pYc][pXc][5]-abs(alys_recrd[pYc][pXc][4])-2;
    pm2 = pXc-alys_recrd[pYc][pXc][5];
    pn2 = pYc+alys_recrd[pYc][pXc][5];
    if (pm1<BOARD_CELL_NO && pn1>=0 && alys_recrd[pYc][pXc][4]*alys_recrd[pn1][pm1][4]==3 && ps_recrd[pn1+1][pm1-1]==0 )
    {type_recrd[10]++;}
    //TL-to-BR direction
    pm1 = pXc-alys_recrd[pYc][pXc][7]-1;
    pn1 = pYc-alys_recrd[pYc][pXc][7]-1;
    pm2 = pXc-alys_recrd[pYc][pXc][7]+abs(alys_recrd[pYc][pXc][6])+1;
    pn2 = pYc-alys_recrd[pYc][pXc][7]+abs(alys_recrd[pYc][pXc][6])+1;
    if (pm1>=0 && pn1>=0 && alys_recrd[pYc][pXc][6]*alys_recrd[pn1][pm1][6]==3 && ps_recrd[pn1+1][pm1+1]==0 )
    {type_recrd[10]++;}
    pm1 = pXc-alys_recrd[pYc][pXc][7]+abs(alys_recrd[pYc][pXc][6])+2;
    pn1 = pYc-alys_recrd[pYc][pXc][7]+abs(alys_recrd[pYc][pXc][6])+2;
    pm2 = pXc-alys_recrd[pYc][pXc][7];
    pn2 = pYc-alys_recrd[pYc][pXc][7];
    if (pm1<BOARD_CELL_NO && pn1<BOARD_CELL_NO && alys_recrd[pYc][pXc][6]*alys_recrd[pn1][pm1][6]==3 && ps_recrd[pn1-1][pm1-1]==0 )
    {type_recrd[10]++;}
    
    //4
    //"** **"
    //type_recrd[9]
    // horizontal direction 
    pm1 = pXc-alys_recrd[pYc][pXc][1]-1;
    pm2 = pXc-alys_recrd[pYc][pXc][1]+abs(alys_recrd[pYc][pXc][0])+1;
    pn1 = pn2 = pYc;
    if (pm1>=0 && alys_recrd[pYc][pXc][0]==2*(1-2*isWhite) && alys_recrd[pn1][pm1][0]==2*(1-2*isWhite) && ps_recrd[pn1][pm1+1]==0)
    {type_recrd[9]++;}
    pm1 = pXc-alys_recrd[pYc][pXc][1]+abs(alys_recrd[pYc][pXc][0])+2;
    pm2 = pXc-alys_recrd[pYc][pXc][1];
    pn1 = pn2 = pYc;
    if (pm1<BOARD_CELL_NO && alys_recrd[pYc][pXc][0]==2*(1-2*isWhite) && alys_recrd[pn1][pm1][0]==2*(1-2*isWhite) && ps_recrd[pn1][pm1-1]==0)
    {type_recrd[9]++;}
    // vertical direction 
    pn1 = pYc-alys_recrd[pYc][pXc][3]-1;
    pn2 = pYc-alys_recrd[pYc][pXc][3]+abs(alys_recrd[pYc][pXc][2])+1;
    pm1 = pm2 = pXc;
    if (pn1>=0 && alys_recrd[pYc][pXc][2]==2*(1-2*isWhite) && alys_recrd[pn1][pm1][2]==2*(1-2*isWhite) && ps_recrd[pn1+1][pm1]==0)
    {type_recrd[9]++;}
    pn1 = pYc-alys_recrd[pYc][pXc][3]+abs(alys_recrd[pYc][pXc][2])+2;
    pn2 = pYc-alys_recrd[pYc][pXc][3];
    pm1 = pm2 = pXc;
    if (pn1<BOARD_CELL_NO && alys_recrd[pYc][pXc][2]==2*(1-2*isWhite) && alys_recrd[pn1][pm1][2]==2*(1-2*isWhite) && ps_recrd[pn1-1][pm1]==0)
    {type_recrd[9]++;}
    //BL-to-TR direction
    pm1 = pXc-alys_recrd[pYc][pXc][5]-1;
    pn1 = pYc+alys_recrd[pYc][pXc][5]+1;
    pm2 = pXc-alys_recrd[pYc][pXc][5]+abs(alys_recrd[pYc][pXc][4])+1;
    pn2 = pYc+alys_recrd[pYc][pXc][5]-abs(alys_recrd[pYc][pXc][4])-1;
    if (pm1>=0 && pn1<BOARD_CELL_NO && alys_recrd[pYc][pXc][4]==2*(1-2*isWhite) && alys_recrd[pn1][pm1][4]==2*(1-2*isWhite) && ps_recrd[pn1-1][pm1+1]==0 )
    {type_recrd[9]++;}
    pm1 = pXc-alys_recrd[pYc][pXc][5]+abs(alys_recrd[pYc][pXc][4])+2;
    pn1 = pYc+alys_recrd[pYc][pXc][5]-abs(alys_recrd[pYc][pXc][4])-2;
    pm2 = pXc-alys_recrd[pYc][pXc][5];
    pn2 = pYc+alys_recrd[pYc][pXc][5];
    if (pm1<BOARD_CELL_NO && pn1>=0 && alys_recrd[pYc][pXc][4]==2*(1-2*isWhite) && alys_recrd[pn1][pm1][4]==2*(1-2*isWhite) && ps_recrd[pn1+1][pm1-1]==0 )
    {type_recrd[9]++;}
    //TL-to-BR direction
    pm1 = pXc-alys_recrd[pYc][pXc][7]-1;
    pn1 = pYc-alys_recrd[pYc][pXc][7]-1;
    pm2 = pXc-alys_recrd[pYc][pXc][7]+abs(alys_recrd[pYc][pXc][6])+1;
    pn2 = pYc-alys_recrd[pYc][pXc][7]+abs(alys_recrd[pYc][pXc][6])+1;
    if (pm1>=0 && pn1>=0 && alys_recrd[pYc][pXc][6]==2*(1-2*isWhite) && alys_recrd[pn1][pm1][6]==2*(1-2*isWhite) && ps_recrd[pn1+1][pm1+1]==0 )
    {type_recrd[9]++;}
    pm1 = pXc-alys_recrd[pYc][pXc][7]+abs(alys_recrd[pYc][pXc][6])+2;
    pn1 = pYc-alys_recrd[pYc][pXc][7]+abs(alys_recrd[pYc][pXc][6])+2;
    pm2 = pXc-alys_recrd[pYc][pXc][7];
    pn2 = pYc-alys_recrd[pYc][pXc][7];
    if (pm1<BOARD_CELL_NO && pn1<BOARD_CELL_NO && alys_recrd[pYc][pXc][6]==2*(1-2*isWhite) && alys_recrd[pn1][pm1][6]==2*(1-2*isWhite) && ps_recrd[pn1-1][pm1-1]==0 )
    {type_recrd[9]++;}
    
    //3
    //"***"
    //type_recrd[8], type_recrd[7]
    //horizontal direction
    pm1 = pXc-alys_recrd[pYc][pXc][1]-1;
    pm2 = pXc-alys_recrd[pYc][pXc][1]+abs(alys_recrd[pYc][pXc][0])+2;
    pn1 = pn2 = pYc;
    if (abs(alys_recrd[pYc][pXc][0])==3 && pm1>=0 && pm2<BOARD_CELL_NO && (ps_recrd[pn1][pm1]+ps_recrd[pn1][pm1+1]+ps_recrd[pn2][pm2-1]+ps_recrd[pn2][pm2])==0)
    {type_recrd[8]++;}
    else if (abs(alys_recrd[pYc][pXc][0])==3 && 
        ((pm1>=0 && (ps_recrd[pn1][pm1]+ps_recrd[pn1][pm1+1])==0)||
        (pm2<BOARD_CELL_NO && (ps_recrd[pn2][pm2]+ps_recrd[pn2][pm2-1])==0)) )
    {type_recrd[7]++;}
    //verticle direction
    pn1 = pYc-alys_recrd[pYc][pXc][3]-1;
    pn2 = pYc-alys_recrd[pYc][pXc][3]+abs(alys_recrd[pYc][pXc][2])+2;
    pm1 = pm2 = pXc;
    if (abs(alys_recrd[pYc][pXc][2])==3 && pn1>=0 && pn2<BOARD_CELL_NO && (ps_recrd[pn1][pm1]+ps_recrd[pn1+1][pm1]+ps_recrd[pn2-1][pm2]+ps_recrd[pn2][pm2])==0)
    {type_recrd[8]++;}
    else if (abs(alys_recrd[pYc][pXc][2])==3 && 
        ((pn1>=0 && (ps_recrd[pn1][pm1]+ps_recrd[pn1+1][pm1])==0)||
        (pn2<BOARD_CELL_NO && (ps_recrd[pn2][pm2]+ps_recrd[pn2-1][pm2])==0)) )
    {type_recrd[7]++;}
    //BL-to-TR direction
    pm1 = pXc-alys_recrd[pYc][pXc][5]-1;
    pn1 = pYc+alys_recrd[pYc][pXc][5]+1;
    pm2 = pXc-alys_recrd[pYc][pXc][5]+abs(alys_recrd[pYc][pXc][4])+2;
    pn2 = pYc+alys_recrd[pYc][pXc][5]-abs(alys_recrd[pYc][pXc][4])-2;
    if (abs(alys_recrd[pYc][pXc][4])==3 && pm1>=0 && pn1<BOARD_CELL_NO && pm2<BOARD_CELL_NO && pn2>=0 && (ps_recrd[pn1][pm1]+ps_recrd[pn1-1][pm1+1]+ps_recrd[pn2+1][pm2-1]+ps_recrd[pn2][pm2])==0)
    {type_recrd[8]++;}
    else if (abs(alys_recrd[pYc][pXc][4])==3 && 
        ((pm1>=0 && pn1<BOARD_CELL_NO && (ps_recrd[pn1][pm1]+ps_recrd[pn1-1][pm1+1])==0)||
        (pm2<BOARD_CELL_NO && pn2>=0 && (ps_recrd[pn2][pm2]+ps_recrd[pn2+1][pm2-1])==0)) )
    {type_recrd[7]++;}
    //TL-to-BR direction
    pm1 = pXc-alys_recrd[pYc][pXc][7]-1;
    pn1 = pYc-alys_recrd[pYc][pXc][7]-1;
    pm2 = pXc-alys_recrd[pYc][pXc][7]+abs(alys_recrd[pYc][pXc][6])+2;
    pn2 = pYc-alys_recrd[pYc][pXc][7]+alys_recrd[pYc][pXc][7]+2;
    if (abs(alys_recrd[pYc][pXc][6])==3 && pm1>=0 && pn1>=0 && pm2<BOARD_CELL_NO && pn2<BOARD_CELL_NO && (ps_recrd[pn1][pm1]+ps_recrd[pn1+1][pm1+1]+ps_recrd[pn2-1][pm2-1]+ps_recrd[pn2][pm2])==0)
    {type_recrd[8]++;}
    else if (abs(alys_recrd[pYc][pXc][6])==3 && 
        ((pm1>=0 && pn1>=0 && (ps_recrd[pn1][pm1]+ps_recrd[pn1+1][pm1+1])==0)||
        (pm2<BOARD_CELL_NO && pn2<BOARD_CELL_NO && (ps_recrd[pn2][pm2]+ps_recrd[pn2-1][pm2-1])==0)) )
    {type_recrd[7]++;}
    
    //3
    //"** *"
    //type_recrd[6]
    // horizontal direction 
    pm1 = pXc-alys_recrd[pYc][pXc][1]-1;
    pm2 = pXc-alys_recrd[pYc][pXc][1]+abs(alys_recrd[pYc][pXc][0])+1;
    pn1 = pn2 = pYc;
    if (pm1>=0 && alys_recrd[pYc][pXc][0]*alys_recrd[pn1][pm1][0]==2 && ps_recrd[pn1][pm1+1]==0)
    {
        pm3 = pm1-alys_recrd[pn1][pm1][1];
        pn3 = pYc;
        if ((pm3>=0 && ps_recrd[pn3][pm3]==0)&&(pm2<BOARD_CELL_NO && ps_recrd[pn2][pm2]==0 ))
        {type_recrd[6]++;}
    }
    pm1 = pXc-alys_recrd[pYc][pXc][1]+abs(alys_recrd[pYc][pXc][0])+2;
    pm2 = pXc-alys_recrd[pYc][pXc][1];
    pn1 = pn2 = pYc;
    if (pm1<BOARD_CELL_NO && alys_recrd[pYc][pXc][0]*alys_recrd[pn1][pm1][0]==2 && ps_recrd[pn1][pm1-1]==0)
    {
        pm3 = pm1-alys_recrd[pn1][pm1][1]+abs(alys_recrd[pn1][pm1][0])+1;
        pn3 = pYc;
        if ((pm3<BOARD_CELL_NO && ps_recrd[pn3][pm3]==0) && (pm2>=0 && ps_recrd[pn2][pm2]==0 ))
        {type_recrd[6]++;}
    }
    // vertical direction 
    pn1 = pYc-alys_recrd[pYc][pXc][3]-1;
    pn2 = pYc-alys_recrd[pYc][pXc][3]+abs(alys_recrd[pYc][pXc][2])+1;
    pm1 = pm2 = pXc;
    if (pn1>=0 && alys_recrd[pYc][pXc][2]*alys_recrd[pn1][pm1][2]==2 && ps_recrd[pn1+1][pm1]==0)
    {
        pn3 = pn1-alys_recrd[pn1][pm1][3];
        pm3 = pXc;
        if ((pn3>=0 && ps_recrd[pn3][pm3]==0)&& (pn2<BOARD_CELL_NO && ps_recrd[pn2][pm2]==0 ))
        {type_recrd[6]++;}
    }
    pn1 = pYc-alys_recrd[pYc][pXc][3]+abs(alys_recrd[pYc][pXc][2])+2;
    pn2 = pYc-alys_recrd[pYc][pXc][3];
    pm1 = pm2 = pXc;
    if (pn1<BOARD_CELL_NO && alys_recrd[pYc][pXc][2]*alys_recrd[pn1][pm1][2]==2 && ps_recrd[pn1-1][pm1]==0)
    {
        pn3 = pn1-alys_recrd[pn1][pm1][3]+abs(alys_recrd[pn1][pm1][2])+1;
        pm3 = pXc;
        if ((pn3<BOARD_CELL_NO && ps_recrd[pn3][pm3]==0)&& (pn2>=0 && ps_recrd[pn2][pm2]==0 ))
        {type_recrd[6]++;}
    }
    //BL-to-TR direction
    pm1 = pXc-alys_recrd[pYc][pXc][5]-1;
    pn1 = pYc+alys_recrd[pYc][pXc][5]+1;
    pm2 = pXc-alys_recrd[pYc][pXc][5]+abs(alys_recrd[pYc][pXc][4])+1;
    pn2 = pYc+alys_recrd[pYc][pXc][5]-abs(alys_recrd[pYc][pXc][4])-1;
    if (pm1>=0 && pn1<BOARD_CELL_NO && alys_recrd[pYc][pXc][4]*alys_recrd[pn1][pm1][4]==2 && ps_recrd[pn1-1][pm1+1]==0 )
    {
        pm3 = pm1-alys_recrd[pn1][pm1][5];
        pn3 = pn1+alys_recrd[pn1][pm1][5];
        if ((pm3>=0 && pn3<BOARD_CELL_NO && ps_recrd[pn3][pm3]==0)&& (pm2<BOARD_CELL_NO && pn2>=0 && ps_recrd[pn2][pm2]==0 ))
        {type_recrd[6]++;}
    }
    pm1 = pXc-alys_recrd[pYc][pXc][5]+abs(alys_recrd[pYc][pXc][4])+2;
    pn1 = pYc+alys_recrd[pYc][pXc][5]-abs(alys_recrd[pYc][pXc][4])-2;
    pm2 = pXc-alys_recrd[pYc][pXc][5];
    pn2 = pYc+alys_recrd[pYc][pXc][5];
    if (pm1<BOARD_CELL_NO && pn1>=0 && alys_recrd[pYc][pXc][4]*alys_recrd[pn1][pm1][4]==2 && ps_recrd[pn1+1][pm1-1]==0 )
    {
        pm3 = pm1-alys_recrd[pn1][pm1][5]+abs(alys_recrd[pn1][pm1][4])+1;
        pn3 = pn1+alys_recrd[pn1][pm1][5]-abs(alys_recrd[pn1][pm1][4])-1;
        if ((pm3<BOARD_CELL_NO && pn3>=0 && ps_recrd[pn3][pm3]==0)&& (pm2>=0 && pn2<BOARD_CELL_NO && ps_recrd[pn2][pm2]==0 ))
        {type_recrd[6]++;}
    }
    //TL-to-BR direction
    pm1 = pXc-alys_recrd[pYc][pXc][7]-1;
    pn1 = pYc-alys_recrd[pYc][pXc][7]-1;
    pm2 = pXc-alys_recrd[pYc][pXc][7]+abs(alys_recrd[pYc][pXc][6])+1;
    pn2 = pYc-alys_recrd[pYc][pXc][7]+abs(alys_recrd[pYc][pXc][6])+1;
    if (pm1>=0 && pn1>=0 && alys_recrd[pYc][pXc][6]*alys_recrd[pn1][pm1][6]==2 && ps_recrd[pn1+1][pm1+1]==0 )
    {
        pm3 = pm1-alys_recrd[pn1][pm1][7];
        pn3 = pn1-alys_recrd[pn1][pm1][7];
        if ((pm3>=0 && pn3>=0 && ps_recrd[pn3][pm3]==0)&& (pm2<BOARD_CELL_NO && pn2<BOARD_CELL_NO && ps_recrd[pn2][pm2]==0 ))
        {type_recrd[6]++;}
    }
    pm1 = pXc-alys_recrd[pYc][pXc][7]+abs(alys_recrd[pYc][pXc][6])+2;
    pn1 = pYc-alys_recrd[pYc][pXc][7]+abs(alys_recrd[pYc][pXc][6])+2;
    pm2 = pXc-alys_recrd[pYc][pXc][7];
    pn2 = pYc-alys_recrd[pYc][pXc][7];
    if (pm1<BOARD_CELL_NO && pn1<BOARD_CELL_NO && alys_recrd[pYc][pXc][6]*alys_recrd[pn1][pm1][6]==2 && ps_recrd[pn1-1][pm1-1]==0 )
    {
        pm3 = pm1-alys_recrd[pn1][pm1][7]+abs(alys_recrd[pn1][pm1][6])+1;
        pn3 = pn1-alys_recrd[pn1][pm1][7]+abs(alys_recrd[pn1][pm1][6])+1;
        if ((pm3<BOARD_CELL_NO && pn3<BOARD_CELL_NO && ps_recrd[pn3][pm3]==0)&& (pm2>=0 && pn2>=0 && ps_recrd[pn2][pm2]==0 ))
        {type_recrd[6]++;}
    }
    //3
    //"** *"
    //type_recrd[5]
    // horizontal direction 
    pm1 = pXc-alys_recrd[pYc][pXc][1]-2;
    pn1 = pYc;
    if (pm1>=0 && alys_recrd[pYc][pXc][0]*alys_recrd[pn1][pm1][0]==2 && (ps_recrd[pn1][pm1+1]+ps_recrd[pn1][pm1+2])==0)
    {type_recrd[5]++;}
    pm1 = pXc-alys_recrd[pYc][pXc][1]+abs(alys_recrd[pYc][pXc][0])+3;
    pn1 = pYc;
    if (pm1<BOARD_CELL_NO && alys_recrd[pYc][pXc][0]*alys_recrd[pn1][pm1][0]==2 && (ps_recrd[pn1][pm1-1]+ps_recrd[pn1][pm1-2])==0)
    {type_recrd[5]++;}
    // vertical direction 
    pn1 = pYc-alys_recrd[pYc][pXc][3]-2;
    pm1 = pXc;
    if (pn1>=0 && alys_recrd[pYc][pXc][2]*alys_recrd[pn1][pm1][2]==2 && (ps_recrd[pn1+1][pm1]+ps_recrd[pn1+2][pm1])==0)
    {type_recrd[5]++;}
    pn1 = pYc-alys_recrd[pYc][pXc][3]+abs(alys_recrd[pYc][pXc][2])+3;
    pm1 = pXc;
    if (pn1<BOARD_CELL_NO && alys_recrd[pYc][pXc][2]*alys_recrd[pn1][pm1][2]==2 && (ps_recrd[pn1-1][pm1]+ps_recrd[pn1-2][pm1])==0)
    {type_recrd[5]++;}
    //BL-to-TR direction
    pm1 = pXc-alys_recrd[pYc][pXc][5]-2;
    pn1 = pYc+alys_recrd[pYc][pXc][5]+2;
    if (pm1>=0 && pn1<BOARD_CELL_NO && alys_recrd[pYc][pXc][4]*alys_recrd[pn1][pm1][4]==2 && (ps_recrd[pn1-1][pm1+1]+ps_recrd[pn1-2][pm1+2])==0 )
    {type_recrd[5]++;}
    pm1 = pXc-alys_recrd[pYc][pXc][5]+abs(alys_recrd[pYc][pXc][4])+3;
    pn1 = pYc+alys_recrd[pYc][pXc][5]-abs(alys_recrd[pYc][pXc][4])-3;
    if (pm1<BOARD_CELL_NO && pn1>=0 && alys_recrd[pYc][pXc][4]*alys_recrd[pn1][pm1][4]==2 && (ps_recrd[pn1+1][pm1-1]+ps_recrd[pn1+2][pm1-2])==0 )
    {type_recrd[5]++;}
    //TL-to-BR direction
    pm1 = pXc-alys_recrd[pYc][pXc][7]-2;
    pn1 = pYc-alys_recrd[pYc][pXc][7]-2;
    if (pm1>=0 && pn1>=0 && alys_recrd[pYc][pXc][6]*alys_recrd[pn1][pm1][6]==2 && (ps_recrd[pn1+1][pm1+1]+ps_recrd[pn1+2][pm1+2])==0 )
    {type_recrd[5]++;}
    pm1 = pXc-alys_recrd[pYc][pXc][7]+abs(alys_recrd[pYc][pXc][6])+3;
    pn1 = pYc-alys_recrd[pYc][pXc][7]+abs(alys_recrd[pYc][pXc][6])+3;
    if (pm1<BOARD_CELL_NO && pn1<BOARD_CELL_NO && alys_recrd[pYc][pXc][6]*alys_recrd[pn1][pm1][6]==2 && (ps_recrd[pn1-1][pm1-1]+ps_recrd[pn1-2][pm1-2])==0 )
    {type_recrd[6]++;}
    
    //3
    //"* * *"
    //type_recrd[4]
    // horizontal direction 
    pm1 = pXc-4;pm2 = pXc-2;pn1 = pn2 = pYc;
    if (pm1>=0 && alys_recrd[pYc][pXc][0]*alys_recrd[pn1][pm1][0]==1 && 
        pm2>=0 && alys_recrd[pYc][pXc][0]*alys_recrd[pn2][pm2][0]==1 &&
        (alys_recrd[pYc][pXc-1][0]+alys_recrd[pYc][pXc-3][0])==0 )
    {type_recrd[4]++;}
    // vertical direction 
    pn1 = pYc-4;pn2 = pYc-2;pm1 = pm2 = pXc;
    if (pn1>=0 && alys_recrd[pYc][pXc][2]*alys_recrd[pn1][pm1][2]==1 && 
        pn2>=0 && alys_recrd[pYc][pXc][2]*alys_recrd[pn2][pm2][2]==1 &&
        (alys_recrd[pYc-1][pXc][2]+alys_recrd[pYc-3][pXc][2])==0 )
    {type_recrd[4]++;}
    //BL-to-TR direction
    pm1 = pXc-4;pn1 = pYc+4;pm2 = pXc-2;pn2 = pYc+2;
    if (pm1>=0 && pn1<BOARD_CELL_NO && alys_recrd[pYc][pXc][4]*alys_recrd[pn1][pm1][4]==1 && 
        pm2>=0 && pn2<BOARD_CELL_NO  && alys_recrd[pYc][pXc][4]*alys_recrd[pn2][pm2][4]==1 &&
        (alys_recrd[pYc+3][pXc-3][4]+alys_recrd[pYc+1][pXc-1][4])==0 )
    {type_recrd[4]++;}
    //TL-to-BR direction
    pm1 = pXc-4;pn1 = pYc-4;pm2 = pXc-2;pn2 = pYc-2;
    if (pm1>=0 && pn1>=0 && alys_recrd[pYc][pXc][6]*alys_recrd[pn1][pm1][6]==1 && 
        pm2>=0 && pn2>=0 && alys_recrd[pYc][pXc][6]*alys_recrd[pn2][pm2][6]==1 &&
        (alys_recrd[pYc-1][pXc-1][6]+alys_recrd[pYc-3][pXc-3][6])==0 )
    {type_recrd[4]++;}
    // horizontal direction 
    pm1 = pXc-2;pm2 = pXc+2;pn1 = pn2 = pYc;
    if (pm1>=0 && alys_recrd[pYc][pXc][0]*alys_recrd[pn1][pm1][0]==1 && 
        pm2<BOARD_CELL_NO && alys_recrd[pYc][pXc][0]*alys_recrd[pn2][pm2][0]==1 &&
        (alys_recrd[pYc][pXc-1][0]+alys_recrd[pYc][pXc+1][0])==0 )
    {type_recrd[4]++;}
    // vertical direction 
    pn1 = pYc-2;pn2 = pYc+2;pm1 = pm2 = pXc;
    if (pn1>=0 && alys_recrd[pYc][pXc][2]*alys_recrd[pn1][pm1][2]==1 && 
        pn2<BOARD_CELL_NO && alys_recrd[pYc][pXc][2]*alys_recrd[pn2][pm2][2]==1 &&
        (alys_recrd[pYc-1][pXc][2]+alys_recrd[pYc+1][pXc][2])==0 )
    {type_recrd[4]++;}
    //BL-to-TR direction
    pm1 = pXc-2;pn1 = pYc+2;pm2 = pXc+2;pn2 = pYc-2;
    if (pm1>=0 && pn1<BOARD_CELL_NO && alys_recrd[pYc][pXc][4]*alys_recrd[pn1][pm1][4]==1 && 
        pm2<BOARD_CELL_NO && pn2>=0 && alys_recrd[pYc][pXc][4]*alys_recrd[pn2][pm2][4]==1 &&
        (alys_recrd[pYc+1][pXc-1][4]+alys_recrd[pYc-1][pXc+1][4])==0 )
    {type_recrd[4]++;}
    //TL-to-BR direction
    pm1 = pXc-2;pn1 = pYc-2;pm2 = pXc+2;pn2 = pYc+2;
    if (pm1>=0 && pn1>=0 && alys_recrd[pYc][pXc][6]*alys_recrd[pn1][pm1][6]==1 && 
        pm2<BOARD_CELL_NO && pn2<BOARD_CELL_NO && alys_recrd[pYc][pXc][6]*alys_recrd[pn2][pm2][6]==1 &&
        (alys_recrd[pYc-1][pXc-1][6]+alys_recrd[pYc+1][pXc+1][6])==0 )
    {type_recrd[4]++;}
    // horizontal direction 
    pm1 = pXc+4;pm2 = pXc+2;pn1 = pn2 = pYc;
    if (pm1<BOARD_CELL_NO && alys_recrd[pYc][pXc][0]*alys_recrd[pn1][pm1][0]==1 && 
        pm2<BOARD_CELL_NO && alys_recrd[pYc][pXc][0]*alys_recrd[pn2][pm2][0]==1 &&
        (alys_recrd[pYc][pXc+1][0]+alys_recrd[pYc][pXc+3][0])==0 )
    {type_recrd[4]++;}
    // vertical direction 
    pn1 = pYc+4;pn2 = pYc+2;pm1 = pm2 = pXc;
    if (pn1<BOARD_CELL_NO && alys_recrd[pYc][pXc][2]*alys_recrd[pn1][pm1][2]==1 && 
        pn2<BOARD_CELL_NO && alys_recrd[pYc][pXc][2]*alys_recrd[pn2][pm2][2]==1 &&
        (alys_recrd[pYc+1][pXc][2]+alys_recrd[pYc+3][pXc][2])==0 )
    {type_recrd[4]++;}
    //BL-to-TR direction
    pm1 = pXc+4;pn1 = pYc-4;pm2 = pXc+2;pn2 = pYc-2;
    if (pm1<BOARD_CELL_NO && pn1>=0 && alys_recrd[pYc][pXc][4]*alys_recrd[pn1][pm1][4]==1 && 
        pm2<BOARD_CELL_NO && pn2>=0 && alys_recrd[pYc][pXc][4]*alys_recrd[pn2][pm2][4]==1 &&
        (alys_recrd[pYc-1][pXc+1][4]+alys_recrd[pYc-3][pXc+3][4])==0 )
    {type_recrd[4]++;}
    //TL-to-BR direction
    pm1 = pXc+4;pn1 = pYc+4;pm2 = pXc+2;pn2 = pYc+2;
    if (pm1<BOARD_CELL_NO && pn1<BOARD_CELL_NO && alys_recrd[pYc][pXc][6]*alys_recrd[pn1][pm1][6]==1 && 
        pm2<BOARD_CELL_NO && pn2<BOARD_CELL_NO && alys_recrd[pYc][pXc][6]*alys_recrd[pn2][pm2][6]==1 &&
        (alys_recrd[pYc+1][pXc+1][6]+alys_recrd[pYc+3][pXc+3][6])==0 )
    {type_recrd[4]++;}
    
    //2
    //"**"
    //type_recrd[3], type_recrd[2]
    //horizontal direction
    pm1 = pXc-alys_recrd[pYc][pXc][1]-2;
    pm2 = pXc-alys_recrd[pYc][pXc][1]+abs(alys_recrd[pYc][pXc][0])+3;
    pn1 = pn2 = pYc;
    if (abs(alys_recrd[pYc][pXc][0])==2 && pm1>=0 && pm2<BOARD_CELL_NO && 
        (ps_recrd[pn1][pm1]+ps_recrd[pn1][pm1+1]+ps_recrd[pn1][pm1+2]+ps_recrd[pn2][pm2-2]+ps_recrd[pn2][pm2-1]+ps_recrd[pn2][pm2])==0)
    {type_recrd[3]++;}
    else if (abs(alys_recrd[pYc][pXc][0])==2 && 
        ((pm1>=0 && (ps_recrd[pn1][pm1]+ps_recrd[pn1][pm1+1]+ps_recrd[pn1][pm1+2])==0)||
        (pm2<BOARD_CELL_NO && (ps_recrd[pn2][pm2]+ps_recrd[pn2][pm2-1]+ps_recrd[pn2][pm2-2])==0)) )
    {type_recrd[2]++;}
    //verticle direction
    pn1 = pYc-alys_recrd[pYc][pXc][3]-2;
    pn2 = pYc-alys_recrd[pYc][pXc][3]+abs(alys_recrd[pYc][pXc][2])+3;
    pm1 = pm2 = pXc;
    if (abs(alys_recrd[pYc][pXc][2])==2 && pn1>=0 && pn2<BOARD_CELL_NO && 
        (ps_recrd[pn1][pm1]+ps_recrd[pn1+1][pm1]+ps_recrd[pn2-1][pm2]+ps_recrd[pn2][pm2])==0)
    {type_recrd[3]++;}
    else if (abs(alys_recrd[pYc][pXc][2])==2 && 
        ((pn1>=0 && (ps_recrd[pn1][pm1]+ps_recrd[pn1+1][pm1]+ps_recrd[pn1+2][pm1])==0)||
        (pn2<BOARD_CELL_NO && (ps_recrd[pn2][pm2]+ps_recrd[pn2-1][pm2]+ps_recrd[pn2-21][pm2])==0)) )
    {type_recrd[2]++;}
    //BL-to-TR direction
    pm1 = pXc-alys_recrd[pYc][pXc][5]-2;
    pn1 = pYc+alys_recrd[pYc][pXc][5]+2;
    pm2 = pXc-alys_recrd[pYc][pXc][5]+abs(alys_recrd[pYc][pXc][4])+3;
    pn2 = pYc+alys_recrd[pYc][pXc][5]-abs(alys_recrd[pYc][pXc][4])-3;
    if (abs(alys_recrd[pYc][pXc][4])==2 && pm1>=0 && pn1<BOARD_CELL_NO && pm2<BOARD_CELL_NO && pn2>=0 && 
        (ps_recrd[pn1][pm1]+ps_recrd[pn1-1][pm1+1]+ps_recrd[pn2+1][pm2-1]+ps_recrd[pn2][pm2])==0)
    {type_recrd[3]++;}
    else if (abs(alys_recrd[pYc][pXc][4])==2 && 
        ((pm1>=0 && pn1<BOARD_CELL_NO && (ps_recrd[pn1][pm1]+ps_recrd[pn1-1][pm1+1]+ps_recrd[pn1-2][pm1+2])==0)||
        (pm2<BOARD_CELL_NO && pn2>=0 && (ps_recrd[pn2][pm2]+ps_recrd[pn2+1][pm2-1]+ps_recrd[pn2+2][pm2-2])==0)) )
    {type_recrd[2]++;}
    //TL-to-BR direction
    pm1 = pXc-alys_recrd[pYc][pXc][7]-2;
    pn1 = pYc-alys_recrd[pYc][pXc][7]-2;
    pm2 = pXc-alys_recrd[pYc][pXc][7]+abs(alys_recrd[pYc][pXc][6])+3;
    pn2 = pYc-alys_recrd[pYc][pXc][7]+alys_recrd[pYc][pXc][7]+3;
    if (abs(alys_recrd[pYc][pXc][6])==2 && pm1>=0 && pn1>=0 && pm2<BOARD_CELL_NO && pn2<BOARD_CELL_NO && 
        (ps_recrd[pn1][pm1]+ps_recrd[pn1+1][pm1+1]+ps_recrd[pn2-1][pm2-1]+ps_recrd[pn2][pm2])==0)
    {type_recrd[3]++;}
    else if (abs(alys_recrd[pYc][pXc][6])==2 && 
        ((pm1>=0 && pn1>=0 && (ps_recrd[pn1][pm1]+ps_recrd[pn1+1][pm1+1]+ps_recrd[pn1+2][pm1+2])==0)||
        (pm2<BOARD_CELL_NO && pn2<BOARD_CELL_NO && (ps_recrd[pn2][pm2]+ps_recrd[pn2-1][pm2-1]+ps_recrd[pn2-2][pm2-2])==0)) )
    {type_recrd[2]++;}
    
    //2
    //"* *"
    //type_recrd[1]
    // horizontal direction 
    pm1 = pXc-4;pm2 = pXc+2;pn1 = pn2 = pYc;
    if (pm1>=0 && pm2<BOARD_CELL_NO &&
        alys_recrd[pYc][pXc][0]*alys_recrd[pYc][pXc-2][0]==1 && 
        (alys_recrd[pYc][pXc-4][0]+alys_recrd[pYc][pXc-3][0]+alys_recrd[pYc][pXc-1][0]+alys_recrd[pYc][pXc+1][0]+alys_recrd[pYc][pXc+2][0])==0 )
    {type_recrd[1]++;}
    // vertical direction 
    pn1 = pYc-4;pn2 = pYc+2;pm1 = pm2 = pXc;
    if (pn1>=0 && pn2<BOARD_CELL_NO &&
        alys_recrd[pYc][pXc][2]*alys_recrd[pYc-2][pXc][2]==1 && 
        (alys_recrd[pYc-4][pXc][2]+alys_recrd[pYc-3][pXc][2]+alys_recrd[pYc-1][pXc][2]+alys_recrd[pYc+1][pXc][2]+alys_recrd[pYc+2][pXc][2])==0 )
    {type_recrd[1]++;}
    //BL-to-TR direction
    pm1 = pXc-4;pn1 = pYc+4;pm2 = pXc+2;pn2 = pYc-2;
    if (pm1>=0 && pn1<BOARD_CELL_NO && pm2<BOARD_CELL_NO && pn2>=0 &&
        alys_recrd[pYc][pXc][4]*alys_recrd[pYc+2][pXc-2][4]==1 && 
        (alys_recrd[pYc+4][pXc-4][4]+alys_recrd[pYc+3][pXc-3][4]+alys_recrd[pYc+1][pXc-1][4]+alys_recrd[pYc-1][pXc+1][4]+alys_recrd[pYc-2][pXc+2][4])==0 )
    {type_recrd[1]++;}
    //TL-to-BR direction
    pm1 = pXc-4;pn1 = pYc-4;pm2 = pXc+2;pn2 = pYc+2;
    if (pm1>=0 && pn1>=0 && pm2<BOARD_CELL_NO && pn2<BOARD_CELL_NO &&
        alys_recrd[pYc][pXc][6]*alys_recrd[pYc-2][pXc-2][6]==1 && 
        (alys_recrd[pYc-4][pXc-4][6]+alys_recrd[pYc-3][pXc-3][6]+alys_recrd[pYc-1][pXc-1][6]+alys_recrd[pYc+1][pXc+1][6]+alys_recrd[pYc+2][pXc+2][6])==0 )
    {type_recrd[1]++;}
    // horizontal direction 
    pm1 = pXc+4;pm2 = pXc-2;pn1 = pn2 = pYc;
    if (pm2>=0 && pm1<BOARD_CELL_NO &&
        alys_recrd[pYc][pXc][0]*alys_recrd[pYc][pXc+2][0]==1 && 
        (alys_recrd[pYc][pXc+4][0]+alys_recrd[pYc][pXc+3][0]+alys_recrd[pYc][pXc+1][0]+alys_recrd[pYc][pXc-1][0]+alys_recrd[pYc][pXc-2][0])==0 )
    {type_recrd[1]++;}
    // vertical direction 
    pn1 = pYc+4;pn2 = pYc-2;pm1 = pm2 = pXc;
    if (pn2>=0 && pn1<BOARD_CELL_NO &&
        alys_recrd[pYc][pXc][2]*alys_recrd[pYc+2][pXc][2]==1 && 
        (alys_recrd[pYc+4][pXc][2]+alys_recrd[pYc+3][pXc][2]+alys_recrd[pYc+1][pXc][2]+alys_recrd[pYc-1][pXc][2]+alys_recrd[pYc-2][pXc][2])==0 )
    {type_recrd[1]++;}
    //BL-to-TR direction
    pm1 = pXc+4;pn1 = pYc-4;pm2 = pXc-2;pn2 = pYc+2;
    if (pm2>=0 && pn2<BOARD_CELL_NO && pm1<BOARD_CELL_NO && pn1>=0 &&
        alys_recrd[pYc][pXc][4]*alys_recrd[pYc-2][pXc+2][4]==1 && 
        (alys_recrd[pYc-4][pXc+4][4]+alys_recrd[pYc-3][pXc+3][4]+alys_recrd[pYc-1][pXc+1][4]+alys_recrd[pYc+1][pXc-1][4]+alys_recrd[pYc+2][pXc-2][4])==0 )
    {type_recrd[1]++;}
    //TL-to-BR direction
    pm1 = pXc+4;pn1 = pYc+4;pm2 = pXc-2;pn2 = pYc-2;
    if (pm2>=0 && pn2>=0 && pm1<BOARD_CELL_NO && pn1<BOARD_CELL_NO &&
        alys_recrd[pYc][pXc][6]*alys_recrd[pYc+2][pXc+2][6]==1 && 
        (alys_recrd[pYc+4][pXc+4][6]+alys_recrd[pYc+3][pXc+3][6]+alys_recrd[pYc+1][pXc+1][6]+alys_recrd[pYc-1][pXc-1][6]+alys_recrd[pYc-2][pXc-2][6])==0 )
    {type_recrd[1]++;}
    
    //2
    //"* *"
    //type_recrd[0]
    // horizontal direction 
    pm1 = pXc-4;pm2 = pXc+1;pn1 = pn2 = pYc;
    if (pm1>=0 && pm2<BOARD_CELL_NO &&
        alys_recrd[pYc][pXc][0]*alys_recrd[pYc][pXc-3][0]==1 && 
        (alys_recrd[pYc][pXc-4][0]+alys_recrd[pYc][pXc-2][0]+alys_recrd[pYc][pXc-1][0]+alys_recrd[pYc][pXc+1][0])==0 )
    {type_recrd[1]++;}
    // vertical direction 
    pn1 = pYc-4;pn2 = pYc+1;pm1 = pm2 = pXc;
    if (pn1>=0 && pn2<BOARD_CELL_NO &&
        alys_recrd[pYc][pXc][2]*alys_recrd[pYc-3][pXc][2]==1 && 
        (alys_recrd[pYc-4][pXc][2]+alys_recrd[pYc-2][pXc][2]+alys_recrd[pYc-1][pXc][2]+alys_recrd[pYc+1][pXc][2])==0 )
    {type_recrd[1]++;}
    //BL-to-TR direction
    pm1 = pXc-4;pn1 = pYc+1;pm2 = pXc+1;pn2 = pYc-1;
    if (pm1>=0 && pn1<BOARD_CELL_NO && pm2<BOARD_CELL_NO && pn2>=0 &&
        alys_recrd[pYc][pXc][4]*alys_recrd[pYc+3][pXc-3][4]==1 && 
        (alys_recrd[pYc+4][pXc-4][4]+alys_recrd[pYc+2][pXc-2][4]+alys_recrd[pYc+1][pXc-1][4]+alys_recrd[pYc-1][pXc+1][4])==0 )
    {type_recrd[1]++;}
    //TL-to-BR direction
    pm1 = pXc-4;pn1 = pYc-4;pm2 = pXc+1;pn2 = pYc+1;
    if (pm1>=0 && pn1>=0 && pm2<BOARD_CELL_NO && pn2<BOARD_CELL_NO &&
        alys_recrd[pYc][pXc][6]*alys_recrd[pYc-3][pXc-3][6]==1 && 
        (alys_recrd[pYc-4][pXc-4][6]+alys_recrd[pYc-2][pXc-2][6]+alys_recrd[pYc-1][pXc-1][6]+alys_recrd[pYc+1][pXc+1][6])==0 )
    {type_recrd[1]++;}
    // horizontal direction 
    pm1 = pXc+4;pm2 = pXc-1;pn1 = pn2 = pYc;
    if (pm2>=0 && pm1<BOARD_CELL_NO &&
        alys_recrd[pYc][pXc][0]*alys_recrd[pYc][pXc+3][0]==1 && 
        (alys_recrd[pYc][pXc+4][0]+alys_recrd[pYc][pXc+2][0]+alys_recrd[pYc][pXc+1][0]+alys_recrd[pYc][pXc-1][0])==0 )
    {type_recrd[1]++;}
    // vertical direction 
    pn1 = pYc+4;pn2 = pYc-1;pm1 = pm2 = pXc;
    if (pn2>=0 && pn1<BOARD_CELL_NO &&
        alys_recrd[pYc][pXc][2]*alys_recrd[pYc+3][pXc][2]==1 && 
        (alys_recrd[pYc+4][pXc][2]+alys_recrd[pYc+2][pXc][2]+alys_recrd[pYc+1][pXc][2]+alys_recrd[pYc-1][pXc][2])==0 )
    {type_recrd[1]++;}
    //BL-to-TR direction
    pm1 = pXc+4;pn1 = pYc-4;pm2 = pXc-1;pn2 = pYc+1;
    if (pm2>=0 && pn2<BOARD_CELL_NO && pm1<BOARD_CELL_NO && pn1>=0 &&
        alys_recrd[pYc][pXc][4]*alys_recrd[pYc-3][pXc+3][4]==1 && 
        (alys_recrd[pYc-4][pXc+4][4]+alys_recrd[pYc-2][pXc+2][4]+alys_recrd[pYc-1][pXc+1][4]+alys_recrd[pYc+1][pXc-1][4])==0 )
    {type_recrd[1]++;}
    //TL-to-BR direction
    pm1 = pXc+4;pn1 = pYc+4;pm2 = pXc-1;pn2 = pYc-1;
    if (pm2>=0 && pn2>=0 && pm1<BOARD_CELL_NO && pn1<BOARD_CELL_NO &&
        alys_recrd[pYc][pXc][6]*alys_recrd[pYc+3][pXc+3][6]==1 && 
        (alys_recrd[pYc+4][pXc+4][6]+alys_recrd[pYc+2][pXc+2][6]+alys_recrd[pYc+1][pXc+1][6]+alys_recrd[pYc-1][pXc-1][6])==0 )
    {type_recrd[1]++;}
    
//    for (i=0; i<14; ++i) {total_score += type_recrd[i]*type_weigh[i];}
    if (type_recrd[13]>=1)
        total_score = 100000;
    else if (type_recrd[12]>=1 ||(type_recrd[11]+type_recrd[10]+type_recrd[9])>=2 ||((type_recrd[11]+type_recrd[10]+type_recrd[9])>=1 && type_recrd[8]>=1))
        total_score = 10000;
    else if (type_recrd[8]>=2)
        total_score = 5000;
    else if (type_recrd[8]>=1 &&(type_recrd[7]+type_recrd[6]+type_recrd[5]+type_recrd[4])>=1)
        total_score = 1000;
    else if ((type_recrd[11]+type_recrd[10]+type_recrd[9])>=1)
        total_score = 500;
    else if (type_recrd[8]>=1)
        total_score = 200;
    else if (type_recrd[3]>=2)
        total_score = 100;
    else if ((type_recrd[7]+type_recrd[6]+type_recrd[5]+type_recrd[4])>=1)
        total_score = 50;
    else if ((type_recrd[2]+type_recrd[1]+type_recrd[0])>=2)
        total_score = 10;
    else if (type_recrd[3]>=1)
        total_score = 5;
    else if ((type_recrd[2]+type_recrd[1]+type_recrd[0])>=1)
        total_score = 3;
    return total_score;
}
//-------------------------------------------------------------------------
unsigned int gobang_place_piece(int pXc, int pYc)
{
//    int ii,jj;
    unsigned int isWhite = Ongame_Array[2];
    Piece_History[0][0]++;
    Piece_History[Piece_History[0][0]][0] = pXc;
    Piece_History[Piece_History[0][0]][1] = pYc;
    Piece_History[Piece_History[0][0]][2] = isWhite;
    
    AI_Region[0] = AI_Region[0]>=pXc ? (pXc>0?(pXc-1):0) : AI_Region[0];
    AI_Region[1] = AI_Region[1]<=pXc ? (pXc<(BOARD_CELL_NO-1)?(pXc+1):(BOARD_CELL_NO-1)) : AI_Region[1];
    AI_Region[2] = AI_Region[2]>=pYc ? (pYc>0?(pYc-1):0) : AI_Region[2];
    AI_Region[3] = AI_Region[3]<=pYc ? (pYc<(BOARD_CELL_NO-1)?(pYc+1):(BOARD_CELL_NO-1)) : AI_Region[3];
        
    gobang_draw_piece(pXc, pYc, isWhite);
//    if (isWhite == 1)
//    {
//        gobang_draw_circle(BOARD_PIECE_RADIUS, (pXc*BOARD_HOR_MARGIN+BOARD_LEFT_EDGE), (pYc*BOARD_VER_MARGIN+BOARD_TOP_EDGE));
//    }
//    else
//    {
//        gobang_draw_circle(BOARD_PIECE_RADIUS, (pXc*BOARD_HOR_MARGIN+BOARD_LEFT_EDGE), (pYc*BOARD_VER_MARGIN+BOARD_TOP_EDGE));
//        gobang_clear_circle(BOARD_PIECE_RADIUS*5/6, (pXc*BOARD_HOR_MARGIN+BOARD_LEFT_EDGE), (pYc*BOARD_VER_MARGIN+BOARD_TOP_EDGE));
//    }
    
    //Start update the piece on board
    Piece_Record[pYc][pXc] = 1-2*isWhite;
    
    unsigned int place_result = gobang_update_state(Piece_Analysis_Record,Piece_Record,pXc, pYc, isWhite);
    if (place_result!=2)    return place_result;
//    ///////////////////////////////////////////////////////////////////
//    //         Start update the state of Horzontal direction         //
//    //////////////////////////////////////////////////////////////////
//    int Series_Start_Point;
//    int Series_End_Point;
//    //left side
//    if (pXc>0 && Piece_Record[pYc][pXc]*Piece_Record[pYc][pXc-1] > 0)
//    {
//        Series_Start_Point = pXc - abs(Piece_Analysis_Record[pYc][pXc-1][0]);
//        Piece_Analysis_Record[pYc][pXc][0] = (1-2*isWhite) + Piece_Analysis_Record[pYc][pXc-1][0];  //how many, 1-black, -1-white
//        Piece_Analysis_Record[pYc][pXc][1] = 1 + Piece_Analysis_Record[pYc][pXc-1][1]; //第几个
//    }
//    else
//    {
//        Series_Start_Point = pXc;
//        Piece_Analysis_Record[pYc][pXc][0] = 1-2*isWhite;  //how many, 1-black, -1-white
//    }
//    //right side
//    if (pXc<BOARD_CELL_NO-1 && Piece_Record[pYc][pXc]*Piece_Record[pYc][pXc+1] > 0)
//    {
//        Series_End_Point = pXc + abs(Piece_Analysis_Record[pYc][pXc+1][0]);
//        Piece_Analysis_Record[pYc][pXc][0] += Piece_Analysis_Record[pYc][pXc+1][0];  //how many, 1-black, -1-white
//    }
//    else
//    {
//        Series_End_Point = pXc;
//    }
//    //decide if the player wins
//    if (abs(Piece_Analysis_Record[pYc][pXc][0]) == 5)
//    {
//        return isWhite;
//    }
//    if (abs(Piece_Analysis_Record[pYc][pXc][0])>5 && Instr_Array[2]==0)
//    {
//        return isWhite;
//    }
//    //update the horizontal state
//    for (ii = Series_Start_Point; ii <= Series_End_Point; ++ii)
//    {
//        Piece_Analysis_Record[pYc][ii][0] = Piece_Analysis_Record[pYc][pXc][0];
//        Piece_Analysis_Record[pYc][ii][1] = ii - Series_Start_Point + 1;
//    }
//    ///////////////////////////////////////////////////////////////////
//    //         Start update the state of Verticle direction          //
//    ///////////////////////////////////////////////////////////////////
//    //top side
//    if (pYc>0 && Piece_Record[pYc][pXc]*Piece_Record[pYc-1][pXc] > 0)
//    {
//        Series_Start_Point = pYc - abs(Piece_Analysis_Record[pYc-1][pXc][2]);
//        Piece_Analysis_Record[pYc][pXc][2] = (1-2*isWhite) + Piece_Analysis_Record[pYc-1][pXc][2];  //how many, 1-black, -1-white
//        Piece_Analysis_Record[pYc][pXc][3] = 1 + Piece_Analysis_Record[pYc-1][pXc][3]; //第几个
//    }
//    else
//    {
//        Series_Start_Point = pYc;
//        Piece_Analysis_Record[pYc][pXc][2] = 1-2*isWhite;  //how many, 1-black, -1-white
//    }
//    //bottom side
//    if (pYc<BOARD_CELL_NO-1 && Piece_Record[pYc][pXc]*Piece_Record[pYc+1][pXc] > 0)
//    {
//        Series_End_Point = pYc + abs(Piece_Analysis_Record[pYc+1][pXc][2]);
//        Piece_Analysis_Record[pYc][pXc][2] += Piece_Analysis_Record[pYc+1][pXc][2];  //how many, 1-black, -1-white
//    }
//    else
//    {
//        Series_End_Point = pYc;
//    }
//    //decide if the player wins
//    if (abs(Piece_Analysis_Record[pYc][pXc][2]) == 5)
//    {
//        return isWhite;
//    }
//    if (abs(Piece_Analysis_Record[pYc][pXc][2])>5 && Instr_Array[2]==0)
//    {
//        return isWhite;
//    }
//    //update the vertical state
//    for (jj = Series_Start_Point; jj <= Series_End_Point; ++jj)
//    {
//        Piece_Analysis_Record[jj][pXc][2] = Piece_Analysis_Record[pYc][pXc][2];
//        Piece_Analysis_Record[jj][pXc][3] = jj - Series_Start_Point + 1;
//    }
//    ///////////////////////////////////////////////////////////////////
//    //         Start update the state of BL-to-TR direction          //
//    ///////////////////////////////////////////////////////////////////
//    int Series_Start_Point2; //verticle start cordinate
//    int Series_Stend_Points; //number of point-series
//    //bottom-left side
//    if (pXc>0 && pYc<BOARD_CELL_NO-1 && Piece_Record[pYc][pXc]*Piece_Record[pYc+1][pXc-1] > 0)
//    {
//        Series_Start_Point = pXc - abs(Piece_Analysis_Record[pYc+1][pXc-1][4]);
//        Series_Start_Point2 = pYc + abs(Piece_Analysis_Record[pYc+1][pXc-1][4]);
//        Piece_Analysis_Record[pYc][pXc][4] = (1-2*isWhite) + Piece_Analysis_Record[pYc+1][pXc-1][4];  //how many, 1-black, -1-white
//        Piece_Analysis_Record[pYc][pXc][5] = 1 + Piece_Analysis_Record[pYc+1][pXc-1][5]; //第几个
//    }
//    else
//    {
//        Series_Start_Point = pXc;
//        Series_Start_Point2 = pYc;
//        Piece_Analysis_Record[pYc][pXc][4] = 1-2*isWhite;  //how many, 1-black, -1-white
//    }
//    //top-right side
//    if (pXc<BOARD_CELL_NO-1 && pYc>0 && Piece_Record[pYc][pXc]*Piece_Record[pYc-1][pXc+1] > 0)
//    {
//        Piece_Analysis_Record[pYc][pXc][4] += Piece_Analysis_Record[pYc-1][pXc+1][4];  //how many, 1-black, -1-white
//    }
//    Series_Stend_Points = abs(Piece_Analysis_Record[pYc][pXc][4]);
//    //decide if the player wins
//    if (Series_Stend_Points == 5)
//    {
//        return isWhite;
//    }
//    if (Series_Stend_Points>5 && Instr_Array[2]==0)
//    {
//        return isWhite;
//    }
//    //update the BL-to-TR state
//    for (ii = 0; ii < Series_Stend_Points; ++ii)
//    {
//        Piece_Analysis_Record[Series_Start_Point2-ii][Series_Start_Point+ii][4] = Piece_Analysis_Record[pYc][pXc][4];
//        Piece_Analysis_Record[Series_Start_Point2-ii][Series_Start_Point+ii][5] = ii + 1;
//    }
//    ///////////////////////////////////////////////////////////////////
//    //         Start update the state of TL-to-BR direction          //
//    ///////////////////////////////////////////////////////////////////
////    int Series_Start_Point2; //verticle start cordinate
////    int Series_Stend_Points; //number of point-series
//    //top-left side
//    if (pXc>0 && pYc>0 && Piece_Record[pYc][pXc]*Piece_Record[pYc-1][pXc-1] > 0)
//    {
//        Series_Start_Point = pXc - abs(Piece_Analysis_Record[pYc-1][pXc-1][6]);
//        Series_Start_Point2 = pYc - abs(Piece_Analysis_Record[pYc-1][pXc-1][6]);
//        Piece_Analysis_Record[pYc][pXc][6] = (1-2*isWhite) + Piece_Analysis_Record[pYc-1][pXc-1][6];  //how many, 1-black, -1-white
//        Piece_Analysis_Record[pYc][pXc][7] = 1 + Piece_Analysis_Record[pYc-1][pXc-1][7]; //第几个
//    }
//    else
//    {
//        Series_Start_Point = pXc;
//        Series_Start_Point2 = pYc;
//        Piece_Analysis_Record[pYc][pXc][6] = 1-2*isWhite;  //how many, 1-black, -1-white
//    }
//    //bottom-right side
//    if (pXc<BOARD_CELL_NO-1 && pYc<BOARD_CELL_NO-1 && Piece_Record[pYc][pXc]*Piece_Record[pYc+1][pXc+1] > 0)
//    {
//        Piece_Analysis_Record[pYc][pXc][6] += Piece_Analysis_Record[pYc+1][pXc+1][6];  //how many, 1-black, -1-white
//    }
//    Series_Stend_Points = abs(Piece_Analysis_Record[pYc][pXc][6]);
//    //decide if the player wins
//    if (Series_Stend_Points == 5)
//    {
//        return isWhite;
//    }
//    if (Series_Stend_Points>5 && Instr_Array[2]==0)
//    {
//        return isWhite;
//    }
//    //update the TL-to-BR state
//    for (ii = 0; ii < Series_Stend_Points; ++ii)
//    {
//        Piece_Analysis_Record[Series_Start_Point2+ii][Series_Start_Point+ii][6] = Piece_Analysis_Record[pYc][pXc][6];
//        Piece_Analysis_Record[Series_Start_Point2+ii][Series_Start_Point+ii][7] = ii + 1;
//    }
    
    ///////////////////////////////////////////////////////////////////
    //          Start check if the hand-cut problem exists           //
    /////////////////////////////////////////////////////////////////// 
    if (Instr_Array[2]==1 && Ongame_Array[5]==0)
    {
        if (gobang_handcut_check(Piece_Analysis_Record, isWhite, pXc, pYc))
        {
            return 1; //白方获胜
        }
    }
    
    Ongame_Array[2] = 1 - Ongame_Array[2];
    gobang_instrB_ondisplay();    //refresh instruction part
    return 2;
}
//-------------------------------------------------------------------------
unsigned int gobang_update_state(int alys_recrd[][BOARD_CELL_NO][8], int ps_recrd[][BOARD_CELL_NO], int pXc, int pYc, int isWhite)
{
    ///////////////////////////////////////////////////////////////////
    //         Start update the state of Horzontal direction         //
    //////////////////////////////////////////////////////////////////
    int ii, jj;
    int Series_Start_Point;
    int Series_End_Point;
    //left side
    if (pXc>0 && ps_recrd[pYc][pXc]*ps_recrd[pYc][pXc-1] > 0)
    {
        Series_Start_Point = pXc - abs(alys_recrd[pYc][pXc-1][0]);
        alys_recrd[pYc][pXc][0] = (1-2*isWhite) + alys_recrd[pYc][pXc-1][0];  //how many, 1-black, -1-white
        alys_recrd[pYc][pXc][1] = 1 + alys_recrd[pYc][pXc-1][1]; //第几个
    }
    else
    {
        Series_Start_Point = pXc;
        alys_recrd[pYc][pXc][0] = 1-2*isWhite;  //how many, 1-black, -1-white
    }
    //right side
    if (pXc<BOARD_CELL_NO-1 && ps_recrd[pYc][pXc]*ps_recrd[pYc][pXc+1] > 0)
    {
        Series_End_Point = pXc + abs(alys_recrd[pYc][pXc+1][0]);
        alys_recrd[pYc][pXc][0] += alys_recrd[pYc][pXc+1][0];  //how many, 1-black, -1-white
    }
    else
    {
        Series_End_Point = pXc;
    }
    //decide if the player wins
    if (abs(alys_recrd[pYc][pXc][0]) == 5)
    {
        return isWhite;
    }
    if (abs(alys_recrd[pYc][pXc][0])>5 && (Instr_Array[2]==0||isWhite==1))
    {
        return isWhite;
    }
    //update the horizontal state
    for (ii = Series_Start_Point; ii <= Series_End_Point; ++ii)
    {
        alys_recrd[pYc][ii][0] = alys_recrd[pYc][pXc][0];
        alys_recrd[pYc][ii][1] = ii - Series_Start_Point + 1;
    }
    ///////////////////////////////////////////////////////////////////
    //         Start update the state of Verticle direction          //
    ///////////////////////////////////////////////////////////////////
    //top side
    if (pYc>0 && ps_recrd[pYc][pXc]*ps_recrd[pYc-1][pXc] > 0)
    {
        Series_Start_Point = pYc - abs(alys_recrd[pYc-1][pXc][2]);
        alys_recrd[pYc][pXc][2] = (1-2*isWhite) + alys_recrd[pYc-1][pXc][2];  //how many, 1-black, -1-white
        alys_recrd[pYc][pXc][3] = 1 + alys_recrd[pYc-1][pXc][3]; //第几个
    }
    else
    {
        Series_Start_Point = pYc;
        alys_recrd[pYc][pXc][2] = 1-2*isWhite;  //how many, 1-black, -1-white
    }
    //bottom side
    if (pYc<BOARD_CELL_NO-1 && ps_recrd[pYc][pXc]*ps_recrd[pYc+1][pXc] > 0)
    {
        Series_End_Point = pYc + abs(alys_recrd[pYc+1][pXc][2]);
        alys_recrd[pYc][pXc][2] += alys_recrd[pYc+1][pXc][2];  //how many, 1-black, -1-white
    }
    else
    {
        Series_End_Point = pYc;
    }
    //decide if the player wins
    if (abs(alys_recrd[pYc][pXc][2]) == 5)
    {
        return isWhite;
    }
    if (abs(alys_recrd[pYc][pXc][2])>5 && Instr_Array[2]==0)
    {
        return isWhite;
    }
    //update the vertical state
    for (jj = Series_Start_Point; jj <= Series_End_Point; ++jj)
    {
        alys_recrd[jj][pXc][2] = alys_recrd[pYc][pXc][2];
        alys_recrd[jj][pXc][3] = jj - Series_Start_Point + 1;
    }
    ///////////////////////////////////////////////////////////////////
    //         Start update the state of BL-to-TR direction          //
    ///////////////////////////////////////////////////////////////////
    int Series_Start_Point2; //verticle start cordinate
    int Series_Stend_Points; //number of point-series
    //bottom-left side
    if (pXc>0 && pYc<BOARD_CELL_NO-1 && ps_recrd[pYc][pXc]*ps_recrd[pYc+1][pXc-1] > 0)
    {
        Series_Start_Point = pXc - abs(alys_recrd[pYc+1][pXc-1][4]);
        Series_Start_Point2 = pYc + abs(alys_recrd[pYc+1][pXc-1][4]);
        alys_recrd[pYc][pXc][4] = (1-2*isWhite) + alys_recrd[pYc+1][pXc-1][4];  //how many, 1-black, -1-white
        alys_recrd[pYc][pXc][5] = 1 + alys_recrd[pYc+1][pXc-1][5]; //第几个
    }
    else
    {
        Series_Start_Point = pXc;
        Series_Start_Point2 = pYc;
        alys_recrd[pYc][pXc][4] = 1-2*isWhite;  //how many, 1-black, -1-white
    }
    //top-right side
    if (pXc<BOARD_CELL_NO-1 && pYc>0 && ps_recrd[pYc][pXc]*ps_recrd[pYc-1][pXc+1] > 0)
    {
        alys_recrd[pYc][pXc][4] += alys_recrd[pYc-1][pXc+1][4];  //how many, 1-black, -1-white
    }
    Series_Stend_Points = abs(alys_recrd[pYc][pXc][4]);
    //decide if the player wins
    if (Series_Stend_Points == 5)
    {
        return isWhite;
    }
    if (Series_Stend_Points>5 && (Instr_Array[2]==0||isWhite==1))
    {
        return isWhite;
    }
    //update the BL-to-TR state
    for (ii = 0; ii < Series_Stend_Points; ++ii)
    {
        alys_recrd[Series_Start_Point2-ii][Series_Start_Point+ii][4] = alys_recrd[pYc][pXc][4];
        alys_recrd[Series_Start_Point2-ii][Series_Start_Point+ii][5] = ii + 1;
    }
    ///////////////////////////////////////////////////////////////////
    //         Start update the state of TL-to-BR direction          //
    ///////////////////////////////////////////////////////////////////
//    int Series_Start_Point2; //verticle start cordinate
//    int Series_Stend_Points; //number of point-series
    //top-left side
    if (pXc>0 && pYc>0 && ps_recrd[pYc][pXc]*ps_recrd[pYc-1][pXc-1] > 0)
    {
        Series_Start_Point = pXc - abs(alys_recrd[pYc-1][pXc-1][6]);
        Series_Start_Point2 = pYc - abs(alys_recrd[pYc-1][pXc-1][6]);
        alys_recrd[pYc][pXc][6] = (1-2*isWhite) + alys_recrd[pYc-1][pXc-1][6];  //how many, 1-black, -1-white
        alys_recrd[pYc][pXc][7] = 1 + alys_recrd[pYc-1][pXc-1][7]; //第几个
    }
    else
    {
        Series_Start_Point = pXc;
        Series_Start_Point2 = pYc;
        alys_recrd[pYc][pXc][6] = 1-2*isWhite;  //how many, 1-black, -1-white
    }
    //bottom-right side
    if (pXc<BOARD_CELL_NO-1 && pYc<BOARD_CELL_NO-1 && ps_recrd[pYc][pXc]*Piece_Record[pYc+1][pXc+1] > 0)
    {
        alys_recrd[pYc][pXc][6] += alys_recrd[pYc+1][pXc+1][6];  //how many, 1-black, -1-white
    }
    Series_Stend_Points = abs(alys_recrd[pYc][pXc][6]);
    //decide if the player wins
    if (Series_Stend_Points == 5)
    {
        return isWhite;
    }
    if (Series_Stend_Points>5 && (Instr_Array[2]==0||isWhite==1))
    {
        return isWhite;
    }
    //update the TL-to-BR state
    for (ii = 0; ii < Series_Stend_Points; ++ii)
    {
        alys_recrd[Series_Start_Point2+ii][Series_Start_Point+ii][6] = alys_recrd[pYc][pXc][6];
        alys_recrd[Series_Start_Point2+ii][Series_Start_Point+ii][7] = ii + 1;
    }
    
    ///////////////////////////////////////////////////////////////////
    //          Start check if the hand-cut problem exists           //
    /////////////////////////////////////////////////////////////////// 
    if (Instr_Array[2]==1 && Ongame_Array[5]==0)
    {
        if (gobang_handcut_check(alys_recrd, isWhite, pXc, pYc))
        {
            return 1; //白方获胜
        }
    }
    return 2;
}
//-------------------------------------------------------------------------
void gobang_proc_win(int winner)
{
    if (Ongame_Array[1]%2!=winner)  //先手获胜
        Ongame_Array[3]++;   //胜场加1
    else
        Ongame_Array[4]++;
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
        gobang_proc_ai(CPiece, Ongame_Array[2]);   //computer generate position of piece,
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
unsigned int gobang_handcut_check(int alys_recrd[][BOARD_CELL_NO][8], unsigned int isWhiteMode, int pXc, int pYc)
{
    if (isWhiteMode)    return 0;
    
    int pm1, pn1, pm2, pn2, pm3, pn3;
    //int qm1, qn1, qm2, qn2, qm3, qn3;
    pm1=0;pn1=0;pm2=0;pn2=0;pm3=0;pn3=0;
    //qm1=qn1=qm2=qn2=qm3=qn3=0;
    int hc_three = 0;   //hand_cut_three
    int hc_four = 0;
    int hc_six = 0;
    int hc_recrd[8][6];   //hand_cut_record[8][6], 8 Directions, 6 Kinds of Handcut
    int i, j;
    for (i=0; i<8; ++i)
        for (j=0; j<6; ++j)
            hc_recrd[i][j] = 0;
    ///////////////////////////////////////////////////////////////////
    //                     Start check hand-cut                      //
    ///////////////////////////////////////////////////////////////////
    //1-"***"
    // horizontal direction 
    pm1 = pXc-alys_recrd[pYc][pXc][1];
    pm2 = pXc-alys_recrd[pYc][pXc][1]+alys_recrd[pYc][pXc][0]+1;
    pn1 = pn2 = pYc;
    if (alys_recrd[pYc][pXc][0]==3 && pm1>=0 && Piece_Record[pn1][pm1]==0 && pm2<BOARD_CELL_NO && Piece_Record[pn2][pm2]==0 )
    {
        hc_recrd[0][0]++;
        hc_recrd[1][0] = -1;
        hc_three++;
    }
    //verticle direction
    pn1 = pYc-alys_recrd[pYc][pXc][3];
    pn2 = pYc-alys_recrd[pYc][pXc][3]+alys_recrd[pYc][pXc][2]+1;
    pm1 = pm2 = pXc;
    if (alys_recrd[pYc][pXc][2]==3 && pn1>=0 && Piece_Record[pn1][pm1]==0 && pn2<BOARD_CELL_NO && Piece_Record[pn2][pm2]==0 )
    {
        hc_recrd[2][0]++;
        hc_recrd[3][0] = -1;
        hc_three++;
    }
    //BL-to-TR direction
    pm1 = pXc-alys_recrd[pYc][pXc][5];
    pn1 = pYc+alys_recrd[pYc][pXc][5];
    pm2 = pXc-alys_recrd[pYc][pXc][5]+alys_recrd[pYc][pXc][4]+1;
    pn2 = pYc+alys_recrd[pYc][pXc][5]-alys_recrd[pYc][pXc][4]-1;
    if (alys_recrd[pYc][pXc][4]==3 && pm1>=0 && pn1<BOARD_CELL_NO && Piece_Record[pn1][pm1]==0 && pm2<BOARD_CELL_NO && pn2>=0 && Piece_Record[pn2][pm2]==0 )
    {
        hc_recrd[4][0]++;
        hc_recrd[5][0] = -1;
        hc_three++;
    }
    //TL-to-BR direction
    pm1 = pXc-alys_recrd[pYc][pXc][7];
    pn1 = pYc-alys_recrd[pYc][pXc][7];
    pm2 = pXc-alys_recrd[pYc][pXc][7]+alys_recrd[pYc][pXc][6]+1;
    pn2 = pYc-alys_recrd[pYc][pXc][7]+alys_recrd[pYc][pXc][7]+1;
    if (alys_recrd[pYc][pXc][6]==3 && pm1>=0 && pn1>=0 && Piece_Record[pn1][pm1]==0 && pm2<BOARD_CELL_NO && pn2<BOARD_CELL_NO && Piece_Record[pn2][pm2]==0 )
    {
        hc_recrd[6][0]++;
        hc_recrd[7][0] = -1;
        hc_three++;
    }

    //2-"** *"
    // horizontal direction 
    pm1 = pXc-alys_recrd[pYc][pXc][1]-1;
    pm2 = pXc-alys_recrd[pYc][pXc][1]+alys_recrd[pYc][pXc][0]+1;
    pn1 = pn2 = pYc;
    if (pm1>=0 && alys_recrd[pYc][pXc][0]*alys_recrd[pn1][pm1][0]==2 && pm2<BOARD_CELL_NO && Piece_Record[pn2][pm2]==0 && Piece_Record[pn1][pm1+1]==0)
    {
        pm3 = pm1-alys_recrd[pn1][pm1][1];
        pn3 = pYc;
        if (pm3>=0 && Piece_Record[pn3][pm3]==0)
        {
            hc_recrd[0][1]++;
            hc_three++;
        }
    }
    pm1 = pXc-alys_recrd[pYc][pXc][1]+alys_recrd[pYc][pXc][0]+2;
    pm2 = pXc-alys_recrd[pYc][pXc][1];
    pn1 = pn2 = pYc;
    if (pm1<BOARD_CELL_NO && alys_recrd[pYc][pXc][0]*alys_recrd[pn1][pm1][0]==2 && pm2>=0 && Piece_Record[pn2][pm2]==0 && Piece_Record[pn1][pm1-1]==0)
    {
        pm3 = pm1-alys_recrd[pn1][pm1][1]+alys_recrd[pn1][pm1][0]+1;
        pn3 = pYc;
        if (pm3<BOARD_CELL_NO && Piece_Record[pn3][pm3]==0)
        {
            hc_recrd[1][1]++;
            hc_three++;
        }
    }
    // vertical direction 
    pn1 = pYc-alys_recrd[pYc][pXc][3]-1;
    pn2 = pYc-alys_recrd[pYc][pXc][3]+alys_recrd[pYc][pXc][2]+1;
    pm1 = pm2 = pXc;
    if (pn1>=0 && alys_recrd[pYc][pXc][2]*alys_recrd[pn1][pm1][2]==2 && pn2<BOARD_CELL_NO && Piece_Record[pn2][pm2]==0 && Piece_Record[pn1+1][pm1]==0)
    {
        pn3 = pn1-alys_recrd[pn1][pm1][3];
        pm3 = pXc;
        if (pn3>=0 && Piece_Record[pn3][pm3]==0)
        {
            hc_recrd[2][1]++;
            hc_three++;
        }
    }
    pn1 = pYc-alys_recrd[pYc][pXc][3]+alys_recrd[pYc][pXc][2]+2;
    pn2 = pYc-alys_recrd[pYc][pXc][3];
    pm1 = pm2 = pXc;
    if (pn1<BOARD_CELL_NO && alys_recrd[pYc][pXc][2]*alys_recrd[pn1][pm1][2]==2 && pn2>=0 && Piece_Record[pn2][pm2]==0 && Piece_Record[pn1-1][pm1]==0)
    {
        pn3 = pn1-alys_recrd[pn1][pm1][3]+alys_recrd[pn1][pm1][2]+1;
        pm3 = pXc;
        if (pn3<BOARD_CELL_NO && Piece_Record[pn3][pm3]==0)
        {
            hc_recrd[3][1]++;
            hc_three++;
        }
    }
    //BL-to-TR direction
    pm1 = pXc-alys_recrd[pYc][pXc][5]-1;
    pn1 = pYc+alys_recrd[pYc][pXc][5]+1;
    pm2 = pXc-alys_recrd[pYc][pXc][5]+alys_recrd[pYc][pXc][4]+1;
    pn2 = pYc+alys_recrd[pYc][pXc][5]-alys_recrd[pYc][pXc][4]-1;
    if (pm1>=0 && pn1<BOARD_CELL_NO && alys_recrd[pYc][pXc][4]*alys_recrd[pn1][pm1][4]==2 && pm2<BOARD_CELL_NO && pn2>=0 && Piece_Record[pn2][pm2]==0 && Piece_Record[pn1-1][pm1+1]==0 )
    {
        pm3 = pm1-alys_recrd[pn1][pm1][5];
        pn3 = pn1+alys_recrd[pn1][pm1][5];
        if (pm3>=0 && pn3<BOARD_CELL_NO && Piece_Record[pn3][pm3]==0)
        {
            hc_recrd[4][1]++;
            hc_three++;
        }
    }
    pm1 = pXc-alys_recrd[pYc][pXc][5]+alys_recrd[pYc][pXc][4]+2;
    pn1 = pYc+alys_recrd[pYc][pXc][5]-alys_recrd[pYc][pXc][4]-2;
    pm2 = pXc-alys_recrd[pYc][pXc][5];
    pn2 = pYc+alys_recrd[pYc][pXc][5];
    if (pm1<BOARD_CELL_NO && pn1>=0 && alys_recrd[pYc][pXc][4]*alys_recrd[pn1][pm1][4]==2 && pm2>=0 && pn2<BOARD_CELL_NO && Piece_Record[pn2][pm2]==0 && Piece_Record[pn1+1][pm1-1]==0 )
    {
        pm3 = pm1-alys_recrd[pn1][pm1][5]+alys_recrd[pn1][pm1][4]+1;
        pn3 = pn1+alys_recrd[pn1][pm1][5]-alys_recrd[pn1][pm1][4]-1;
        if (pm3<BOARD_CELL_NO && pn3>=0 && Piece_Record[pn3][pm3]==0)
        {
            hc_recrd[5][1]++;
            hc_three++;
        }
    }
    //TL-to-BR direction
    pm1 = pXc-alys_recrd[pYc][pXc][7]-1;
    pn1 = pYc-alys_recrd[pYc][pXc][7]-1;
    pm2 = pXc-alys_recrd[pYc][pXc][7]+alys_recrd[pYc][pXc][6]+1;
    pn2 = pYc-alys_recrd[pYc][pXc][7]+alys_recrd[pYc][pXc][6]+1;
    if (pm1>=0 && pn1>=0 && alys_recrd[pYc][pXc][6]*alys_recrd[pn1][pm1][6]==2 && pm2<BOARD_CELL_NO && pn2<BOARD_CELL_NO && Piece_Record[pn2][pm2]==0 && Piece_Record[pn1+1][pm1+1]==0 )
    {
        pm3 = pm1-alys_recrd[pn1][pm1][7];
        pn3 = pn1-alys_recrd[pn1][pm1][7];
        if (pm3>=0 && pn3>=0 && Piece_Record[pn3][pm3]==0)
        {
            hc_recrd[6][1]++;
            hc_three++;
        }
    }
    pm1 = pXc-alys_recrd[pYc][pXc][7]+alys_recrd[pYc][pXc][6]+2;
    pn1 = pYc-alys_recrd[pYc][pXc][7]+alys_recrd[pYc][pXc][6]+2;
    pm2 = pXc-alys_recrd[pYc][pXc][7];
    pn2 = pYc-alys_recrd[pYc][pXc][7];
    if (pm1<BOARD_CELL_NO && pn1<BOARD_CELL_NO && alys_recrd[pYc][pXc][6]*alys_recrd[pn1][pm1][6]==2 && pm2>=0 && pn2>=0 && Piece_Record[pn2][pm2]==0 && Piece_Record[pn1-1][pm1-1]==0 )
    {
        pm3 = pm1-alys_recrd[pn1][pm1][7]+alys_recrd[pn1][pm1][6]+1;
        pn3 = pn1-alys_recrd[pn1][pm1][7]+alys_recrd[pn1][pm1][6]+1;
        if (pm3<BOARD_CELL_NO && pn3<BOARD_CELL_NO && Piece_Record[pn3][pm3]==0)
        {
            hc_recrd[7][1]++;
            hc_three++;
        }
    }

    //3-"****"
    //horizontal direction
    pm1 = pXc-alys_recrd[pYc][pXc][1];
    pm2 = pXc-alys_recrd[pYc][pXc][1]+alys_recrd[pYc][pXc][0]+1;
    pn1 = pn2 = pYc;
    if (alys_recrd[pYc][pXc][0]==4 && 
        ((pm1>=0 && pm2<BOARD_CELL_NO && Piece_Record[pn1][pm1]*Piece_Record[pn2][pm2]==0)||
        (pm1>=0 && pm2>=BOARD_CELL_NO && Piece_Record[pn1][pm1]==0)||
        (pm1<0 && pm2<BOARD_CELL_NO && Piece_Record[pn2][pm2]==0)) )
    {
        hc_recrd[0][2]++;
        hc_recrd[1][2] = -1;
        hc_four++;
    }
    //verticle direction
    pn1 = pYc-alys_recrd[pYc][pXc][3];
    pn2 = pYc-alys_recrd[pYc][pXc][3]+alys_recrd[pYc][pXc][2]+1;
    pm1 = pm2 = pXc;
    if (alys_recrd[pYc][pXc][2]==4 && 
        ((pn1>=0 && pn2<BOARD_CELL_NO && Piece_Record[pn1][pm1]*Piece_Record[pn2][pm2]==0)||
        (pn1>=0 && pn2>=BOARD_CELL_NO && Piece_Record[pn1][pm1]==0)||
        (pn1<0 && pn2<BOARD_CELL_NO && Piece_Record[pn2][pm2]==0)) )
    {
        hc_recrd[2][2]++;
        hc_recrd[3][2] = -1;
        hc_four++;
    }
    //BL-to-TR direction
    pm1 = pXc-alys_recrd[pYc][pXc][5];
    pn1 = pYc+alys_recrd[pYc][pXc][5];
    pm2 = pXc-alys_recrd[pYc][pXc][5]+alys_recrd[pYc][pXc][4]+1;
    pn2 = pYc+alys_recrd[pYc][pXc][5]-alys_recrd[pYc][pXc][4]-1;
    if (alys_recrd[pYc][pXc][4]==4 && 
        ((pm1>=0 && pn1<BOARD_CELL_NO && pm2<BOARD_CELL_NO && pn2>=0 && Piece_Record[pn1][pm1]*Piece_Record[pn2][pm2]==0)||
        (pm1>=0 && pn1<BOARD_CELL_NO && (pm2>=BOARD_CELL_NO || pn2<0) && Piece_Record[pn1][pm1]==0)||
        ((pm1<0 || pn1>=BOARD_CELL_NO) && pm2<BOARD_CELL_NO && pn2>=0 && Piece_Record[pn2][pm2]==0)) )
    {
        hc_recrd[4][2]++;
        hc_recrd[5][2] = -1;
        hc_four++;
    }
    //TL-to-BR direction
    pm1 = pXc-alys_recrd[pYc][pXc][7];
    pn1 = pYc-alys_recrd[pYc][pXc][7];
    pm2 = pXc-alys_recrd[pYc][pXc][7]+alys_recrd[pYc][pXc][6]+1;
    pn2 = pYc-alys_recrd[pYc][pXc][7]+alys_recrd[pYc][pXc][7]+1;
    if (alys_recrd[pYc][pXc][6]==4 && 
        ((pm1>=0 && pn1>=0 && pm2<BOARD_CELL_NO && pn2<BOARD_CELL_NO && Piece_Record[pn1][pm1]*Piece_Record[pn2][pm2]==0)||
        (pm1>=0 && pn1>=0 && (pm2>=BOARD_CELL_NO || pn2>=BOARD_CELL_NO) && Piece_Record[pn1][pm1])||
        ((pm1<0 || pn1<0) && pm2<BOARD_CELL_NO && pn2<BOARD_CELL_NO && Piece_Record[pn2][pm2]==0)) )
    {
        hc_recrd[6][2]++;
        hc_recrd[7][2] = -1;
        hc_four++;
    }

    //4-"*** *"
    //horizontal direction
    pm1 = pXc-alys_recrd[pYc][pXc][1]-1;
    pn1 = pYc;
    if (pm1>=0 && alys_recrd[pYc][pXc][0]*alys_recrd[pn1][pm1][0]==3 && Piece_Record[pn1][pm1+1]==0)
    {
        hc_recrd[0][3]++;
        hc_four++;
    }
    pm1 = pXc-alys_recrd[pYc][pXc][1]+alys_recrd[pYc][pXc][0]+2;
    pn1 = pYc;
    if (pm1<BOARD_CELL_NO && alys_recrd[pYc][pXc][0]*alys_recrd[pn1][pm1][0]==3 && Piece_Record[pn1][pm1-1]==0)
    {
        hc_recrd[1][3]++;
        hc_four++;
    }
    // vertical direction 
    pn1 = pYc-alys_recrd[pYc][pXc][3]-1;
    pm1 = pXc;
    if (pn1>=0 && alys_recrd[pYc][pXc][2]*alys_recrd[pn1][pm1][2]==3 && Piece_Record[pn1+1][pm1]==0)
    {
        hc_recrd[2][3]++;
        hc_four++;
    }
    pn1 = pYc-alys_recrd[pYc][pXc][3]+alys_recrd[pYc][pXc][2]+2;
    pm1 = pXc;
    if (pn1<BOARD_CELL_NO && alys_recrd[pYc][pXc][2]*alys_recrd[pn1][pm1][2]==3 && Piece_Record[pn1-1][pm1]==0)
    {
        hc_recrd[3][3]++;
        hc_four++;
    }
    //BL-to-TR direction
    pm1 = pXc-alys_recrd[pYc][pXc][5]-1;
    pn1 = pYc+alys_recrd[pYc][pXc][5]+1;
    if (pm1>=0 && pn1<BOARD_CELL_NO && alys_recrd[pYc][pXc][4]*alys_recrd[pn1][pm1][4]==3 && Piece_Record[pn1-1][pm1+1]==0 )
    {
        hc_recrd[4][3]++;
        hc_four++;
    }
    pm1 = pXc-alys_recrd[pYc][pXc][5]+alys_recrd[pYc][pXc][4]+2;
    pn1 = pYc+alys_recrd[pYc][pXc][5]-alys_recrd[pYc][pXc][4]-2;
    if (pm1<BOARD_CELL_NO && pn1>=0 && alys_recrd[pYc][pXc][4]*alys_recrd[pn1][pm1][4]==3 && Piece_Record[pn1+1][pm1-1]==0 )
    {
        hc_recrd[5][3]++;
        hc_four++;
    }
    //TL-to-BR direction
    pm1 = pXc-alys_recrd[pYc][pXc][7]-1;
    pn1 = pYc-alys_recrd[pYc][pXc][7]-1;
    if (pm1>=0 && pn1>=0 && alys_recrd[pYc][pXc][6]*alys_recrd[pn1][pm1][6]==3 && Piece_Record[pn1+1][pm1+1]==0 )
    {
        hc_recrd[6][3]++;
        hc_four++;
    }
    pm1 = pXc-alys_recrd[pYc][pXc][7]+alys_recrd[pYc][pXc][6]+2;
    pn1 = pYc-alys_recrd[pYc][pXc][7]+alys_recrd[pYc][pXc][6]+2;
    if (pm1<BOARD_CELL_NO && pn1<BOARD_CELL_NO && alys_recrd[pYc][pXc][6]*alys_recrd[pn1][pm1][6]==3 && Piece_Record[pn1-1][pm1-1]==0 )
    {
        hc_recrd[7][3]++;
        hc_four++;
    }


    //5-"** **"
    pm1 = pXc-alys_recrd[pYc][pXc][1]-1;
    pn1 = pYc;
    if (pm1>=0 && alys_recrd[pYc][pXc][0]==2 && alys_recrd[pn1][pm1][0]==2 && Piece_Record[pn1][pm1+1]==0)
    {
        hc_recrd[0][4]++;
        hc_four++;
    }
    pm1 = pXc-alys_recrd[pYc][pXc][1]+alys_recrd[pYc][pXc][0]+2;
    pn1 = pYc;
    if (pm1<BOARD_CELL_NO && alys_recrd[pYc][pXc][0]==2 && alys_recrd[pn1][pm1][0]==2 && Piece_Record[pn1][pm1-1]==0)
    {
        hc_recrd[1][4]++;
        hc_four++;
    }
    // vertical direction 
    pn1 = pYc-alys_recrd[pYc][pXc][3]-1;
    pm1 = pXc;
    if (pn1>=0 && alys_recrd[pYc][pXc][2]==2 && alys_recrd[pn1][pm1][2]==2 && Piece_Record[pn1+1][pm1]==0)
    {
        hc_recrd[2][4]++;
        hc_four++;
    }
    pn1 = pYc-alys_recrd[pYc][pXc][3]+alys_recrd[pYc][pXc][2]+2;
    pm1 = pXc;
    if (pn1<BOARD_CELL_NO && alys_recrd[pYc][pXc][2]==2 && alys_recrd[pn1][pm1][2]==2 && Piece_Record[pn1-1][pm1]==0)
    {
        hc_recrd[3][4]++;
        hc_four++;
    }
    //BL-to-TR direction
    pm1 = pXc-alys_recrd[pYc][pXc][5]-1;
    pn1 = pYc+alys_recrd[pYc][pXc][5]+1;
    if (pm1>=0 && pn1<BOARD_CELL_NO && alys_recrd[pYc][pXc][4]==2 && alys_recrd[pn1][pm1][4]==2 && Piece_Record[pn1-1][pm1+1]==0 )
    {
        hc_recrd[4][4]++;
        hc_four++;
    }
    pm1 = pXc-alys_recrd[pYc][pXc][5]+alys_recrd[pYc][pXc][4]+2;
    pn1 = pYc+alys_recrd[pYc][pXc][5]-alys_recrd[pYc][pXc][4]-2;
    if (pm1<BOARD_CELL_NO && pn1>=0 && alys_recrd[pYc][pXc][4]==2 && alys_recrd[pn1][pm1][4]==2 && Piece_Record[pn1+1][pm1-1]==0 )
    {
        hc_recrd[5][4]++;
        hc_four++;
    }
    //TL-to-BR direction
    pm1 = pXc-alys_recrd[pYc][pXc][7]-1;
    pn1 = pYc-alys_recrd[pYc][pXc][7]-1;
    if (pm1>=0 && pn1>=0 && alys_recrd[pYc][pXc][6]==2 && alys_recrd[pn1][pm1][6]==2 && Piece_Record[pn1+1][pm1+1]==0 )
    {
        hc_recrd[6][4]++;
        hc_four++;
    }
    pm1 = pXc-alys_recrd[pYc][pXc][7]+alys_recrd[pYc][pXc][6]+2;
    pn1 = pYc-alys_recrd[pYc][pXc][7]+alys_recrd[pYc][pXc][6]+2;
    if (pm1<BOARD_CELL_NO && pn1<BOARD_CELL_NO && alys_recrd[pYc][pXc][6]==2 && alys_recrd[pn1][pm1][6]==2 && Piece_Record[pn1-1][pm1-1]==0 )
    {
        hc_recrd[7][4]++;
        hc_four++;
    }
    //6-"***...***"
    //horizontal direction
    if (alys_recrd[pYc][pXc][0] > 5)
    {
        hc_recrd[0][5]++;
        hc_recrd[1][5] = -1;
        hc_six++;
    }
    // vertical direction
    if (alys_recrd[pYc][pXc][2] > 5)
    {
        hc_recrd[2][5]++;
        hc_recrd[3][5] = -1;
        hc_six++;
    }
    //BL-to-TR direction
    if (alys_recrd[pYc][pXc][4] > 5)
    {
        hc_recrd[4][5]++;
        hc_recrd[5][5] = -1;
        hc_six++;
    }
    //TL-to-BR direction
    if (alys_recrd[pYc][pXc][6] > 5)
    {
        hc_recrd[6][5]++;
        hc_recrd[7][5] = -1;
        hc_six++;
    }
        
    if (hc_three >= 2 || hc_four >= 2 || hc_six >= 1)
    { 
//        gobang_draw_circle(BOARD_PIECE_RADIUS/2, (pXc*BOARD_HOR_MARGIN+BOARD_LEFT_EDGE), (pYc*BOARD_VER_MARGIN+BOARD_TOP_EDGE));
//        
//        Instr_Array[0] = 0;
//        int IBDebug_Left, IBDebug_Top;
//        IBDebug_Left=480; IBDebug_Top=170;
//        gobang_box_fill(120, 275, IBDebug_Left, IBDebug_Top);       
//        gobang_show_text("调试结果：", IBDebug_Left, IBDebug_Top);
//        gobang_show_text("pXc=", IBDebug_Left, IBDebug_Top+25); gobang_show_num((pXc+1), IBDebug_Left+40, IBDebug_Top+25);
//        gobang_show_text("pYc=", IBDebug_Left+60, IBDebug_Top+25); gobang_show_num((pYc+1), IBDebug_Left+100, IBDebug_Top+25);
//        
//        gobang_show_text("alys_recrd:", IBDebug_Left, IBDebug_Top+45);
////        int i, j;
//        for (i=0; i<4; ++i)
//        {
//            gobang_show_num(alys_recrd[pYc][pXc][2*i], (IBDebug_Left+20*i), IBDebug_Top+65);
//            gobang_show_num(alys_recrd[pYc][pXc][2*i+1], (IBDebug_Left+20*i), IBDebug_Top+85);
//        }
//        gobang_show_text("***************", IBDebug_Left, IBDebug_Top+105);
//        for (i=0; i<8; ++i)
//            for (j=0; j<6; ++j)
//            {
//                gobang_show_num(hc_recrd[i][j], (IBDebug_Left+20*j), (IBDebug_Top+125+16*i));
//            }
//        
////        gobang_show_text("3连=", 480, 290); gobang_show_num(hc_three, 540, 290);
////        gobang_show_text("4连=", 480, 310); gobang_show_num(hc_four, 540, 310);
////        gobang_show_text("6连=", 480, 330); gobang_show_num(hc_six, 540, 330);
        
        return 1;
    }
    
    return 0;
}