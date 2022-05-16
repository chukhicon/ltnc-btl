#include "chukhi_base.h"


SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;
/*SDL_Color textColor = { 0, 0, 0 };
TTF_Font* gFont = nullptr;
Mix_Music* gMusic = nullptr;
Mix_Music* gMenuMusic = nullptr;
Mix_Chunk* gClick = nullptr;
Mix_Chunk* gBom = nullptr;
Mix_Chunk* gLose = nullptr;

LTexture gTextTexture;

Button PlayButton(PLAY_BUTON_POSX, PLAY_BUTTON_POSY);
Button HelpButton(HELP_BUTTON_POSX, HELP_BUTTON_POSY);*/

bool quit_menu=false, play_again=false, Quit_Game = false;

/*SDL_Rect gPlayButton[BUTTON_TOTAL];
SDL_Rect gExitButton[BUTTON_TOTAL];
SDL_Rect gBackButton[BUTTON_TOTAL];
SDL_Rect gPauseButton[BUTTON_TOTAL];
SDL_Rect gContinueButton[BUTTON_TOTAL];
SDL_Rect gPlayAgainButton[BUTTON_TOTAL];
SDL_Rect gCharacterClips[RUNNING_FRAMES];
SDL_Rect gEnemyClips[FLYING_FRAMES];*/
/*SDL_Window* window;
SDL_Renderer* renderer;
SDL_Surface *screen;
SDL_Surface *image;*/

int random(int N)
{
    return rand()%N;
}




int main(int argc, char* argv[])
{
    srand(time(NULL));
    initSDL();


    const int step=50;
    if(!initSDL)
    {
        cout << "load init loi roi !!" << endl;
    }
    else
    {
        if(!loadMedia())
        {
            cout << "load media failed" << endl;
        }
        else{
            SDL_Texture* background = loadTexture("imgs\Background\game_menu.png", renderer);
            SDL_RenderCopy( gRenderer, background, NULL, NULL);

            /*Mix_PlayMusic(gMenuMusic, IS_REPEATITIVE);
            while (!Quit_Menu)
			{
				SDL_Event e_mouse;
				while (SDL_PollEvent(&e_mouse) != 0)
				{
					if (e_mouse.type == SDL_QUIT)
					{
						Quit_Menu = true;
					}
					HandlePlayButton(&e_mouse, PlayButton, Quit_Menu, Play_Again, gClick);


					HandleExitButton(&e_mouse, ExitButton, Quit_Menu, gClick);

					if (Quit_Game == true)
					{
						return 0;
					}
				}

				gMenuTexture.Render(0, 0, gRenderer);

				SDL_Rect* currentClip_Play = &gPlayButton[PlayButton.currentSprite];
				PlayButton.Render(currentClip_Play, gRenderer, gPlayButtonTexture);

				SDL_Rect* currentClip_Exit = &gExitButton[ExitButton.currentSprite];
				ExitButton.Render(currentClip_Exit, gRenderer, gExitButtonTexture);

				SDL_RenderPresent(gRenderer);*/
			}

        }
    }
    /*SDL_Event e;
    while(true){
        if(SDL_WaitEvent(&e)==0)SDL_Delay(100);
        else if (e.type==SDL_QUIT)break;
        else if (e.type==SDL_KEYDOWN){
            cerr<<"_" << SDL_GetKeyName(e.key.keysym.sym) << "_" << endl;
            switch(e.key.keysym.sym){
                case SDLK_u:
            case SDLK_UP: y-=step; break;
            case SDLK_m:
            case SDLK_DOWN: y+=step; break;
            case SDLK_h:
            case SDLK_LEFT: x-=step; break;
            case SDLK_k:
            case SDLK_RIGHT: x+=step; break;
            }

            draw(renderer, x, y);
        }
    }

    close();
*/
    return 0;
}
bool initSDL() {
    bool success=true;
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        logError("Failed to init SDL", SDL_ERROR);
        success = false;
    }
    else
    {
        gWindow = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                   SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        if (gWindow == NULL)
        {
            logError("Can not create window: ", SDL_ERROR);
            success = false;
        }
        else
        {
            gRenderer = SDL_CreateRenderer(gWindow, -1,
                                           SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (gRenderer == NULL) {
                logError("Can not create renderer: ", SDL_ERROR);
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                if (!IMG_Init(IMG_INIT_PNG))
                {
                    logError("Can not initialize SDL_image: ", IMG_ERROR);
                    success = false;
                }

                if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
                {
                    logError("Can not initialize audio: ", MIX_ERROR);
                    success = false;
                }

                if (TTF_Init() < 0)
                {
                    logError("Can not initialize font: ", TTF_ERROR);
                    success = false ;
                }
            }
        }
    }
    return success;
}
void loadMedia()
{

}
void close()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
SDL_Texture* loadTexture( string path, SDL_Renderer* renderer )
{
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if ( loadedSurface == nullptr )
        cout << "Unable to load image " << path << " SDL_image Error: "
             << IMG_GetError() << endl;
    else {
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == nullptr )
            cout << "Unable to create texture from " << path << " SDL Error: "
                 << SDL_GetError() << endl;
        SDL_FreeSurface( loadedSurface );
    }
    return newTexture;
}

