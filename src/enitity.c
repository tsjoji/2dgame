#include "entity.h"
#include <math.h>
#include "gf2d_types.h"
#include <SDL.h>


#define entitySize 15000


typedef struct
{
	Entity *EntityList[entitySize];
}EntityMan;

EntityMan entity_manager;

/*
*@ first entity will always be the player
*/
void gf2d_entity_init(int boss)
{
	int counter = 0;
	for (counter = 0; counter < entitySize; counter++)
	{
		entity_manager.EntityList[counter] = (Entity *)malloc(sizeof(Entity));
		memset(entity_manager.EntityList[counter], 0, sizeof(Entity));
	}
	entity_manager.EntityList[0]->type = 1;//player
	entity_manager.EntityList[1]->type = 2;//boss
	entity_manager.EntityList[1]->damaging = boss;
}

int test = 0;


void gf2d_entity_spawn()
{
	Vector4D mouseColor = { 255, 100, 255, 200 };
	int counter = 0;

	for (counter; counter < entitySize; counter++)
	{
		if (entity_manager.EntityList[counter]->inuse == 0)
		{
			//entity_manager.EntityList[counter]->img = gf2d_sprite_load_all("images/projectiles/bullet.png", 32, 32, 18);
			entity_manager.EntityList[counter]->pos.x = 50;
			entity_manager.EntityList[counter]->pos.y = 30;
			entity_manager.EntityList[counter]->inuse = 1;
			entity_manager.EntityList[counter]->health = 100;
			entity_manager.EntityList[counter]->scale = 1;
			entity_manager.EntityList[counter]->delta = 0.07;
			entity_manager.EntityList[counter]->maxFrames = 3;
			entity_manager.EntityList[counter]->frame = 0;


			//gf2d_sprite_draw_image(entity_manager.EntityList[counter]->img, vector2d(250, 300));
			entity_manager.EntityList[counter]->health = 100;
		}
		entity_manager.EntityList[0]->maxFrames = 1;
	}

}


void drawEntity(int mf, int boss)
{
	Vector4D mouseColor = { 255, 100, 255, 200 };
	int counter = 0;
	

	for (counter; counter<entitySize; counter++)
	{
		

		if (entity_manager.EntityList[counter]->inuse == 1)
		{

			//player
			if (entity_manager.EntityList[counter]->type == 1)
				entity_manager.EntityList[counter]->img = gf2d_sprite_load_all("images/bosses/player.png", 96, 96, 0);
			//boss
			else if (entity_manager.EntityList[counter]->type == 2)
			{
				if (boss == 1)
				{
					entity_manager.EntityList[counter]->img = gf2d_sprite_load_all("images/bosses/apoc.png", 294, 351, 0);
					entity_manager.EntityList[counter]->maxFrames = 1;
					entity_manager.EntityList[counter]->pos.x = 410;
					entity_manager.EntityList[counter]->pos.y = 50;
				}
					
				else
					entity_manager.EntityList[counter]->img = gf2d_sprite_load_all("images/bosses/sylphfix (w122 h 101).png", 122, 101, 4);
			}
			else 
				entity_manager.EntityList[counter]->img = gf2d_sprite_load_all("images/projectiles/ball_2.png", 102, 115, 3);

			if (!test)
			{
				//gf2d_sprite_draw_image(entity_manager.EntityList[counter]->img, vector2d(12, 350));
				test++;
			}

			entity_manager.EntityList[counter]->frame = entity_manager.EntityList[counter]->frame + entity_manager.EntityList[counter]->delta;
			if (entity_manager.EntityList[counter]->frame>entity_manager.EntityList[counter]->maxFrames)
			{
				entity_manager.EntityList[counter]->frame = 0;
			}
			gf2d_sprite_draw(
				entity_manager.EntityList[counter]->img,
				vector2d(entity_manager.EntityList[counter]->pos.x, entity_manager.EntityList[counter]->pos.y),
				NULL,
				NULL,
				NULL,
				NULL,
				NULL,
				(int)entity_manager.EntityList[counter]->frame);
			entity_manager.EntityList[counter]->pos.x += 5;
		}
	}
}

