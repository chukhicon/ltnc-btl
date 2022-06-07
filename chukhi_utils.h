#ifndef CHUKHI_UTILS_H_
#define CHUKHI_UTILS_H_

#include "chukhi_base.h"
#include "chukhi_LTexture.h"
#include "chukhi_button.h"
#include "chukhi_character.h"
#include "chukhi_enemy.h"
#include "chukhi_help.h"

bool Init();
bool LoadMedia();
void Close();

string GetHighScoreFromFile(string path);

void UpdateHighScore(string path,
	const int& score,
	const string& old_high_score);

void HandlePlayButton(SDL_Event* e,
	Button& PlayButton,
	bool& QuitMenu,
	bool& Play,
	Mix_Chunk* gClick);

void HandleHelpButton(SDL_Event* e,
	SDL_Rect& gBackButton,
	Button& HelpButton,
	Button& BackButton,
	LTexture gInstructionTexture,
	LTexture gBackButtonTexture,
	SDL_Renderer *gRenderer,
	bool &Quit_game,
	Mix_Chunk *gClick);

void HandleExitButton(SDL_Event* e,
	Button& ExitButton,
	bool& Quit,
	Mix_Chunk* gClick);

void GenerateEnemy(Enemy& enemy1, Enemy& enemy2, Enemy& enemy3, SDL_Renderer* gRenderer);

void GenerateHelp(Help& help1, Help& help2, SDL_Renderer* gRenderer);

bool CheckInside(Character character,  LTexture char_img, const int CHIEU_DAI, const int CHIEU_RONG);

bool CheckColission(Character character, LTexture char_img, Enemy enemy);

bool CheckEnemyColission(Enemy enemy1, Enemy enemy2);

void DrawPlayerScore(LTexture gTextTexture,
    LTexture gScoreTexture,
    SDL_Color textColor,
    SDL_Renderer* gRenderer,
    TTF_Font* gFont,
    const int& score);

void DrawPlayerHighScore(LTexture gTextTexture,
    LTexture gHighScoreTexture,
    SDL_Color textColor,
    SDL_Renderer* gRenderer,
    TTF_Font* gFont, 
    const string& HighScore);

void DrawPlayerHeath(LTexture gTextTexture,
    LTexture gHeathTexture,
    SDL_Color textColor,
    SDL_Renderer* gRenderer,
    TTF_Font* gFont, 
    const int& Heath);




void DrawPlayerYourScore(LTexture gTextTexture,
	LTexture gYourScoreTexture, 
	SDL_Color textColor, 
	SDL_Renderer* gRenderer, 
	TTF_Font* gFont, 
	const int& YourScore);

void DrawPlayerYourHighScore(LTexture gTextTexture,
	LTexture gYourHighScoreTexture, 
	SDL_Color textColor, 
	SDL_Renderer* gRenderer, 
	TTF_Font* gFont, 
	const int& YourScore);

void DrawEndGameSelection(LTexture gLoseTexture, LTexture gText5Texture, LTexture gText6Texture, LTexture gYourScoreTexture, 
                    SDL_Event* e, SDL_Renderer* gRenderer, SDL_Color textcolor, TTF_Font* gFont, 
                    bool& Play_Again, bool& Return_Menu, bool& Quit_Menu, 
                    const int& YourScore, const string& highscore, Mix_Music* gMenuMusic);

#endif // CHUKHI_UTILS_H_
