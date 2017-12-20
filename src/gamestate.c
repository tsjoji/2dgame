#include <SDL.h>
#include "gf2d_graphics.h"
#include "gf2d_sprite.h"
#include "simple_logger.h"
#include "entity.h"
#include <stdio.h>
#include "gameSound.h"
#include "gamestate.h"
#include "ui.h"
#include "physfs.h"



extern enum gametype currState;

extern gamestate *CurrGamestate;

const Uint8 * keys;
int test = 0;
int done = 0;
int reallydone = 0;
int levelSelect = 0;
int spawncontroller = 10;
int aichange;
int aitype = 1;
int playerhealth = 100;
int powerbar = 100;
long biggestamp = 0, timer=0;

const Uint8 * keys;

Sprite *sprite, *sprite1, *deleteme, *startscreen, *endscreen, *optionsScreen;

Sprite *enemy;

Entity *enter, *checker;

int mx, my, boss, endgame;

float mf = 0;

Sprite *mouse;

Vector4D mouseColor = { 255, 100, 255, 200 };

FILE *file;

int lengthofsong;

double starttime, currtime;

extern long deltatime;

SDL_Joystick* gGameController = NULL;

//Event handler
SDL_Event e;

//Normalized direction
int xDir = 0;
int yDir = 0;
int abutton = 0;
int bbutton = 0;
int xbutton = 0;
int startbutton = 0;
int leftclick = 0;
int lastclickstate = 0;

float maingamevolume = 128;
//Analog joystick dead zone
const int JOYSTICK_DEAD_ZONE = 8000;

int controller = 1;
/*program initializtion*/

int slowdownsong = 0;
/*demo setup*/

int title = 1;

extern int WentToOptions, changedSize, Sizenowis, UseCustomSong, Continuesong;

char sizetype[10];
char resumelocation[10];


void setup()
{
	FILE *fp;
	
	fp = fopen("data.config", "r");
	if (fp)
	{

		fscanf(fp, "%s", sizetype);
		fscanf(fp, "%s", resumelocation);
		fclose(fp);
	}
	else
	{
		
		PHYSFS_init(NULL);
		PHYSFS_addToSearchPath("data.zip", 1);
		PHYSFS_file* myfile = PHYSFS_openRead("data.config");
		char myBuf[60];
		memset(myBuf, '\0', 60);
		PHYSFS_read(myfile, myBuf, 1, PHYSFS_fileLength(myfile));
		PHYSFS_close(myfile);
		PHYSFS_deinit();
		fp = fopen("data.config", "w");
		fprintf(fp, "%s", myBuf);
		fclose(fp);
		fscanf(fp, "%s", sizetype);
		fscanf(fp, "%s", resumelocation);
		fclose(fp);
	}
	


	if ((atoi(sizetype) == 1))
	{
		init_logger("gf2d.log");
		slog("---==== BEGIN ====---");
		gf2d_graphics_initialize(
			"fool's logic",
			1200,
			720,
			1200,
			720,
			vector4d(0, 0, 0, 255),
			0);
	}
	if ((atoi(sizetype) == 0))
	{
		init_logger("gf2d.log");
		slog("---==== BEGIN ====---");
		gf2d_graphics_initialize(
			"fool's logic",
			900,
			600,
			900,
			600,
			vector4d(0, 0, 0, 255),
			0);
	}
	gf2d_graphics_set_frame_delay(16);
	gf2d_sprite_init(1024);
	SDL_ShowCursor(SDL_DISABLE);

	endscreen = gf2d_sprite_load_image("images/backgrounds/end screen.png");
	startscreen = gf2d_sprite_load_image("images/backgrounds/foolsLogic.jpg");
	optionsScreen = gf2d_sprite_load_image("images/backgrounds/optionsmenu.jpg");


	if (SDL_NumJoysticks() < 1)
	{
		controller = 0;
	}
	else
	{
		//Load joystick
		gGameController = SDL_JoystickOpen(0);
		if (gGameController == NULL)
		{
			controller = 0;
		}
	}
	
	if (SDL_Init(SDL_INIT_JOYSTICK) < 0)
	{
		controller = 0;
	}
}




