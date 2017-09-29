#include "entity.h"
#include <math.h>
#include "gf2d_types.h"
#include <SDL.h>


#define entitySize 15


typedef struct 
{
	Entity *EntityList[entitySize];
}EntityMan;

EntityMan entity_manager;

/*
*@ first entity will always be the player
*/
gf2d_entity_init()
{
	int counter = 0;
	for (counter = 0; counter < entitySize; counter++)
	{
		entity_manager.EntityList[counter] = (Entity *)malloc(sizeof(Entity));
		memset(entity_manager.EntityList[counter], 0, sizeof(Entity));
	}
	entity_manager.EntityList[0]->player = 1;

}

int test = 0;


drawEntity(int mf)
{
	Vector4D mouseColor = { 255, 100, 255, 200 };
	int counter = 0;
	

	
	for (counter; counter<entitySize; counter++)
	{
		

		if (entity_manager.EntityList[counter]->inuse == 1)
		{
			entity_manager.EntityList[counter]->img = gf2d_sprite_load_all("images/pointer.png", 32, 32, 16);
			
			if (!test)
			{
				//gf2d_sprite_draw_image(entity_manager.EntityList[counter]->img, vector2d(12, 350));
				test++;
			}
			
			gf2d_sprite_draw(
				entity_manager.EntityList[counter]->img,
				vector2d(entity_manager.EntityList[counter]->pos.x, entity_manager.EntityList[counter]->pos.y),
				NULL,
				NULL,
				NULL,
				NULL,
				NULL,
				mf);
			entity_manager.EntityList[counter]->pos.x += 5;
		}
	}
}

updateEnt()
{
	int mx, my;
	Vector4D mouseColor = { 255, 100, 255, 200 };
	int counter = 1;
	SDL_GetMouseState(&mx, &my);
	for (counter = 1; counter < entitySize;counter++)
	{

		gf2d_rotTransx2(entity_manager.EntityList[counter]);
		
		//gf2d_sprite_draw_image(entity_manager.EntityList[counter]->img, vector2d(250, 300));
	}
	
	entity_manager.EntityList[0]->pos.x = mx;
	entity_manager.EntityList[0]->pos.y = my;

}

Ent_Hit()
{
	int counter;
	for (counter = 1; counter < entitySize; counter++)
	{

		if (entity_manager.EntityList[0]->pos.x >= (entity_manager.EntityList[counter]->pos.x-16)&&
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
	int counter = 1;
	for (counter; counter < entitySize;counter++)
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
*@ memory in the structure
*/
/*
Entity *gf2d_entity_new()
{
	Entity *ent = (Entity *)malloc(sizeof(Entity));
	memset(ent,0,sizeof(Entity));
	
	ent->pos.x = 200 + delta;
	ent->pos.y = 300;
	ent->inuse = 1;
	delta -= 10;
	return ent;
}
*/


/*
*@ frees memory in the structure
*@ sets x = 1 if x = 0
*@ xf=xcostheta-x^2costheta
*@ yf=xcostheta+x^2costheta
*/
void gf2d_rotTransx2(Entity *ent)
{
	double xf, yf;
	ent->time+=.01;
	if (ent->pos.x < 0)ent->pos.x = 1.00;
	if(ent->theta==NULL)ent->theta = atan(ent->pos.y, ent->pos.x);
	xf = ent->time*cos(ent->theta) + ent->time* ent->time*sin(ent->theta) + ent->pos.x;
	yf = ent->time*sin(ent->theta) + ent->time * ent->time*cos(ent->theta) + ent->pos.y;
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

 void gf2d_entity_spawn()
{
	Vector4D mouseColor = { 255, 100, 255, 200 };
	int counter = 0;

	for (counter; counter < entitySize; counter++)
	{
		if (entity_manager.EntityList[counter]->inuse==0)
		{
			entity_manager.EntityList[counter]->img = gf2d_sprite_load_all("images/pointer.png", 32, 32, 16);
			entity_manager.EntityList[counter]->pos.x = 50 + gf2d_random()*100;
			entity_manager.EntityList[counter]->pos.y = 30 + gf2d_random()*150;
			entity_manager.EntityList[counter]->inuse = 1;
			entity_manager.EntityList[counter]->health = 100;
			entity_manager.EntityList[counter]->scale = 1;


			gf2d_sprite_draw_image(entity_manager.EntityList[counter]->img, vector2d(250, 300));
			entity_manager.EntityList[counter]->health = 100;
		}
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
