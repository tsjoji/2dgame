#include <SDL.h>
#include "gf2d_graphics.h"
#include "gf2d_sprite.h"
#include "simple_logger.h"
#include "entity.h"
#include <stdio.h>
#include "gamestate.h"



enum gametype currState = Mainmenu;

gamestate *CurrGamestate;


int main(int argc, char * argv[])
{
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
		


	}
    slog("---==== END ====---");
    return 0;

	
}
/*eol@eof*/
