#ifndef __GOBANG_H__
#define __GOBANG_H__

#define INSTR_BORDER        475
#define BOARD_LEFT_EDGE     35
#define BOARD_HOR_MARGIN    30
#define BOARD_VER_MARGIN    30
#define BOARD_TOP_EDGE      30
#define BOARD_CELL_NO       15 
#define BOARD_PIECE_RADIUS  12  //棋子半径。注：黑子默认为10-12的环
#define BOARD_PIECE_OFFSET  10  //半径10内的点击有效
#define RCLICK_RESTART_THRESHOLD   40  //Threshold for NO. of right-click before game restarts

int Piece_Record[BOARD_CELL_NO][BOARD_CELL_NO]; 
//char ASCII8x16_Table[4080];

//Record to help analyze the game status
//--Four directions:Horizontal, Vertical, Bottom_Left to Top-Right, Top-Left to Bottom-Right
//--[0,2,4,6]:Number of connected same color pieces of each direction
//--[1,3,5,7]:Serial No. of current piece in the connected series 
int Piece_Analysis_Record[BOARD_CELL_NO][BOARD_CELL_NO][8];
//Instr_Array[5]:0-Mode, 1-Total Rounds of game, 2-Hand-cut or not, 3-Peer-Peer or Peer-PC, 4-User first or not, 5-Start GAme
//0-Mode: 0-调试，1-欢迎，2-对战中，3-局结束，4-比赛结束
#define INSTR_ARRAY_SIZE    5
int Instr_Array[INSTR_ARRAY_SIZE];
//Ongame_Array[5]:0-No. of Rounds, 1-current round, 2-current color(W-1/B-0), 3-B wins rounds, 4-W wins rounds
#define ONGAME_ARRAY_SIZE    5
int Ongame_Array[ONGAME_ARRAY_SIZE];
   
void reset_piece_record_array();    //reset all arrays
void clean_screen();            //clean all points on screen
void gobang_board_display();    //Display gobang board on screen
void gobang_instr_display();    //display gobang instruction on the right of screen
void gobang_instr_ongame_display();//display instruction part when players are now playing
void gobang_box_fill(int, int, int, int);   //(int width, int height, int posx, int posy), (posx, posy) is the top-left coordinate of box
void gobang_box_fullfill(int, int, int, int);   //(int width, int height, int posx, int posy), (posx, posy) is the top-left coordinate of box
void gobang_box_outline(int, int, int, int);//(int width, int height, int posx, int posy), (posx, posy) is the top-left coordinate of the outline
void gobang_game_start();       //start a game
void gobang_win_display(unsigned int);      //change screen color and display tiptext when win

void gobang_draw_circle(int, int, int);
void gobang_clear_circle(int, int, int);
unsigned int gobang_click_circle(int, int, int, int, int);
//void set_ASCII8x16_Table();

/*
 * Display single character(char format), a letter or number, or a Chinese character
 * (unsigned char* charac, int isASC, int posx, int posy), isASC-if the character is ASCII character
 */
void gobang_show_char(unsigned char*, int, int, int);  
/*
 * Display strings(char format), a series of letters, numbers, or Chinese characters
 * (unsigned char* text, int posx, int posy)
 */ 
void gobang_show_text(unsigned char*, int, int);  
/*
 * Display Chinese characters according to its offsets in the word stock
 * AS for tests during designing
 * (int* text, int posx, int posy)
 */      
void gobang_show_chinese(int*, int, int);
/*
 * Display single number(int format)
 * (int num, int posx, int posy)
 */
void gobang_show_num(int, int, int);


void gobang_read_instr_state(int, int);
//return value of gobang_place_piece(), 2-successful, 3-fail, 0-black win, 1-white win
unsigned int gobang_place_piece(int, int, unsigned int);
unsigned int gobang_handcut_check(int[][BOARD_CELL_NO][8], unsigned int, int, int);

#endif
