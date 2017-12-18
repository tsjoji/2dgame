#include <SDL.h>
#include "gf2d_graphics.h"
#include "gf2d_sprite.h"
#include "simple_logger.h"
#include <SDL_ttf.h>
#include "gf2d_vector.h"

Sprite *healthbar, *design, *PressStart, *powerbar;

static float mframe = 0.0;


void init_UI()
{
	design = gf2d_sprite_load_image("images/ui/health bar.png");
	TTF_Init();
	
}

void draw_text(int time)
{
	int texW = 0;
	int texH = 0;
	char buffer[7];
	SDL_Rect dstrect = { 1000, 0, texW, texH };


	itoa(time, buffer, 10);
	TTF_Font * font = TTF_OpenFont("arial.ttf", 40);
	SDL_Color color = { 30, 100, 240 };
	SDL_Surface * surface = TTF_RenderText_Solid(font, buffer, color);
	SDL_Texture * texture = SDL_CreateTextureFromSurface(gf2d_graphics_get_renderer(), surface);

	

	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
	
	dstrect.w = texW;
	dstrect.h = texH;
	SDL_RenderCopy(gf2d_graphics_get_renderer(), texture, NULL, &dstrect);
	SDL_RenderPresent(gf2d_graphics_get_renderer);


	TTF_CloseFont(font);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
	memset(buffer, 0, sizeof(buffer));
}


void draw_UI(int playerhealth, int powerbar)
{
	double width = (double)playerhealth/10000;
	double width2 = (double)powerbar / 10000;
	Vector2D scale = vector2d(width, 1.0);
	Vector2D scale2 = vector2d(width2, 1.0);
	//slog("your health is cuurently %f/210", width);
	if (width > 1)
		width = 1;
	if (width2 > 1)
		width2 = 1;
	healthbar = gf2d_sprite_load_all("images/ui/life.png", 210, 24, 1);
	gf2d_sprite_draw(healthbar,
		vector2d(100,28),
		&scale,
		NULL,
		NULL,
		NULL,
		NULL,
		0);
	powerbar = gf2d_sprite_load_all("images/ui/green bar.png", 213, 30, 1);
	gf2d_sprite_draw(powerbar,
		vector2d(94, 45),
		&scale2,
		NULL,
		NULL,
		NULL,
		NULL,
		0);
	
	gf2d_sprite_draw_image(design, vector2d(50, 25));



	PressStart = gf2d_sprite_load_all("images/ui/Press Escape.png", 400, 100, 2);
	
	mframe += 0.025;
	
	if (mframe > 2.0)
		mframe = 0;

	gf2d_sprite_draw(PressStart,
		vector2d(400, 0),
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		(int)mframe);

}

void drawMainmenu_UI()
{
	int texW = 0;
	int texH = 0;
	char buffer[7];
	SDL_Rect dstrect = { 1000, 0, texW, texH };


	itoa(400, buffer, 10);
	TTF_Font * font = TTF_OpenFont("arial.ttf", 40);
	SDL_Color color = { 30, 100, 240 };
	SDL_Surface * surface = TTF_RenderText_Solid(font, buffer, color);
	SDL_Texture * texture = SDL_CreateTextureFromSurface(gf2d_graphics_get_renderer(), surface);



	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);

	dstrect.w = texW;
	dstrect.h = texH;
	SDL_RenderCopy(gf2d_graphics_get_renderer(), texture, NULL, &dstrect);
	SDL_RenderPresent(gf2d_graphics_get_renderer);


	TTF_CloseFont(font);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
	memset(buffer, 0, sizeof(buffer));




}