#ifndef __GOMOKU_H__
#define __GOMOKU_H__

#define BOARD_LEFT_EDGE     40
#define BOARD_HOR_MARGIN    40
#define BOARD_VER_MARGIN    30
#define BOARD_TOP_EDGE      30
#define BOARD_CELL_NO       15 
#define BOARD_PIECE_RADIUS  12  //���Ӱ뾶��ע������Ĭ��Ϊ10-12�Ļ�
#define BOARD_PIECE_OFFSET  15  //�뾶15�ڵĵ����Ч
#define RCLICK_RESTART_THRESHOLD   40  //Threshold for NO. of right-click before game restarts

int Piece_Record[BOARD_CELL_NO][BOARD_CELL_NO]; 

//Record to help analyze the game status
//--Four directions:Horizontal, Vertical, Bottom_Left to Top-Right, Top-Left to Bottom-Right
//--[0,2,4,6]:Number of connected same color pieces of each direction
//--[1,3,5,7]:Serial No. of current piece in the connected series 
int Piece_Analysis_Record[BOARD_CELL_NO][BOARD_CELL_NO][8];
   
void reset_piece_record_array();
void clean_screen();            //clean all points on screen
void gomoku_board_display();    //Display gomoku board on screen
void gomoku_game_start();       //start a game

#endif
