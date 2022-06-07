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
SDL_Color textColor = {255, 255, 255};
SDL_Color textColor2 = {255, 255, 0};
TTF_Font* gFont = nullptr;
Mix_Music* gMusic = nullptr;
Mix_Music* gMenuMusic = nullptr;
Mix_Chunk* gClick = nullptr;
Mix_Chunk* gBom = nullptr;
Mix_Chunk* gLose = nullptr;
Mix_Chunk* gJump = nullptr;
Mix_Chunk* gColu = nullptr;

LTexture gMenuTexture;
LTexture gInstructionTexture;
LTexture gBackgroundTexture;
LTexture gBackgroundTexture2;
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
LTexture gText5Texture;
LTexture gYourScoreTexture;
LTexture gText6Texture;

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
            Mix_PlayMusic(gMenuMusic, IS_REPEATITIVE);
            while (!Quit_Menu) {
                SDL_Event e_mouse;
                while (SDL_PollEvent(&e_mouse) != 0) {
                    if (e_mouse.type == SDL_QUIT) {
                        Quit_Menu = true;
                    }
                    HandlePlayButton(&e_mouse, PlayButton, Quit_Menu,
                                     Play_Again, gClick);

                    HandleHelpButton(&e_mouse, gBackButton, HelpButton,
                                     BackButton, gInstructionTexture,
                                     gBackButtonTexture, gRenderer, Quit_Game,
                                     gClick);

                    HandleExitButton(&e_mouse, ExitButton, Quit_Menu, gClick);

                    if (Quit_Game == true) {
                        return 0;
                    }
                }

                gMenuTexture.Render(0, 0, gRenderer);

                SDL_RenderPresent(gRenderer);
                bool Return_Menu = false;
                while (Play_Again && !Return_Menu) {
                    srand(time(NULL));
                    cerr << "playing";
                    int time = 0;
                    int score = 0;
                    int heath = 20;
                    int armor = 0;
                    bool paused = false;
                    bool characterShown = true;
                    int YourScore;
                    int StartTime = SDL_GetTicks();
                    int EndTime;
                    int pauseStart;
                    int pauseEnd;
                    bool invincible = false;
                    int invincibleStart;
                    int invincibleEnd;
                    int blinkStart = SDL_GetTicks();
                    int blinkEnd;
                    string highscore = GetHighScoreFromFile("high_score.txt");

                    SDL_Event e;

                    Mix_PlayMusic(gMusic, IS_REPEATITIVE);

                    bool Quit = false;
                    bool Game_Stage = true;
                    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                    vector<Enemy*> enemies;
                    while (!Quit) {
                        if (Game_Stage) {
                            SDL_RenderClear(gRenderer);
                            if (!paused) {
                                score++;
                                if(score%500==0 && score>=500) {
                                    heath+=1;
                                    character.MOVE_X+=SPEED_UP;
                                    character.MOVE_Y+=SPEED_UP;
                                }
                            }
                            EndTime = SDL_GetTicks();
                            while (SDL_PollEvent(&e) != 0) {
                                if (e.type == SDL_QUIT) {
                                    Quit = true;
                                    Play_Again = false;
                                }
                                if (e.type == SDL_KEYDOWN) {
                                    if (e.key.keysym.sym == SDLK_ESCAPE)
                                        if (paused) {
                                            pauseEnd = SDL_GetTicks();
                                            paused = false;
                                            Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);
                                            if(Mix_PlayingMusic()!=0) Mix_ResumeMusic();
                                            else Mix_PlayMusic(gMusic, IS_REPEATITIVE);
                                            
                                            
                                            StartTime += pauseEnd - pauseStart;
                                            for (auto& enem : enemies) {
                                                (*enem).intervalStart +=
                                                    pauseEnd - pauseStart;
                                            }

                                        } else {
                                            Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);
                                            Mix_PauseMusic();
                                            pauseStart = SDL_GetTicks();
                                            paused = true;
                                        }
                                    if(e.key.keysym.sym == SDLK_g && heath>5 && score >= 500)
                                    {
                                        character.MOVE_X-=SPEED_UP;
                                        character.MOVE_Y-=SPEED_UP;
                                        heath-=5;

                                    }
                                }
                                if (!paused) character.CheckEvent(e, gJump);
                            }
                            if (!paused) {
                                if (invincible) {
                                    blinkEnd = SDL_GetTicks();
                                    if (blinkEnd - blinkStart > 1000 / 16) {
                                        characterShown =
                                            characterShown ? false : true;
                                        blinkStart = SDL_GetTicks();
                                    }
                                }

                                if (!paused) character.Move();
                                if (EndTime - StartTime > 700) {
                                    int enem = rand() % 3, r = rand() % 4;
                                    if (enem == 0) {
                                        Enemy* enemy = new Enemy(
                                            rand() % (SCREEN_WIDTH - 50),
                                            rand() % (TEXT_1_POSY - 50), 1,
                                            "imgs/Enemy/Enemy1.png", gRenderer,
                                            r);
                                        enemy->startInterval();
                                        enemies.push_back(enemy);
                                    }
                                    if (enem == 1) {
                                        Enemy* enemy = new Enemy(
                                            rand() % (SCREEN_WIDTH - 50),
                                            rand() % (TEXT_1_POSY - 50), 2,
                                            "imgs/Enemy/Enemy2.png", gRenderer,
                                            r);
                                        enemy->startInterval();
                                        enemies.push_back(enemy);
                                    }
                                    if (enem == 2) {
                                        Enemy* enemy = new Enemy(
                                            rand() % (SCREEN_WIDTH - 50),
                                            rand() % (TEXT_1_POSY - 50), 3,
                                            "imgs/Enemy/Enemy3.png", gRenderer,
                                            r);
                                        enemy->startInterval();
                                        enemies.push_back(enemy);
                                    }
                                    cerr << "ok !!!" << endl;
                                    StartTime = SDL_GetTicks();

                                }
                                if (!(CheckInside(character, gCharacterTexture,
                                                  SCREEN_WIDTH,
                                                  SCREEN_HEIGHT - 37)) ||
                                    heath <= 0) {
                                    Mix_PauseMusic();
                                    Mix_PlayChannel(MIX_CHANNEL, gLose, NOT_REPEATITIVE);// phat am thanh

                                    Quit = true;
                                    UpdateHighScore("high_score.txt", score,
                                                    highscore);
                                    character = Character();
                                    for (vector<Enemy*>::iterator enem =
                                             enemies.begin();
                                         enem != enemies.end(); enem++) {
                                        (*enem)->free();
                                        delete *enem;
                                    }
                                    enemies.clear();
                                }
                                for (vector<Enemy*>::iterator enem =
                                         enemies.begin();
                                     enem != enemies.end(); enem++) {
                                    if (!paused) (*enem)->move(); 
                                    if (CheckColission(character,
                                                       gCharacterTexture,
                                                       **enem)) {
                                        Mix_PlayChannel(
                                            MIX_CHANNEL, gColu,
                                            NOT_REPEATITIVE);  // phat am thanh
                                                               // tai day

                                        // Quit = true;
                                        // UpdateHighScore("high_score.txt",
                                        // score,
                                        //                 highscore);
                                        // character = Character();
                                        // switch (character.check)
                                        // {
                                        // case Character::move_up:
                                        //     character.check=Character::move_down;
                                        //     // if(!(CheckColission(character,
                                        //     gCharacterTexture,
                                        //     //            **enem))){

                                        //     //         }
                                        //     break;
                                        // case Character::move_down:
                                        //     character.check=Character::move_up;
                                        //     break;
                                        // case Character::move_left:
                                        //     character.check=Character::move_left;
                                        //     break;
                                        // case Character::move_right:
                                        //     character.check=Character::move_left;
                                        //     break;
                                        // default:
                                        //     break;
                                        // }
                                        if (!invincible) {
                                            // heath--;
                                            if ((*enem)->GetType() == 1)
                                                heath--;
                                            if ((*enem)->GetType() == 2)
                                                heath -= 2;
                                            if ((*enem)->GetType() == 3)
                                                heath -= 4;
                                            
                                            invincible = true;
                                            invincibleStart = SDL_GetTicks();
                                            blinkStart = SDL_GetTicks();
                                        }
                                    }
                                    if (invincible) {
                                        invincibleEnd = SDL_GetTicks();
                                        if (invincibleEnd - invincibleStart >
                                            1000) {
                                            invincible = false;
                                            characterShown = true;
                                        }
                                    }
                                    if ((*enem)->getExistTime() > 5000) {
                                        (*enem)->free();
                                        delete *enem;
                                        enemies.erase(enem);
                                    }
                                }
                            }
                        }

                        
                        gBackgroundTexture.Render(0, 0, gRenderer);

                        for (auto& enem : enemies) {
                            enem->Render(gRenderer);
                        }
                        if (characterShown) {
                            character.Render(gRenderer, gCharacterTexture);
                        }
                        gBackgroundTexture2.Render(0, 539, gRenderer);

                        DrawPlayerScore(gText1Texture, gScoreTexture, textColor,
                                        gRenderer, gFont, score);
                        DrawPlayerHighScore(gText2Texture, gHighScoreTexture,
                                            textColor, gRenderer, gFont,
                                            highscore);
                        DrawPlayerHeath(gText3Texture, gHeathTexture, textColor,
                                        gRenderer, gFont, heath);

                        SDL_RenderPresent(gRenderer);
                    }
                    DrawEndGameSelection(
                        gLoseTexture, gText5Texture, gText6Texture,
                        gYourScoreTexture, &e, gRenderer, textColor2, gFont,
                        Play_Again, Return_Menu, Quit_Menu, score, highscore, gMenuMusic);
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
        gWindow = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                   SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        if (gWindow == NULL) {
            LogError("Can not create window: ", SDL_ERROR);
            success = false;
        } else {
            gRenderer = SDL_CreateRenderer(
                gWindow, -1,
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
    gMenuMusic = Mix_LoadMUS("Music/game_music_backg.mp3");
    if (gMenuMusic == nullptr) {
        cerr << "Failed to load menu sound" << endl;
        success = false;
    }
    gMusic = Mix_LoadMUS("Music/game_play.mp3");
    if (gMenuMusic == nullptr) {
        cerr << "Failed to load play sound" << endl;
        success = false;
    }
    gClick = Mix_LoadWAV("Music/mouse_click.wav");
    if (gClick == nullptr) {
        cerr << "Failed to load click sound" << endl;
        success = false;
    }
    gColu = Mix_LoadWAV("Music/bonk-sound-effect.wav");
    if (gColu == nullptr) {
        cerr << "Failed to load colu sound" << endl;
        success = false;
    }
    gJump = Mix_LoadWAV("Music/Jump.wav");
    if (gJump == nullptr) {
        cerr << "Failed to load jump sound" << endl;
        success = false;
    }
    gLose = Mix_LoadWAV("Music/game_death.wav");
    if (gLose == nullptr) {
        cerr << "Failed to load lose sound" << endl;
        success = false;
    }
    if (!gMenuTexture.LoadFromFile("imgs/Background/game_menu.png",
                                   gRenderer)) {
        cerr << "Failed to load menu image" << endl;
        success = false;
    }

    if (!gInstructionTexture.LoadFromFile("imgs/Background/game_intro.png",
                                          gRenderer)) {
        cerr << "Failed to load instruction image" << endl;
        success = false;
    }
    if (!gBackgroundTexture.LoadFromFile("imgs/Background/game_play.png",
                                         gRenderer)) {
        cerr << "Failed to load gameplay image" << endl;
        success = false;
    }
    if (!gBackgroundTexture2.LoadFromFile("imgs/Background/game_play2.png",
                                         gRenderer)) {
        cerr << "Failed to load gameplay image" << endl;
        success = false;
    }
    if (!gCharacterTexture.LoadFromFile("imgs/Character/Character.png",
                                        gRenderer)) {
        cerr << "Failed to load character image" << endl;
        success = false;
    }
    if (!gLoseTexture.LoadFromFile("imgs/Background/game_lose.png",
                                   gRenderer)) {
        cerr << "Failed to load lose image" << endl;
        success = false;
    }
    gFont = TTF_OpenFont("Font/RobotoCondensed-Regular.ttf", 28);
    if (gFont == NULL) {
        LogError("Failed to load font", MIX_ERROR);
        success = false;
    } else {
        if (!gText1Texture.LoadFromRenderedText("Score: ", gFont, textColor,
                                                gRenderer)) {
            cerr << "Failed to render text1 texture" << endl;
            success = false;
        }
        if (!gText2Texture.LoadFromRenderedText("High: ", gFont, textColor,
                                                gRenderer)) {
            cerr << "Failed to render text2 texture" << endl;
            success = false;
        }
        if (!gText3Texture.LoadFromRenderedText("Heath: ", gFont, textColor,
                                                gRenderer)) {
            cerr << "Failed to render text3 texture" << endl;
            success = false;
        }
        
        if (!gText5Texture.LoadFromRenderedText("Your score : ", gFont,
                                                textColor2, gRenderer)) {
            cerr << "Failed to render text5 texture" << endl;
            success = false;
        }
        if (!gText6Texture.LoadFromRenderedText("Sir's score :  ", gFont,
                                                textColor2, gRenderer)) {
            cerr << "Failed to render text6 texture" << endl;
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
