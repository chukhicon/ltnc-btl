#ifndef CHUKHI_BASE_
#define CHUKHI_BASE_
#include<bits/stdc++.h>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>
using namespace std;

#define IS_REPEATITIVE -1
#define NOT_REPEATITIVE 0

#define MIX_CHANNEL -1

#define SMALL_BUTTON 1
#define COMMON_BUTTON 2

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 576;
const int RECT_SIZE=30;

const int MOVE_START_X = 8, MOVE_START_Y = 8, SPEED_UP = 1;
const int MOVE_ENEMY_X = 4, MOVE_ENEMY_Y = 3;

const int COMMON_BUTTON_WIDTH = 150;
const int COMMON_BUTTON_HEIGHT = 98;
const int SMALL_BUTTON_WIDTH = 22;
const int SMALL_BUTTON_HEIGHT = 34;

const int PLAY_BUTON_POSX = 444;
const int PLAY_BUTTON_POSY= 141;
const int HELP_BUTTON_POSX = 444;
const int HELP_BUTTON_POSY = 296;
const int EXIT_BUTTON_POSX = 444;
const int EXIT_BUTTON_POSY = 435;
const int BACK_BUTTON_POSX = 31;
const int BACK_BUTTON_POSY = 29;
// const int PAUSE_BUTTON_POSX = 31;
// const int PAUSE_BUTTON_POSY = 29;
// const int CONTINUE_BUTTON_POSX = 31;
// const int CONTINUE_BUTTON_POSY = 29;
const int TEXT_1_POSX = 15;
const int TEXT_1_POSY = 542;
const int SCORE_POSX = 110;
const int SCORE_POSY = 542;
const int TEXT_2_POSX = 231;
const int TEXT_2_POSY = 542;
const int HIGH_SCORE_POSX = 314;
const int HIGH_SCORE_POSY = 542;
const int TEXT_3_POSX = 638;
const int TEXT_3_POSY = 542;
const int HEATH_POSX = 750;
const int HEATH_POSY = 542;
const int TEXT_4_POSX = 820; 
const int TEXT_4_POSY = 542;
// const int ARMOR_POSX = 922;
// const int ARMOR_POSY = 535;
const int TEXT_5_POSX = 394;
const int TEXT_5_POSY = 458;
const int YOUR_SCORE_POSX = 536;
const int YOUR_SCORE_POSY = 458;// khai báo hằng số ở đây

enum ErrorType {SDL_ERROR, IMG_ERROR, MIX_ERROR, OK_ERROR, TTF_ERROR};

enum ButtonSprite
{
	BUTTON_MOUSE_OUT = 0,
	BUTTON_MOUSE_OVER = 1,
	BUTTON_TOTAL = 2
};

void LogError(string msg, ErrorType error_code = SDL_ERROR);
#endif // CHUKHI_BASE_
