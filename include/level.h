#include <SDL.h>
#include "gf2d_graphics.h"
#include "gf2d_sprite.h"
#include "simple_logger.h"
#include <math.h>


#define Length 720


int levelSelect, delta;
Sprite *sprite, *sprite1;


/*
*@brief selects the level
*@param void
*@returns int
*/
int selectlevel();

/*
*@brief loads the level world assets
*@param void
*@returns void
*/
void loadlevel();