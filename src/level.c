#include "level.h"

int selectlevel()
{
	levelSelect = rand() %3;
	return levelSelect;
}



void loadlevel()
{
	if (levelSelect==0)
	{
		
		sprite = gf2d_sprite_load_image("images/backgrounds/lavaWorld.jpg");
		sprite1 = gf2d_sprite_load_image("images/backgrounds/lavaWorld.jpg");
		gf2d_sprite_draw_image(sprite, vector2d(0, 0+delta));
		gf2d_sprite_draw_image(sprite1, vector2d(0,delta-Length));
		delta++;


	}
	if (levelSelect ==1 )
	{
		sprite = gf2d_sprite_load_image("images/backgrounds/postApocDontMove.jpg");
		gf2d_sprite_draw_image(sprite, vector2d(0, 0));

	}
	if (levelSelect == 2)
	{
		sprite = gf2d_sprite_load_image("images/backgrounds/skyLevel.png");
		sprite1 = gf2d_sprite_load_image("images/backgrounds/skyLevel.png");
		gf2d_sprite_draw_image(sprite, vector2d(0, 0+delta));
		gf2d_sprite_draw_image(sprite1, vector2d(0, delta - Length));
		delta++;
	}
	if (delta == Length)
		delta = 0;
}


