
#include "system.h"
#include "basic_io.h"
#include "LCD.h"
#include "Test.h"
#include "sys/alt_irq.h"
#include "VGA.h"
#include "GoBang.h"
#include <math.h>

//int Piece_Record[BOARD_CELL_NO][BOARD_CELL_NO]={0};

int maxmin(int no, int max, int min)
{
 if(no>max) {no=max;}
 if(no<min) {no=min;}

 return(no);
}

void play_mouse(unsigned int addr)
{
 unsigned int cbuf[128];
 unsigned int rbuf[128];

 //buffer information
 unsigned int atllen,ptllen,intllen;
 unsigned int int_start;

 //int parameters
 unsigned long int_skip=0xFFFFFFFE;
 unsigned long int_last=0x00000001;
 unsigned int  int_blk_size=64;

 unsigned int timecnt;
 unsigned int freq;

 signed char X=0,Y=0,B=0;

 unsigned int pX=320,pY=240;
 unsigned int oX=320,oY=240;

 unsigned int tog=0;
 
 unsigned int is_white_mode = 0; //Black Piece(1=1-2*is_white_mode) as default
 unsigned int rclick_no = 0;    //no. of right click; Reset when left click
 unsigned int win_state = 0;    //change to 1 when player wins a game, so that no more pieces are allowed
 unsigned int hand_cut_three = 0;   //record number of hand cut of three when is_white_mode==0(Black)
 unsigned int hand_cut_four = 0;    //record number of hand cut of four when is_white_mode==0(Black)
 unsigned int hand_cut_six = 0;     //record number of hand cut of more than five when is_white_mode==0(Black)
 
 freq=0x00;
 erase_all();

 w16(HcBufStatus,0x00);

 //Setup Int Parameters
 w32(HcIntSkip,int_skip);
 w32(HcIntLast,int_last);
 w16(HcIntBlkSize,int_blk_size);

 //Setup Buffer
 atllen  =r16(HcATLLen);
 ptllen  =r16(HcPTLLen);
 intllen =r16(HcINTLen);

 int_start=ptllen+ptllen;

 do
  {
   //send out DATA IN packet
   make_int_ptd(cbuf,IN,1,4,tog%2,addr,addr,freq);
   timecnt=send_int(cbuf,rbuf);
   if(timecnt!=0)
   {
	   X=(rbuf[4]>>8);
	   Y=(rbuf[5]&0x00FF);
	   B=(rbuf[4]&0x000F);
   }
   else
   {
	   X=0;
	   Y=0;
	   B=0;
   }

   oX=pX;
   oY=pY;

   pX=pX+X;
   pY=pY+Y;

   pX=maxmin(pX,639,0);
   pY=maxmin(pY,479,0);

   if(timecnt!=0) {tog++;}

  IOWR(SEG7_DISPLAY_BASE,0,(pX<<16)+pY);
  IOWR(LED_RED_BASE,0,pX);
  IOWR(LED_GREEN_BASE,0,pY);
  
    Set_Cursor_XY(pX,pY);

    //pX-X coordinate of the cursor of mouse
    //pY-Y coordinate of the cursor of mouse
    int ii,jj;
    int pXc, pYc, pXcc, pYcc;
    pXc = (pX-BOARD_LEFT_EDGE) / BOARD_HOR_MARGIN;    
    pXcc = (pX-BOARD_LEFT_EDGE) % BOARD_HOR_MARGIN;
    pYc = (pY-BOARD_TOP_EDGE) / BOARD_VER_MARGIN;
    pYcc = (pY-BOARD_TOP_EDGE) % BOARD_VER_MARGIN;
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
    if (pX<BOARD_LEFT_EDGE && BOARD_LEFT_EDGE-pX<BOARD_PIECE_OFFSET)
    {
        pXc = 0;
        pXcc = BOARD_LEFT_EDGE-pX;
    }
    if (pY<BOARD_TOP_EDGE && BOARD_TOP_EDGE-pY<BOARD_PIECE_OFFSET)
    {
        pYc = 0;
        pYcc = BOARD_TOP_EDGE-pY;
    }
    
  /*if(B==1)
  Vga_Set_Pixel(VGA_0_BASE,pX,pY);*/
  if(B==1){
    rclick_no = 0;  //Reset NO of right-click
    hand_cut_three = 0;
    hand_cut_four = 0;
    hand_cut_six = 0;
    
    if (win_state == 1) continue;   //in win-state, no more pieces are allowed
    if ((pXcc*pXcc+pYcc*pYcc)>BOARD_PIECE_OFFSET*BOARD_PIECE_OFFSET)    continue;
    if (pXc < 0 || pYc < 0 || pXc >= BOARD_CELL_NO || pYc >= BOARD_CELL_NO) continue;
    if (Piece_Record[pYc][pXc] != 0)  continue;
    
    if (is_white_mode == 1)
    {
        for (ii=-BOARD_PIECE_RADIUS; ii<(BOARD_PIECE_RADIUS+1); ++ii)
        {
            for (jj=-BOARD_PIECE_RADIUS; jj<(BOARD_PIECE_RADIUS+1); ++jj)
            {   
                if ((ii*ii+jj*jj)>(BOARD_PIECE_RADIUS*BOARD_PIECE_RADIUS+1))    continue;
                Vga_Set_Pixel(VGA_0_BASE, (pXc*BOARD_HOR_MARGIN+BOARD_LEFT_EDGE+ii), (pYc*BOARD_VER_MARGIN+BOARD_TOP_EDGE+jj));
            }
        }
//        is_white_mode = 0;   //Set back to Black Piece
    }
    else
    {
        for (ii=-BOARD_PIECE_RADIUS; ii<(BOARD_PIECE_RADIUS+1); ++ii)
        {
            for (jj=-BOARD_PIECE_RADIUS; jj<(BOARD_PIECE_RADIUS+1); ++jj)
            {   
                if((ii*ii+jj*jj)>(BOARD_PIECE_RADIUS*BOARD_PIECE_RADIUS+1))    continue;
                if((ii*ii+jj*jj)>(BOARD_PIECE_RADIUS*BOARD_PIECE_RADIUS*25/36+1))
                    Vga_Set_Pixel(VGA_0_BASE,(pXc*BOARD_HOR_MARGIN+BOARD_LEFT_EDGE+ii),(pYc*BOARD_VER_MARGIN+BOARD_TOP_EDGE+jj));
                else
                    Vga_Clr_Pixel(VGA_0_BASE,(pXc*BOARD_HOR_MARGIN+BOARD_LEFT_EDGE+ii),(pYc*BOARD_VER_MARGIN+BOARD_TOP_EDGE+jj));
            }
        }
//        is_white_mode = 1;   //Set back to White Piece
    }
    
    //Start update the piece on board
    Piece_Record[pYc][pXc] = 1-2*is_white_mode;
    
    ///////////////////////////////////////////////////////////////////
    //         Start update the state of Horzontal direction         //
    //////////////////////////////////////////////////////////////////
    int Series_Start_Point;
    int Series_End_Point;
    //left side
    if (pXc>0 && Piece_Record[pYc][pXc]*Piece_Record[pYc][pXc-1] > 0)
    {
        Series_Start_Point = pXc - abs(Piece_Analysis_Record[pYc][pXc-1][0]);
        Piece_Analysis_Record[pYc][pXc][0] = (1-2*is_white_mode) + Piece_Analysis_Record[pYc][pXc-1][0];  //how many, 1-black, -1-white
        Piece_Analysis_Record[pYc][pXc][1] = 1 + Piece_Analysis_Record[pYc][pXc-1][1]; //第几个
    }
    else
    {
        Series_Start_Point = pXc;
        Piece_Analysis_Record[pYc][pXc][0] = 1-2*is_white_mode;  //how many, 1-black, -1-white
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
        win_state = 1;
        gobang_win_display(is_white_mode);
        continue;
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
//    int Series_Start_Point;
//    int Series_End_Point;
    //top side
    if (pYc>0 && Piece_Record[pYc][pXc]*Piece_Record[pYc-1][pXc] > 0)
    {
        Series_Start_Point = pYc - abs(Piece_Analysis_Record[pYc-1][pXc][2]);
        Piece_Analysis_Record[pYc][pXc][2] = (1-2*is_white_mode) + Piece_Analysis_Record[pYc-1][pXc][2];  //how many, 1-black, -1-white
        Piece_Analysis_Record[pYc][pXc][3] = 1 + Piece_Analysis_Record[pYc-1][pXc][3]; //第几个
    }
    else
    {
        Series_Start_Point = pYc;
        Piece_Analysis_Record[pYc][pXc][2] = 1-2*is_white_mode;  //how many, 1-black, -1-white
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
        win_state = 1;
        gobang_win_display(is_white_mode);
        continue;
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
        Piece_Analysis_Record[pYc][pXc][4] = (1-2*is_white_mode) + Piece_Analysis_Record[pYc+1][pXc-1][4];  //how many, 1-black, -1-white
        Piece_Analysis_Record[pYc][pXc][5] = 1 + Piece_Analysis_Record[pYc+1][pXc-1][5]; //第几个
    }
    else
    {
        Series_Start_Point = pXc;
        Series_Start_Point2 = pYc;
        Piece_Analysis_Record[pYc][pXc][4] = 1-2*is_white_mode;  //how many, 1-black, -1-white
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
        win_state = 1;
        gobang_win_display(is_white_mode);
        continue;
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
        Piece_Analysis_Record[pYc][pXc][6] = (1-2*is_white_mode) + Piece_Analysis_Record[pYc-1][pXc-1][6];  //how many, 1-black, -1-white
        Piece_Analysis_Record[pYc][pXc][7] = 1 + Piece_Analysis_Record[pYc-1][pXc-1][7]; //第几个
    }
    else
    {
        Series_Start_Point = pXc;
        Series_Start_Point2 = pYc;
        Piece_Analysis_Record[pYc][pXc][6] = 1-2*is_white_mode;  //how many, 1-black, -1-white
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
        win_state = 1;
        gobang_win_display(is_white_mode);
        continue;
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
    if (is_white_mode == 0)
    {
        int piece_next = 0;
        int piece_next2 = 0;    //for the other cordinate of lean direction
        ///////////////////////////////////////////////////////////////////
        //         Start check hand-cut of horizontal direction          //
        ///////////////////////////////////////////////////////////////////
        //1-"***"
        if (Piece_Analysis_Record[pYc][pXc][0] == 3)
            hand_cut_three++;
        //2-"** *"
        piece_next = pXc - Piece_Analysis_Record[pYc][pXc][1] - 1;
        if (piece_next>=0 && Piece_Analysis_Record[pYc][pXc][0]*Piece_Analysis_Record[pYc][piece_next][0] == 2 )
            hand_cut_three++;
        piece_next = pXc + Piece_Analysis_Record[pYc][pXc][0] - Piece_Analysis_Record[pYc][pXc][1] + 2;
        if (piece_next<BOARD_CELL_NO && Piece_Analysis_Record[pYc][pXc][0]*Piece_Analysis_Record[pYc][piece_next][0] == 2 )
            hand_cut_three++;
        //3-"****"
        if (Piece_Analysis_Record[pYc][pXc][0] == 4)
            hand_cut_four++;
        //4-"*** *"
        piece_next = pXc - Piece_Analysis_Record[pYc][pXc][1] - 1;
        if (piece_next>=0 && Piece_Analysis_Record[pYc][pXc][0]*Piece_Analysis_Record[pYc][piece_next][0] == 3 )
            hand_cut_four++;
        piece_next = pXc + Piece_Analysis_Record[pYc][pXc][0] - Piece_Analysis_Record[pYc][pXc][1] + 2;
        if (piece_next<BOARD_CELL_NO && Piece_Analysis_Record[pYc][pXc][0]*Piece_Analysis_Record[pYc][piece_next][0] == 3 )
            hand_cut_four++;
        //5-"** **"
        piece_next = pXc - Piece_Analysis_Record[pYc][pXc][1] - 1;
        if (piece_next>=0 && Piece_Analysis_Record[pYc][pXc][0] == 2 && Piece_Analysis_Record[pYc][piece_next][0] == 2 )
            hand_cut_four++;
        piece_next = pXc + Piece_Analysis_Record[pYc][pXc][0] - Piece_Analysis_Record[pYc][pXc][1] + 2;
        if (piece_next<BOARD_CELL_NO && Piece_Analysis_Record[pYc][pXc][0] == 2 && Piece_Analysis_Record[pYc][piece_next][0] == 2 )
            hand_cut_four++;
        //6-"***...***"
        if (Piece_Analysis_Record[pYc][pXc][0] > 5)
            hand_cut_six++;
        //////////////////////////////////////////////////////////////////
        //         Start check hand-cut of verticle direction           //
        ///////////////////////////////////////////////////////////////////
        //1-"***"
        if (Piece_Analysis_Record[pYc][pXc][2] == 3)
            hand_cut_three++;
        //2-"** *"
        piece_next = pYc - Piece_Analysis_Record[pYc][pXc][3] - 1;
        if (piece_next>=0 && Piece_Analysis_Record[pYc][pXc][2]*Piece_Analysis_Record[piece_next][pXc][2] == 2 )
            hand_cut_three++;
        piece_next = pYc + Piece_Analysis_Record[pYc][pXc][2] - Piece_Analysis_Record[pYc][pXc][3] + 2;
        if (piece_next<BOARD_CELL_NO && Piece_Analysis_Record[pYc][pXc][2]*Piece_Analysis_Record[piece_next][pXc][2] == 2 )
            hand_cut_three++;
        //3-"****"
        if (Piece_Analysis_Record[pYc][pXc][2] == 4)
            hand_cut_four++;
        //4-"*** *"
        piece_next = pYc - Piece_Analysis_Record[pYc][pXc][3] - 1;
        if (piece_next>=0 && Piece_Analysis_Record[pYc][pXc][2]*Piece_Analysis_Record[piece_next][pXc][2] == 3 )
            hand_cut_four++;
        piece_next = pYc + Piece_Analysis_Record[pYc][pXc][2] - Piece_Analysis_Record[pYc][pXc][3] + 2;
        if (piece_next<BOARD_CELL_NO && Piece_Analysis_Record[pYc][pXc][2]*Piece_Analysis_Record[piece_next][pXc][2] == 3 )
            hand_cut_four++;
        //5-"** **"
        piece_next = pYc - Piece_Analysis_Record[pYc][pXc][3] - 1;
        if (piece_next>=0 && Piece_Analysis_Record[pYc][pXc][2] == 2 && Piece_Analysis_Record[piece_next][pXc][2] == 2 )
            hand_cut_four++;
        piece_next = pYc + Piece_Analysis_Record[pYc][pXc][2] - Piece_Analysis_Record[pYc][pXc][3] + 2;
        if (piece_next<BOARD_CELL_NO && Piece_Analysis_Record[pYc][pXc][2] == 2 && Piece_Analysis_Record[piece_next][pXc][2] == 2 )
            hand_cut_four++;
        //6-"***...***"
        if (Piece_Analysis_Record[pYc][pXc][2] > 5)
            hand_cut_six++;
        ///////////////////////////////////////////////////////////////////
        //          Start check hand-cut of BL-to-TR direction           //
        ///////////////////////////////////////////////////////////////////
        //1-"***"
        if (Piece_Analysis_Record[pYc][pXc][4] == 3)
            hand_cut_three++;
        //2-"** *"
        piece_next = pXc - Piece_Analysis_Record[pYc][pXc][5] - 1;
        piece_next2 = pYc + Piece_Analysis_Record[pYc][pXc][4] - Piece_Analysis_Record[pYc][pXc][5] + 2;
        if (piece_next>=0 && piece_next2<BOARD_CELL_NO && Piece_Analysis_Record[pYc][pXc][4]*Piece_Analysis_Record[piece_next2][piece_next][4] == 2 )
            hand_cut_three++;
        piece_next = pXc + Piece_Analysis_Record[pYc][pXc][4] - Piece_Analysis_Record[pYc][pXc][5] + 2;
        piece_next2 = pYc - Piece_Analysis_Record[pYc][pXc][5] - 1;
        if (piece_next<BOARD_CELL_NO && piece_next2>=0 && Piece_Analysis_Record[pYc][pXc][4]*Piece_Analysis_Record[piece_next2][piece_next][4] == 2 )
            hand_cut_three++;
        //3-"****"
        if (Piece_Analysis_Record[pYc][pXc][4] == 4)
            hand_cut_four++;
        //4-"*** *"
        piece_next = pXc - Piece_Analysis_Record[pYc][pXc][5] - 1;
        piece_next2 = pYc + Piece_Analysis_Record[pYc][pXc][4] - Piece_Analysis_Record[pYc][pXc][5] + 2;
        if (piece_next>=0 && piece_next2<BOARD_CELL_NO && Piece_Analysis_Record[pYc][pXc][4]*Piece_Analysis_Record[piece_next2][piece_next][4] == 3 )
            hand_cut_four++;
        piece_next = pXc + Piece_Analysis_Record[pYc][pXc][4] - Piece_Analysis_Record[pYc][pXc][5] + 2;
        piece_next2 = pYc - Piece_Analysis_Record[pYc][pXc][5] - 1;
        if (piece_next<BOARD_CELL_NO && piece_next2>=0 && Piece_Analysis_Record[pYc][pXc][4]*Piece_Analysis_Record[piece_next2][piece_next][4] == 3 )
            hand_cut_four++;
        //5-"** **"
        piece_next = pXc - Piece_Analysis_Record[pYc][pXc][5] - 1;
        piece_next2 = pYc + Piece_Analysis_Record[pYc][pXc][4] - Piece_Analysis_Record[pYc][pXc][5] + 2;
        if (piece_next>=0 && piece_next2<BOARD_CELL_NO && Piece_Analysis_Record[pYc][pXc][4]==2 && Piece_Analysis_Record[piece_next2][piece_next][4] == 2 )
            hand_cut_four++;
        piece_next = pXc + Piece_Analysis_Record[pYc][pXc][4] - Piece_Analysis_Record[pYc][pXc][5] + 2;
        piece_next2 = pYc - Piece_Analysis_Record[pYc][pXc][5] - 1;
        if (piece_next<BOARD_CELL_NO && piece_next2>=0 && Piece_Analysis_Record[pYc][pXc][4]==2 && Piece_Analysis_Record[piece_next2][piece_next][4] == 2 )
            hand_cut_four++;
        //6-"***...***"
        if (Piece_Analysis_Record[pYc][pXc][4] > 5)
            hand_cut_six++;
        ///////////////////////////////////////////////////////////////////
        //          Start check hand-cut of TL-to-BR direction           //
        ///////////////////////////////////////////////////////////////////
        //1-"***"
        if (Piece_Analysis_Record[pYc][pXc][6] == 3)
            hand_cut_three++;
        //2-"** *"
        piece_next = pXc - Piece_Analysis_Record[pYc][pXc][7] - 1;
        piece_next2 = pYc - Piece_Analysis_Record[pYc][pXc][7] - 1;
        if (piece_next>=0 && piece_next2>=0 && Piece_Analysis_Record[pYc][pXc][6]*Piece_Analysis_Record[piece_next2][piece_next][6] == 2 )
            hand_cut_three++;
        piece_next = pXc + Piece_Analysis_Record[pYc][pXc][6] - Piece_Analysis_Record[pYc][pXc][7] + 2;
        piece_next2 = pYc + Piece_Analysis_Record[pYc][pXc][6] - Piece_Analysis_Record[pYc][pXc][7] + 2;
        if (piece_next<BOARD_CELL_NO && piece_next2<BOARD_CELL_NO && Piece_Analysis_Record[pYc][pXc][6]*Piece_Analysis_Record[piece_next2][piece_next][6] == 2 )
            hand_cut_three++;
        //3-"****"
        if (Piece_Analysis_Record[pYc][pXc][6] == 4)
            hand_cut_four++;
        //4-"*** *"
        piece_next = pXc - Piece_Analysis_Record[pYc][pXc][7] - 1;
        piece_next2 = pYc - Piece_Analysis_Record[pYc][pXc][7] - 1;
        if (piece_next>=0 && piece_next2>=0 && Piece_Analysis_Record[pYc][pXc][6]*Piece_Analysis_Record[piece_next2][piece_next][6] == 3 )
            hand_cut_four++;
        piece_next = pXc + Piece_Analysis_Record[pYc][pXc][6] - Piece_Analysis_Record[pYc][pXc][7] + 2;
        piece_next2 = pYc + Piece_Analysis_Record[pYc][pXc][6] - Piece_Analysis_Record[pYc][pXc][7] + 2;
        if (piece_next<BOARD_CELL_NO && piece_next2<BOARD_CELL_NO && Piece_Analysis_Record[pYc][pXc][6]*Piece_Analysis_Record[piece_next2][piece_next][6] == 3 )
            hand_cut_four++;
        //5-"** **"
        piece_next = pXc - Piece_Analysis_Record[pYc][pXc][7] - 1;
        piece_next2 = pYc - Piece_Analysis_Record[pYc][pXc][7] - 1;
        if (piece_next>=0 && piece_next2>=0 && Piece_Analysis_Record[pYc][pXc][6]==2 && Piece_Analysis_Record[piece_next2][piece_next][6] == 2 )
            hand_cut_four++;
        piece_next = pXc + Piece_Analysis_Record[pYc][pXc][6] - Piece_Analysis_Record[pYc][pXc][7] + 2;
        piece_next2 = pYc + Piece_Analysis_Record[pYc][pXc][6] - Piece_Analysis_Record[pYc][pXc][7] + 2;
        if (piece_next<BOARD_CELL_NO && piece_next2<BOARD_CELL_NO && Piece_Analysis_Record[pYc][pXc][6]==2 && Piece_Analysis_Record[piece_next2][piece_next][6] == 2 )
            hand_cut_four++;
        //6-"***...***"
        if (Piece_Analysis_Record[pYc][pXc][6] > 5)
            hand_cut_six++;
            
        if (hand_cut_three >= 2 || hand_cut_four >= 2 || hand_cut_six >= 1)
        {
            win_state = 1;
            gobang_win_display(1 - is_white_mode);
            continue;
        }
    }
    is_white_mode = 1 - is_white_mode;   //Set back to the Piece of the other color
  }
  else if(B==2)
  {
//    Vga_Clr_Pixel(VGA_0_BASE,pX,pY);
    rclick_no++;
    if (rclick_no > RCLICK_RESTART_THRESHOLD)
    {
        win_state = 0;
        is_white_mode = 0;
        gobang_game_start();
    }
  }
   
  }while((r16(HcRhP2) & 0x01) ==0x01);
 printf("\nMouse Not Detected");
}

void mouse(void)
{
 unsigned int rbuf[128];
 unsigned int dev_req[4]={0x0680,0x0100,0x0000,0x0008};
 unsigned int uni_req[4]={0x0500,3,0x0000,0x0000};

 //buffer information
 unsigned int atllen,ptllen,intllen;
 unsigned int atl_start;

 //atl parameters
 unsigned long atl_skip=0xFFFFFFFE;
 unsigned long atl_done=0;
 unsigned long atl_last=0x00000001;
 unsigned int  atl_blk_size=64;
 unsigned int  atl_cnt=1;
 unsigned int  atl_timeout=200;
 unsigned int mycode;
 unsigned int iManufacturer,iProduct;
 unsigned int starty=5;
 unsigned int status;
 unsigned int mouse01=0,mouse02=0;
 unsigned int g=0;

while(1)
{
  dev_req[0]=0x0680;
  dev_req[1]=0x0100;
  dev_req[2]=0x0000;
  dev_req[3]=0x0008;
  uni_req[0]=0x0500;
  uni_req[1]=3;
  uni_req[2]=0x0000;
  uni_req[3]=0x0000;


 //atl parameters
  atl_skip=0xFFFFFFFE;
  atl_done=0;
  atl_last=0x00000001;
  atl_blk_size=64;
  atl_cnt=1;
  atl_timeout=200;
  starty=5;
  mouse01=0,mouse02=0;
 

 set_operational();
 enable_port();

 reset_usb();
 erase_all();
 set_operational();
 enable_port();

 
 w16(HcControl,0x6c0);
 w16(HcUpInt,0x1a9);
 //delay(300);

 w16(HcBufStatus,0x00);

 //Setup ATL Parameters
 w32(HcATLSkip,atl_skip);
 w32(HcATLLast,atl_last);
 w16(HcATLBlkSize,atl_blk_size);
 w16(HcATLThrsCnt,atl_cnt);
 w16(HcATLTimeOut,atl_timeout);

 //Setup ATL Buffer
 atllen  =r16(HcATLLen);
 ptllen  =r16(HcPTLLen);
 intllen =r16(HcINTLen);

 atl_start=ptllen+ptllen+intllen;

 status=assign_address(1,2,0);
 status=assign_address(1,2,0);

 if(g==0)
 {
  printf("ISP1362 Mouse Demo.....\n");
  g=1;
 }

 w16(HcUpIntEnable,0x120);

 if( (status&0x0001)!=0) //port 2 active
 {
//  Check port 2 for mouse
  mycode=get_control(rbuf,2,'D',0,2);
  if(mycode==0x0300)
  {
   iManufacturer = rbuf[7]&0xFF;
   iProduct = (rbuf[7]&0xFF00)>>8;
   addr_info(2,'W','O',iManufacturer);
   addr_info(2,'W','P',iProduct);
   mycode=get_control(rbuf,2,'H',addr_info(2,'R','P',0),2);
   if( *(rbuf+1)==0x0209  )
   {
	   printf("\nMouse Detected");
	   mouse02=1;
   }
  }
 }

 if((mouse02==1)&&(mouse01==0))
 {
  mycode=set_config(2,1);
  if(mycode==0)
  play_mouse(2);
 }
 usleep(100000);
}
}

