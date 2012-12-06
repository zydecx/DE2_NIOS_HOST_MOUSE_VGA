#ifndef __GOMOKU_H__
#define __GOMOKU_H__

#define BOARD_LEFT_EDGE     40
#define BOARD_HOR_MARGIN    40
#define BOARD_VER_MARGIN    30
#define BOARD_TOP_EDGE      30
#define BOARD_CELL_NO       15 
#define BOARD_PIECE_RADIUS  12  //棋子半径。注：黑子默认为10-12的环
#define BOARD_PIECE_OFFSET  15  //半径15内的点击有效

//int Board_Piece_Record[BOARD_CELL_NO][BOARD_CELL_NO] = {0}; 

void clean_screen();            //clean all points on screen
void gomoku_board_display();    //Display gomoku board on screen
//void gomoku_game_start();       //start a game

#endif
