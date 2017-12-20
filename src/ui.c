#include <SDL.h>
#include "gf2d_graphics.h"
#include "gf2d_sprite.h"
#include "simple_logger.h"
#include <SDL_ttf.h>
#include "gf2d_vector.h"
#include "ui.h"

Sprite *healthbar, *design, *PressStart, *powerbar;

static float mframe = 0.0;

extern int lastclickstate;

extern char sizetype[10];
int WentToOptions = 0, changedSize = 0, Sizenowis = 1, UseCustomSong = 1, Continuesong = 0;

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
	double width = (double)playerhealth / 10000;
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
		vector2d(100, 28),
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



float drawMainmenu_UI(int leftclick)
{

	Sprite * customsong, *songa, *smallmenu, *bigmenu,*continuesong, *horbar, *vertbar, *mouse;
	int mx, my, custOn = 0, songaOn = 0, smalmenuOn = 0, bigON = 0, contsongON = 0;
	float volume;
	static int xposbar=600;//100 min 600 max
	
	WentToOptions = 1;
	SDL_GetMouseState(&mx, &my);
	if (leftclick)
		lastclickstate = 1;
	else
		lastclickstate = 0;
	//left
	if (mx <= 806 && mx >= 550&&leftclick)
	{
		if (my >= 100 && my <= 170)
		{
			custOn = 1;
		}
		
		if (my >= 240 && my <= 310)
		{
			changedSize = 1;
			Sizenowis = 0;
			bigON = 1;
			sizetype[0] = '1';
		}
	}
	//right 
	if (mx <= 406 && mx >= 150&&leftclick)
	{
		if (my >= 100 && my <= 170)
		{
			UseCustomSong = 0;
			songaOn = 1;
		}
		
		if (my >= 240 && my <= 310)
		{
			changedSize = 1;
			Sizenowis = 1;
			smalmenuOn = 1;
			sizetype[0] = '0';
		}
		
	}
	//continue
	if (mx >= 350 && mx <= 600&&my>=600&&my<=650&&leftclick)
	{
		Continuesong = 1;
		contsongON = 1;
	}
	//the bar
	if (lastclickstate == 1 && mx >= 100 && mx <= 600&& my>=400&& my<=500)
	{
		xposbar = mx;
	}

	customsong=gf2d_sprite_load_all("images/ui/custsong.png", 256, 64, 1);
	gf2d_sprite_draw(customsong,
		vector2d(600, 100),
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		custOn);
	songa = gf2d_sprite_load_all("images/ui/songa.png", 256, 64, 1);
	gf2d_sprite_draw(songa,
		vector2d(200, 100),
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		songaOn);
	smallmenu = gf2d_sprite_load_all("images/ui/smallwindow.png", 256, 64, 1);
	gf2d_sprite_draw(smallmenu,
		vector2d(200, 250),
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		smalmenuOn);
	bigmenu = gf2d_sprite_load_all("images/ui/bigwindow.png", 256, 64, 1);
	gf2d_sprite_draw(bigmenu,
		vector2d(600, 250),
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		bigON);
	continuesong = gf2d_sprite_load_all("images/ui/continue.png", 256, 64, 1);
	gf2d_sprite_draw(continuesong,
		vector2d(400, 600),
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		contsongON);
	horbar = gf2d_sprite_load_all("images/ui/barhor.png", 500, 64, 1);
	gf2d_sprite_draw(horbar,
		vector2d(275, 400),
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		0);
	
	vertbar = gf2d_sprite_load_all("images/ui/barver.png", 256, 100, 1);
	gf2d_sprite_draw(vertbar,
		vector2d(xposbar, 390),
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		0);
		
	mouse = gf2d_sprite_load_all("images/bosses/player.png", 96, 96, 0);
	gf2d_sprite_draw(mouse,
		vector2d(mx,my),
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		0);

	volume = (((xposbar - 100) / 500.0)*128);
	return volume;
	
}