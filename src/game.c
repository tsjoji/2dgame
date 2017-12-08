#include <SDL.h>
#include "gf2d_graphics.h"
#include "gf2d_sprite.h"
#include "simple_logger.h"
#include "entity.h"
#include <stdio.h>
#include "gamestate.h"
#include <windows.h>


enum gametype currState = Mainmenu;

gamestate *CurrGamestate;

long deltatime = 0;

#ifdef DEBUG
int main(int argc, char * argv[])
#elif RELEASE
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
#endif
{
	long lastTime = SDL_GetTicks(),currTime;
	setup();
	
	CurrGamestate = malloc(sizeof(gamestate));


	while (1)
	{
		if (currState == Mainmenu)
		{
			CurrGamestate->input = MainMenuInput;
			CurrGamestate->update = MainMenuUpdate;
			CurrGamestate->draw = MainMenuDraw;
		}
		if (currState == Game)
		{
			CurrGamestate->input = MainGameInput;
			CurrGamestate->update = MainGameUpdate;
			CurrGamestate->draw = MainGameDraw;
		}
		if (currState == Loser)
		{
			CurrGamestate->input = LoserInput;
			CurrGamestate->update = LoserUpdate;
			CurrGamestate->draw = LoserDraw;
		}

		(*CurrGamestate->input)();
		(*CurrGamestate->update)();
		(*CurrGamestate->draw)();
		currTime = SDL_GetTicks();
		deltatime = currTime - lastTime;
		lastTime = currTime;


	}
    slog("---==== END ====---");
    return 0;

	
}
/*eol@eof*/
