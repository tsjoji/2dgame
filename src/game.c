#include <SDL.h>
#include "gf2d_graphics.h"
#include "gf2d_sprite.h"
#include "simple_logger.h"
#include "entity.h"
#include <stdio.h>

int main(int argc, char * argv[])
{
    /*variable declarations*/
	int test = 0;
	int done = 0;
	int reallydone = 0;
	int levelSelect = 0;
	int spawncontroller = 10;
	int aichange, timer;
	int aitype=1;
	
	const Uint8 * keys;
	Sprite *sprite, *sprite1, *deleteme,*startscreen, *endscreen;
	Sprite *enemy;
	Entity *enter, *checker;

    int mx,my, counter, boss;
    float mf = 0;
    Sprite *mouse;
    Vector4D mouseColor = {255,100,255,200};
    
	FILE *file;
	int lengthofsong;
	double starttime, currtime;
	counter = 0;
	

    /*program initializtion*/
    init_logger("gf2d.log");
    slog("---==== BEGIN ====---");
    gf2d_graphics_initialize(
        "gf2d",
        1200,
        720,
        1200,
        720,
        vector4d(0,0,0,255),
        0);
    gf2d_graphics_set_frame_delay(16);
    gf2d_sprite_init(1024);
    SDL_ShowCursor(SDL_DISABLE);
    
    /*demo setup*/
    
    mouse = gf2d_sprite_load_all("images/pointer.png",32,32,16);
	startscreen = gf2d_sprite_load_image("images/backgrounds/foolsLogic.jpg");

	endscreen = gf2d_sprite_load_image("images/backgrounds/end screen.png");
	//enemy = gf2d_sprite_load_all("images/pointer.png", 32, 32, 16);
    /*main game loop*/
	
	deleteme = gf2d_sprite_load_image("images/ui/health bar.png");

	
	//setup test entity 
	//update entity
	int done1 = 0;
	while (1)
	{

		while (!done1)
		{
			SDL_PumpEvents();   // update SDL's internal event structures
			keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
			gf2d_graphics_clear_screen();// clears drawing buffers

			// all drawing should happen betweem clear_screen and next_frame
			//backgrounds drawn first

			gf2d_graphics_clear_screen();
			gf2d_sprite_draw_image(startscreen, vector2d(0, 0));




			gf2d_grahics_next_frame();// render current draw frame and skip to the next frame

			if (keys[SDL_SCANCODE_RETURN])done1 = 1; // exit condition
			if (keys[SDL_SCANCODE_ESCAPE])
			{
				reallydone = 1;
				break;
			}
		}
		if (reallydone)
		{
			break;
		}

		//change this up put in a c file just dont know what to do with it
			
	    
		//Soundinit();

		//load the level
		init_UI();
		
		
		Soundinit();//init the sound
		//end loading
		
		boss = selectlevel();//select the level



		gf2d_entity_init(boss, 230000);

		
		file = fopen("test2.wav","rb");
		Soundinfo(file);

		lengthofsong = timeofsong();

		SoundVolume();

		
		starttime = SDL_GetTicks();
		aichange= lengthofsong/numchuncks();
		while (!done)
		{
			SDL_PumpEvents();   // update SDL's internal event structures
			keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
			/*update things here*/
			SDL_GetMouseState(&mx, &my);
			mf += 0.1;
			if (mf >= 21.0)
			{
				mf = 0;

			}


			gf2d_graphics_clear_screen();// clears drawing buffers
			// all drawing should happen betweem clear_screen and next_frame
			//backgrounds drawn first





			//gf2d_sprite_draw_image(sprite, vector2d(0, 0));
			loadlevel();


			//gf2d_sprite_draw_image(deleteme, vector2d(50, 25));

			//gf2d_sprite_draw_image(enemy, vector2d(0, 0));




			if (spawncontroller==10)
			{
				spawncontroller = 0;
			    gf2d_entity_spawn(aitype);
	     	}
			spawncontroller++;
			
				updateEnt();
			
			

			drawEntity((int)mf, boss);

			Ent_Hit();

			//UI elements last
			draw_UI(0.3);


			currtime = SDL_GetTicks();
			draw_text((int)(lengthofsong-(currtime-starttime)/1000));

			timer = (int)((currtime - starttime) / 1000);
			slog("%i", timer);
			if (timer > aichange)
			{
				aichange = aichange + (lengthofsong / numchuncks());
				aitype++;
				if (aitype == 3 && boss != 1)
				{
					aitype++;
				}
				if (aitype > 4)
					aitype = 2;

			}

			gf2d_grahics_next_frame();// render current draw frame and skip to the next frame

			if (keys[SDL_SCANCODE_BACKSPACE])done = 1; // exit condition			
			
			slog("Rendering at %f FPS", gf2d_graphics_get_frames_per_second());
			if (keys[SDL_SCANCODE_ESCAPE])
			{
				reallydone = 1;
				break;
			}

		}
		done = 0;
		done1 = 0;

		if (reallydone)
		{
			break;
		}

		
		aichange = 0;
		timer = 0;
		aitype = 1;
		Soundclose();
		gf2d_entity_free();

		while (!done)
		{
			SDL_PumpEvents();   // update SDL's internal event structures
			keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
			gf2d_graphics_clear_screen();// clears drawing buffers

			// all drawing should happen betweem clear_screen and next_frame
			//backgrounds drawn first

			gf2d_graphics_clear_screen();
			gf2d_sprite_draw_image(endscreen, vector2d(0, 0));


			gf2d_grahics_next_frame();// render current draw frame and skip to the next frame

			if (keys[SDL_SCANCODE_TAB])done = 1; // exit condition
			
			
			if (keys[SDL_SCANCODE_ESCAPE])
			{
				reallydone = 1;
				break;
			}
		
		}
		done = 0;

		if (reallydone)
		{
			break;
		}
	}
    slog("---==== END ====---");
    return 0;

	
}
/*eol@eof*/
