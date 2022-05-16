#ifndef CHUKHI_BASE_
#define CHUKHI_BASE_
#include<bits/stdc++.h>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>
using namespace std;


const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 800;
const int RECT_SIZE=30;
const char* WINDOW_TITLE = "game cua chukhicon ne";

const int COMMON_BUTTON_WIDTH = 150;
const int COMMON_BUTTON_HEIGHT = 98;
const int SMALL_BUTTON_WIDTH = 22;
const int SMALL_BUTTON_HEIGHT = 34;

const int PLAY_BUTON_POSX = 389;
const int PLAY_BUTTON_POSY= 186;
const int HELP_BUTTON_POSX = 389;
const int HELP_BUTTON_POSY = 293;
const int EXIT_BUTTON_POSX = 389;
const int EXIT_BUTTON_POSY = 402;
const int BACK_BUTTON_POSX = 31;
const int BACK_BUTTON_POSY = 29;
const int PAUSE_BUTTON_POSX = 31;
const int PAUSE_BUTTON_POSY = 29;
const int CONTINUE_BUTTON_POSX = 31;
const int CONTINUE_BUTTON_POSY = 29;// khai báo hằng số ở đây

enum ErrorType {SDL_ERROR, IMG_ERROR, MIX_ERROR, OK_ERROR, TTF_ERROR};
void LogError(string msg, ErrorType error_code = SDL_ERROR);
enum ButtonSprite
{
	BUTTON_MOUSE_OUT = 0,
	BUTTON_MOUSE_OVER = 1,
	BUTTON_TOTAL = 2
};


#endif // CHUKHI_BASE_