void MainMenuInput()
{
	
	abutton = 0;
	bbutton = 0;
	xbutton = 0;
	startbutton = 0;
	
	
	
	
	SDL_PumpEvents();   // update SDL's internal event structures

	keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			leftclick = 1;
		}
		if (e.type==SDL_MOUSEBUTTONUP)
			leftclick = 0;

		if (e.type == SDL_KEYDOWN)
		{
			if (keys[SDL_SCANCODE_E])
			{
				abutton = 1;
			}
			if (keys[SDL_SCANCODE_W])
			{
				bbutton = 1;
			}
			if (keys[SDL_SCANCODE_Q])
			{
				xbutton = 1;
			}

	}	

		if (e.type == SDL_JOYBUTTONDOWN)
		{
			if (e.jbutton.button == 0)
			{
				abutton = 1;
			}
			if (e.jbutton.button == 1)
			{
				bbutton = 1;
			}
			if (e.jbutton.button == 2)
			{
				xbutton = 1;
			}
			if (e.jbutton.button == 3)
			{

			}
			if (e.jbutton.button == 6)
			{

			}
			if (e.jbutton.button == 7)
			{
				startbutton = 1;
			}
			//a=0;b=1;x=2;y=3;back=6;start=7
		}
		//slog("the button is %d",SDL_JOYBUTTONDOWN);
		if (e.type == SDL_JOYAXISMOTION)
		{
			//Motion on controller 0
			if (e.jaxis.which == 0)
			{
				//X axis motion
				if (e.jaxis.axis == 0)
				{
					//Left of dead zone
					if (e.jaxis.value < -JOYSTICK_DEAD_ZONE)
					{
						xDir = -1;
						//printf("\nnegative x");
					}
					//Right of dead zone
					else if (e.jaxis.value > JOYSTICK_DEAD_ZONE)
					{
						xDir = 1;
						//printf("\npositive x");
					}
					else
					{
						xDir = 0;
						//printf("\nno x");
					}
				}
				if (e.jaxis.axis == 1)
				{
					//Below of dead zone
					if (e.jaxis.value < -JOYSTICK_DEAD_ZONE)
					{
						yDir = -1;
						//printf("\down y");
					}
					//Above of dead zone
					else if (e.jaxis.value > JOYSTICK_DEAD_ZONE)
					{
						yDir = 1;
						//printf("\nup y");
					}
					else
					{
						yDir = 0;
						//printf("\nno y");
					}
				}
			}
		}
	}

}

void MainMenuUpdate()
{
	FILE *fp;
	static int location = 0;
	
	
	if (keys[SDL_SCANCODE_RETURN]||startbutton)
	{
		fp = fopen("data.config", "w");
		fprintf(fp, "%d\n", atoi(sizetype));
		
		gf2d_graphics_clear_screen();// clears drawing buffers
		if (UseCustomSong)
		file = fopen("test2.wav", "rb");
		else
		file = fopen("test3.wav", "rb");


		resetAI();

		init_UI();

		//end loading

		boss = selectlevel();//select the level

		fseek(file, 0, SEEK_SET);

		biggestamp = Soundinfo(file);

		gf2d_entity_init(boss, biggestamp);

		lengthofsong = timeofsong();


		timer = lengthofsong*1000;
		
		SoundVolume();

		endgame = 0;

		starttime = SDL_GetTicks();
		
		aichange = lengthofsong / numchuncks();
		
		if (UseCustomSong)
		Soundinit("test2.wav");//init the sound
		else
		Soundinit("test3.wav");//init the sound

		void gf2d_entity_init(int boss, long amplitude);

		currState = Game;
		
		if (Continuesong)
		{
			fprintf(fp, "%d", 0);
			timer = (atoi(resumelocation) * 1000);
			fastforward(timer);
			
		}
		else
		{
			fprintf(fp, "%d", atoi(resumelocation));
		}
		fclose(fp);



	}
		
	if (keys[SDL_SCANCODE_ESCAPE])
	{
		exit(1);
	}

	if (bbutton)
	{
		title=0;
	}

}