void updateEnt()
{
	int mx, my;
	Vector4D mouseColor = { 255, 100, 255, 200 };
	int counter;
	SDL_GetMouseState(&mx, &my);
	for (counter = 2; counter < entitySize; counter++)
	{

		gf2d_rotTransx2(entity_manager.EntityList[counter]);

		//gf2d_sprite_draw_image(entity_manager.EntityList[counter]->img, vector2d(250, 300));
	}

	entity_manager.EntityList[0]->pos.x = mx;
	entity_manager.EntityList[0]->pos.y = my;
	entity_manager.EntityList[1]->pos.x = 360;
	entity_manager.EntityList[1]->pos.y = 100;

}

void Ent_Hit()
{
	int counter;
	for (counter = 2; counter < entitySize; counter++)
	{

		if (entity_manager.EntityList[0]->pos.x >= (entity_manager.EntityList[counter]->pos.x - 16) &&
			entity_manager.EntityList[0]->pos.x <= (entity_manager.EntityList[counter]->pos.x + 16) &&
			entity_manager.EntityList[0]->pos.y >= (entity_manager.EntityList[counter]->pos.y - 16) &&
			entity_manager.EntityList[0]->pos.y <= (entity_manager.EntityList[counter]->pos.y + 16)
			)
		{
			gf2d_entity_free_one(counter);
		}


		//gf2d_sprite_draw_image(entity_manager.EntityList[counter]->img, vector2d(250, 300));
	}
}


/*
*@ frees all memory in the structure minus player
*@
*/

void gf2d_entity_free()
{
	int counter = 2;
	for (counter; counter < entitySize; counter++)
	{

		memset(entity_manager.EntityList[counter], 0, sizeof(Entity));
	}

}



/*
*@ frees specific memory in the structure
*@
*/
void gf2d_entity_free_one(int remove)
{

	memset(entity_manager.EntityList[remove], 0, sizeof(Entity));


}





static int delta = 0;
void damageplayer(int dmg)
{
	return;
}

/*
*@ frees memory in the structure
*@ sets x = 1 if x = 0
*@ xf=xcostheta-x^2costheta
*@ yf=xcostheta+x^2costheta
*/
void gf2d_rotTransx2(Entity *ent)
{
	double xf, yf;
	ent->time += .01;
	if (ent->pos.x < 0)ent->pos.x = 1.00;
	if (ent->theta == NULL)ent->theta = atan(ent->pos.y, ent->pos.x);
	xf = (0.98*(ent->time*cos(ent->theta) + ent->time* ent->time*sin(ent->theta) + ent->pos.x)) ;
	yf = (0.98*(ent->time*sin(ent->theta) + ent->time * ent->time*cos(ent->theta) + ent->pos.y))*1.02;
	if (xf < 0 || xf>1150)
	{
		gf2d_entity_free(ent);
	}
	else
	{
		ent->pos.x = xf;
	}
	if (yf < 0 || yf>719)
	{
		gf2d_entity_free(ent);
	}
	else
	{
		ent->pos.y = yf;
	}

}


/*
*@ frees memory in the structure
*@ sets x = 1 if x = 0
*@ xf=xcostheta-x^2costheta
*@ yf=xcostheta+x^2costheta
*/
void gf2d_rotTransx3(Entity *ent)
{
	double xf, yf;
	ent->time += .01;
	if (ent->pos.x < 0)ent->pos.x = 1.00;
	if (ent->theta == NULL)ent->theta = atan(ent->pos.y, ent->pos.x);
	xf = (ent->time*cos(ent->theta) + ent->time* ent->time*sin(ent->theta) + ent->pos.x) + (ent->pos.x*sin(30));
	yf = (ent->time*sin(ent->theta) + ent->time * ent->time*cos(ent->theta) + ent->pos.y) + (ent->pos.y*cos(60));
	ent->theta = ent->theta + 12000;
	if (xf < 0 && xf>1280)
	{
		gf2d_entity_free(ent);
	}
	else
	{
		ent->pos.x = xf;
	}
	if (yf < 0 && yf>1280)
	{
		gf2d_entity_free(ent);
	}
	else
	{
		ent->pos.y = yf;
	}

}



/*
*@sets x = 1 if x = 0
*tan(arccos(x)+arcSin(y))=1
*/
void gf2d_crazyzone(Entity *ent)
{
	if (tan(acos(ent->pos.x) + asin(ent->pos.y) == 1))
	{
		damageplayer(10);//damage player 10 health
	}
}
