#ifndef __GOBANG_H__
#define __GOBANG_H__

#define BOARD_LEFT_EDGE     40
#define BOARD_HOR_MARGIN    40
#define BOARD_VER_MARGIN    30
#define BOARD_TOP_EDGE      30
#define BOARD_CELL_NO       15 
#define BOARD_PIECE_RADIUS  12  //棋子半径。注：黑子默认为10-12的环
#define BOARD_PIECE_OFFSET  15  //半径15内的点击有效
#define RCLICK_RESTART_THRESHOLD   40  //Threshold for NO. of right-click before game restarts

int Piece_Record[BOARD_CELL_NO][BOARD_CELL_NO]; 

//Record to help analyze the game status
//--Four directions:Horizontal, Vertical, Bottom_Left to Top-Right, Top-Left to Bottom-Right
//--[0,2,4,6]:Number of connected same color pieces of each direction
//--[1,3,5,7]:Serial No. of current piece in the connected series 
int Piece_Analysis_Record[BOARD_CELL_NO][BOARD_CELL_NO][8];
   
void reset_piece_record_array();
void clean_screen();            //clean all points on screen
void gobang_board_display();    //Display gobang board on screen
void gobang_game_start();       //start a game
void gobang_win_display(unsigned int);      //change screen color when win

#endif
