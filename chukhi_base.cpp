#include "chukhi_base.h"

void LogError(string msg, ErrorType error_code)
{
	if (error_code == SDL_ERROR)
	{
		cerr << msg << SDL_GetError() << endl;
	}
	if (error_code == IMG_ERROR)
	{
		cerr << msg << IMG_GetError() << endl;
	}
	if (error_code == MIX_ERROR)
	{
		cerr << msg << Mix_GetError() << endl;
	}
	if (error_code == TTF_ERROR)
	{
		cerr << msg << TTF_GetError() << endl;
	}
}
