#include "chukhi_LTexture.h"
#include "chukhi_base.h"
#include "chukhi_button.h"
#include "chukhi_character.h"
#include "chukhi_enemy.h"
#include "chukhi_help.h"
#include "chukhi_utils.h"

const char* WINDOW_TITLE = "game cua chukhicon ne";

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;
SDL_Color textColor = {0, 0, 0};
TTF_Font* gFont = nullptr;
Mix_Music* gMusic = nullptr;
Mix_Music* gMenuMusic = nullptr;
Mix_Chunk* gClick = nullptr;
Mix_Chunk* gBom = nullptr;
Mix_Chunk* gLose = nullptr;

LTexture gMenuTexture;
LTexture gInstructionTexture;
LTexture gBackgroundTexture;
LTexture gCharacterTexture;
LTexture gPlayButtonTexture;
LTexture gHelpButtonTexture;
LTexture gExitButtonTexture;
LTexture gBackButtonTexture;
LTexture gLoseTexture;
LTexture gText1Texture;
LTexture gScoreTexture;
LTexture gText2Texture;
LTexture gHighScoreTexture;
LTexture gText3Texture;
LTexture gHeathTexture;
LTexture gText4Texture;
LTexture gArmorTexture;

Button PlayButton(PLAY_BUTON_POSX, PLAY_BUTTON_POSY);
Button HelpButton(HELP_BUTTON_POSX, HELP_BUTTON_POSY);
Button ExitButton(EXIT_BUTTON_POSX, EXIT_BUTTON_POSY);
Button BackButton(BACK_BUTTON_POSX, BACK_BUTTON_POSY);

Character character;

bool Quit_Menu = false, Play_Again = false, Quit_Game = false;

SDL_Rect gPlayButton;
SDL_Rect gExitButton;
SDL_Rect gHelpButton;
SDL_Rect gBackButton;
/*SDL_Rect gCharacterClips[RUNNING_FRAMES];
SDL_Rect gEnemyClips[FLYING_FRAMES];*/

int random(int N) { return rand() % N; }

bool initSDL();
bool loadMedia();
void Close();

