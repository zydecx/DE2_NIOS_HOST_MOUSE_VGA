#ifndef __GOBANG_H__
#define __GOBANG_H__

#define BOARD_LEFT_EDGE     35
#define BOARD_HOR_MARGIN    30
#define BOARD_VER_MARGIN    30
#define BOARD_TOP_EDGE      30
#define BOARD_CELL_NO       15 
#define BOARD_PIECE_RADIUS  12  //���Ӱ뾶��ע������Ĭ��Ϊ10-12�Ļ�
#define BOARD_PIECE_OFFSET  10  //�뾶10�ڵĵ����Ч
#define RCLICK_RESTART_THRESHOLD   40  //Threshold for NO. of right-click before game restarts

int Piece_Record[BOARD_CELL_NO][BOARD_CELL_NO]; 
//char ASCII8x16_Table[4080];

//Record to help analyze the game status
//--Four directions:Horizontal, Vertical, Bottom_Left to Top-Right, Top-Left to Bottom-Right
//--[0,2,4,6]:Number of connected same color pieces of each direction
//--[1,3,5,7]:Serial No. of current piece in the connected series 
int Piece_Analysis_Record[BOARD_CELL_NO][BOARD_CELL_NO][8];
   
void reset_piece_record_array();
void clean_screen();            //clean all points on screen
void gobang_board_display();    //Display gobang board on screen
void gobang_draw_box(int, int, int, int);
void gobang_game_start();       //start a game
void gobang_win_display(unsigned int);      //change screen color when win

//void set_ASCII8x16_Table();
void gobang_show_char(unsigned char*, int, int, int);
void gobang_show_text(unsigned char*, int, int);
void gobang_show_chinese(int*, int, int);

#endif