void MainMenuDraw()
{
	
	// all drawing should happen betweem clear_screen and next_frame
	//backgrounds drawn first
	gf2d_graphics_clear_screen();
	if (title)
	gf2d_sprite_draw_image(startscreen, vector2d(0, 0));
	else
	{
		gf2d_sprite_draw_image(optionsScreen, vector2d(0, 0));
		maingamevolume=drawMainmenu_UI(leftclick);
	}
	
	gf2d_grahics_next_frame();// render current draw frame and skip to the next frame
	gf2d_graphics_clear_screen();// clears drawing buffers
}

void MainGameInput()
{
	abutton = 0;
	bbutton = 0;
	xbutton = 0;
	startbutton = 0;

	
	SDL_PumpEvents();   // update SDL's internal event structures

	keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_KEYDOWN)
		{
			if (keys[SDL_SCANCODE_E])
			{
				abutton = 1;
			}
			if (keys[SDL_SCANCODE_W])
			{
				bbutton = 1;
			}
			if (keys[SDL_SCANCODE_Q])
			{
				xbutton = 1;
			}

		}

		if (e.type == SDL_JOYBUTTONDOWN)
		{
			if (e.jbutton.button == 0)
			{
				abutton = 1;
			}
			if (e.jbutton.button == 1)
			{
				bbutton = 1;
			}
			if (e.jbutton.button == 2)
			{
				xbutton = 1;
			}
			if (e.jbutton.button == 3)
			{

			}
			if (e.jbutton.button == 6)
			{

			}
			if (e.jbutton.button == 7)
			{
				startbutton = 1;
			}
			//a=0;b=1;x=2;y=3;back=6;start=7
		}
		//slog("the button is %d",SDL_JOYBUTTONDOWN);
		if (e.type == SDL_JOYAXISMOTION)
		{
			//Motion on controller 0
			if (e.jaxis.which == 0)
			{
				//X axis motion
				if (e.jaxis.axis == 0)
				{
					//Left of dead zone
					if (e.jaxis.value < -JOYSTICK_DEAD_ZONE)
					{
						xDir = -1;
						//printf("\nnegative x");
					}
					//Right of dead zone
					else if (e.jaxis.value > JOYSTICK_DEAD_ZONE)
					{
						xDir = 1;
						//printf("\npositive x");
					}
					else
					{
						xDir = 0;
						//printf("\nno x");
					}
				}
				if (e.jaxis.axis == 1)
				{
					//Below of dead zone
					if (e.jaxis.value < -JOYSTICK_DEAD_ZONE)
					{
						yDir = -1;
						//printf("\down y");
					}
					//Above of dead zone
					else if (e.jaxis.value > JOYSTICK_DEAD_ZONE)
					{
						yDir = 1;
						//printf("\nup y");
					}
					else
					{
						yDir = 0;
						//printf("\nno y");
					}
				}
			}
		}
	}
	
}