int main(int argc, char* argv[]) {
    srand(time(NULL));

    // const int step=50;
    if (!initSDL()) {
        cerr << "load init loi roi !!" << endl;
    } else {
        if (!loadMedia()) {
            cerr << "load media failed" << endl;
        } else {
            // Mix_PlayMusic(gMenuMusic, IS_REPEATITIVE);
            while (!Quit_Menu) {
                SDL_Event e_mouse;
                while (SDL_PollEvent(&e_mouse) != 0) {
                    if (e_mouse.type == SDL_QUIT) {
                        Quit_Menu = true;
                    }
                    HandlePlayButton(&e_mouse, PlayButton, Quit_Menu, Play_Again, gClick);

                    HandleHelpButton(&e_mouse, gBackButton, HelpButton, BackButton,
                                     gInstructionTexture, gBackButtonTexture, gRenderer, Quit_Game,
                                     gClick);

                    HandleExitButton(&e_mouse, ExitButton, Quit_Menu, gClick);

                    if (Quit_Game == true) {
                        return 0;
                    }
                }

                gMenuTexture.Render(0, 0, gRenderer);

                // SDL_Rect* currentClip_Play = &gPlayButton[PlayButton.currentSprite];
                // PlayButton.Render( gRenderer, gPlayButtonTexture);

                // SDL_Rect* currentClip_Help = &gHelpButton[HelpButton.currentSprite];
                // HelpButton.Render( gRenderer, gHelpButtonTexture);

                // SDL_Rect* currentClip_Exit = &gExitButton[ExitButton.currentSprite];
                // ExitButton.Render( gRenderer, gExitButtonTexture);

                SDL_RenderPresent(gRenderer);
                bool Return_Menu = false;
                while (Play_Again && !Return_Menu) {
                    srand(time(NULL));
                    cerr << "playing";
                    int time = 0;
                    int score = 0;
                    int heath = 8;
                    int armor = 0;
                    int acceleration = 0;
                    /*int frame_Character = 0;
                    int frame_Enemy = 0;*/
                    string highscore = GetHighScoreFromFile("high_score.txt");

                    SDL_Event e;
                    // Enemy enemy1;
                    // Enemy enemy2;
                    // Enemy enemy3;

                    Mix_PlayMusic(gMusic, IS_REPEATITIVE);
                    // GenerateEnemy(enemy1, enemy2, enemy3, gRenderer);
                    bool Quit = false;
                    bool Game_Stage = true;
                    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                    while (!Quit) {
                        if (Game_Stage) {
                            SDL_RenderClear(gRenderer);
                            // UpdateGameTimeAndScore(time, acceleration, score);

                            while (SDL_PollEvent(&e) != 0) {
                                if (e.type == SDL_QUIT) {
                                    Quit = true;
                                    Play_Again = false;
                                }
                                if (e.type == SDL_KEYDOWN) {
                                    if (e.key.keysym.sym == 'p') Quit = true;
                                }

                                // character.HandleEvent(e, gJump);
                            }
                            gBackgroundTexture.Render(0, 0, gRenderer);
                            SDL_RenderPresent(gRenderer);
                        }
                    }
                    DrawEndGameSelection(gLoseTexture, &e, gRenderer, Play_Again, Return_Menu,
                                         Quit_Menu);
                }
            }
        }
    }

    Close();

    return 0;
}
bool initSDL() {
    bool success = true;
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        LogError("Failed to init SDL", SDL_ERROR);
        success = false;
    } else {
        gWindow = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                   SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        if (gWindow == NULL) {
            LogError("Can not create window: ", SDL_ERROR);
            success = false;
        } else {
            gRenderer = SDL_CreateRenderer(gWindow, -1,
                                           SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (gRenderer == NULL) {
                LogError("Can not create renderer: ", SDL_ERROR);
                success = false;
            } else {
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                if (!IMG_Init(IMG_INIT_PNG)) {
                    LogError("Can not initialize SDL_image: ", IMG_ERROR);
                    success = false;
                }

                if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
                    LogError("Can not initialize audio: ", MIX_ERROR);
                    success = false;
                }

                if (TTF_Init() < 0) {
                    LogError("Can not initialize font: ", TTF_ERROR);
                    success = false;
                }
            }
        }
    }
    return success;
}
bool loadMedia() {
    bool success = true;
    if (!gMenuTexture.LoadFromFile("imgs/Background/game_menu.png", gRenderer)) {
        cerr << "Failed to load menu image" << endl;
        success = false;
    }

    if (!gInstructionTexture.LoadFromFile("imgs/Background/game_intro.png", gRenderer)) {
        cerr << "Failed to load instruction image" << endl;
        success = false;
    }
    if (!gBackgroundTexture.LoadFromFile("imgs/Background/game_play.png", gRenderer)) {
        cerr << "Failed to load gameplay image" << endl;
        success = false;
    }
    if (!gCharacterTexture.LoadFromFile("imgs/Character/Character.png", gRenderer)) {
        cerr << "Failed to load character image" << endl;
        success = false;
    }
    if (!gLoseTexture.LoadFromFile("imgs/Background/game_lose.png", gRenderer)) {
        cerr << "Failed to load lose image" << endl;
        success = false;
    }
    gFont = TTF_OpenFont("Font/RobotoCondensed-Regular.ttf", 28);
    if (gFont == NULL) {
        LogError("Failed to load font", MIX_ERROR);
        success = false;
    } else {
        if (!gText1Texture.LoadFromRenderedText("Your score: ", gFont, textColor, gRenderer)) {
            cerr << "Failed to render text1 texture" << endl;
            success = false;
        }
        if (!gText2Texture.LoadFromRenderedText("High score: ", gFont, textColor, gRenderer)) {
            cerr << "Failed to render text2 texture" << endl;
            success = false;
        }
        if (!gText3Texture.LoadFromRenderedText("Your heath: ", gFont, textColor, gRenderer)) {
            cerr << "Failed to render text3 texture" << endl;
            success = false;
        }
        if (!gText4Texture.LoadFromRenderedText("Your armor: ", gFont, textColor, gRenderer)) {
            cerr << "Failed to render text4 texture" << endl;
            success = false;
        }
    }

    return success;
}
void Close() {
    // free()
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}
