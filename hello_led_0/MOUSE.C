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
 unsigned int lclick_no = 0;
 unsigned int rclick_no = 0;    //no. of right click; Reset when left click
// unsigned int win_state = 0;    //change to 1 when player wins a game, so that no more pieces are allowed
 unsigned int place_piece_status;   //return value of gobang_place_piece(), 2-successful, 3-fail, 0-black win, 1-white win
 
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
    
  /*if(B==1)
  Vga_Set_Pixel(VGA_0_BASE,pX,pY);*/
  if(B==1){
    if (lclick_no==1)   continue; //Forbid continuely placing pieces by keeping left click
    lclick_no = 1;
    rclick_no = 0;  //Reset NO of right-click
    if (pX > INSTR_BORDER)
        gobang_read_instr_state(pX, pY);
    else /*if (win_state==0)*/
    {
        place_piece_status = gobang_proc_lclick(pX, pY);
    }
  }
  else if(B==2)
  {
//    Vga_Clr_Pixel(VGA_0_BASE,pX,pY);
    rclick_no++;
    lclick_no = 0;
    if (rclick_no > RCLICK_RESTART_THRESHOLD)
    {
//        win_state = 0;
//        is_white_mode = 0;
        gobang_game_start();
    }
  }
  else
  {
    lclick_no = 0;
    rclick_no = 0;
//    Vga_Set_Pixel(VGA_0_BASE, pX, pY);
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