int firsttime = 1;
void MainGameUpdate()
{
	FILE *fp;
	int enoughpower, lastloc;
	if (keys[SDL_SCANCODE_BACKSPACE] || startbutton)
	{
		Soundclose();

		aichange = 0;
		
		aitype = 1;

		gf2d_entity_free();
		currtime = 0;
		starttime = 0;
		
		currState = Loser;
		
		lastloc = (int)(timer / 1000);
		
		



		fp = fopen("data.config", "w");
		fprintf(fp, "%d\n", atoi(sizetype));
		fprintf(fp, "%d", lastloc);
		fclose(fp);
		timer = 0;
		Continuesong = 0;
		itoa(lastloc, resumelocation,10);
		return;
	}
	if (keys[SDL_SCANCODE_ESCAPE])
	{
		Soundclose();



		aichange = 0;
		timer = 0;
		aitype = 1;

		gf2d_entity_free();
		currtime = 0;
		starttime = 0;
		exit(1);
	}

	SoundVolume((int)maingamevolume);
	if (!firsttime)
	timer = timer - deltatime;
	firsttime = 0;

	mf += 0.1;
	if (mf >= 21.0)
	{
		mf = 0;

	}
	if (spawncontroller>10)
	{
		spawncontroller = 0;
		gf2d_entity_spawn(aitype);
	}
	spawncontroller += 7;

	updateEnt();

	playerhealth = Ent_Hit();
	
	powerbar = getPowerbar();

	regen();

	if (abutton )
	{
		killallbubbles();
	}
	if (bbutton)
	{
		smallcircle();
	}
	if (xbutton )
	{
		double times = lengthofsong - (timer / 1000);
		enoughpower= reposong(times);
		if (enoughpower)
		{
			timer -= 30000;
		}
	}



	if (playerhealth < 0)
	{
		currState = Loser;
	}

	if (controller)
		updateplayer(xDir, yDir);
	else
		updateplayermouse();

	if (timer == 0 && endgame == 0)
	{
		Soundinit2();
		endgame = 1;
	}

	if (playerhealth < 3000)
	{
		slowdownsong = 0;
		audiospeedchange(slowdownsong, (double)(lengthofsong - timer / 1000));
	}
	else
	{
		slowdownsong = 1;
		audiospeedchange(slowdownsong, (double)(lengthofsong - timer / 1000));

	}
	


	

	if ((lengthofsong-(timer/1000)) > aichange)
	{
		
		
		randompowerup();
		aichange = aichange + (lengthofsong / numchuncks());
		aitype++;
		//if (aitype > 2)
			//returnspeed();
		if (aitype == 3 && boss != 1)
		{
			aitype++;
		}
		if (aitype > 4)
			aitype = 2;


	}


	
	

	if ((int)(timer/1000) < -7)
	{
		Soundclose();

		aichange = 0;
		timer = 0;
		aitype = 1;

		gf2d_entity_free();
		currtime = 0;
		starttime = 0;
		currState = Loser;//change this when get a winnner
	}

}

void MainGameDraw()
{
	
	gf2d_graphics_clear_screen();// clears drawing buffers

	loadlevel();

	playerhealth= Ent_Hit();

	drawEntity((int)mf, boss, endgame);


	draw_UI(playerhealth, powerbar);
	
	draw_text((int)(timer / 1000));

	gf2d_grahics_next_frame();// render current draw frame and skip to the next frame
}

void LoserInput()
{

	abutton = 0;
	bbutton = 0;
	xbutton = 0;
	startbutton = 0;

	SDL_PumpEvents();   // update SDL's internal event structures
	keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_JOYBUTTONDOWN)
		{
			if (e.jbutton.button == 0)
			{
				abutton = 1;
			}
			if (e.jbutton.button == 1)
			{
				bbutton = 1;
			}
			if (e.jbutton.button == 2)
			{
				xbutton = 1;
			}
			if (e.jbutton.button == 3)
			{

			}
			if (e.jbutton.button == 6)
			{

			}
			if (e.jbutton.button == 7)
			{
				startbutton = 1;
			}
			//a=0;b=1;x=2;y=3;back=6;start=7
		}
	}
}

void LoserUpdate()
{
	if (keys[SDL_SCANCODE_TAB]||startbutton)
	{
		fclose(file);
		Soundclose();

		currState = Mainmenu;
	}


	if (keys[SDL_SCANCODE_ESCAPE]||abutton)
		exit(1);
}

void LoserDraw()
{
	gf2d_graphics_clear_screen();// clears drawing buffers

	gf2d_sprite_draw_image(endscreen, vector2d(0, 0));


	gf2d_grahics_next_frame();// render current draw frame and skip to the next frame


}



