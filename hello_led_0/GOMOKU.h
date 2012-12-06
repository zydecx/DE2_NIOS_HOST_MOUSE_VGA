#ifndef __GOMOKU_H__
#define __GOMOKU_H__

#define BOARD_LEFT_EDGE     40
#define BOARD_HOR_MARGIN    40
#define BOARD_VER_MARGIN    30
#define BOARD_TOP_EDGE      30
#define BOARD_CELL_NO       15 
#define BOARD_PIECE_RADIUS  12  //���Ӱ뾶��ע������Ĭ��Ϊ10-12�Ļ�
#define BOARD_PIECE_OFFSET  15  //�뾶15�ڵĵ����Ч

//int Board_Piece_Record[BOARD_CELL_NO][BOARD_CELL_NO] = {0}; 

void clean_screen();            //clean all points on screen
void gomoku_board_display();    //Display gomoku board on screen
//void gomoku_game_start();       //start a game

#endif
