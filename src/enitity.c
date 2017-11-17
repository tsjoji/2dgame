#include "entity.h"
#include <math.h>
#include "gf2d_types.h"
#include <SDL.h>
#include "simple_logger.h"


#define entitySize 1500

#define deltamove 1
#define deltamax 360
#define AI2_leftx 260
#define AI2_rightx 800
#define AI2_y 100



#define AI3_y 200
#define AI3_y2 400
#define AI3_x 10



int AI2_speed=0;
int signx = 0;
int signy = 1;
int spawner_x, spawner_y;
double deltax = deltamax;
double deltay = 0;
int AI_Type;

typedef struct
{
	Entity *EntityList[entitySize];
}EntityMan;

EntityMan entity_manager;

/*
*@ first entity will always be the player
*/
void gf2d_entity_init(int boss, long amplitude)
{
	int modulation = 17;
	int counter = 0;
	for (counter = 0; counter < entitySize; counter++)
	{
		entity_manager.EntityList[counter] = (Entity *)malloc(sizeof(Entity));
		memset(entity_manager.EntityList[counter], 0, sizeof(Entity));
	}
	entity_manager.EntityList[0]->type = player;//player
	entity_manager.EntityList[1]->type = Boss;//boss
	entity_manager.EntityList[1]->damaging = boss;
	spawner_x = amplitude % 100;//will spawn the location for the AI1 function
	spawner_y = amplitude % 200;//will spawn the location for the AI1 function
	while (1)
	{
		AI2_speed = abs(amplitude)%modulation;
		if (AI2_speed<30 && AI2_speed>13)
			break;
		else
			modulation++;

	}
	entity_manager.EntityList[0]->health=100;


}

int test1 = 0;

int verticaldelta = 0;
int horizontaldelta = 0;
int AItype = 0;//0 will be vertical bar moving right 1 will be horizontal bar moving down 2 will be veritcal bar moving left 3 will be horizontal bar moving up
void gf2d_entity_spawn(int AI_Pattern)//AI function 1
{
	Vector4D mouseColor = { 255, 100, 255, 200 };
	int counter = 0;
	int mx, my;
	SDL_GetMouseState(&mx, &my);
	


	
	if (AI_Pattern == 1)
	{
		AI_Type = 1;
		if (AItype == 0)
		{
			for (counter; counter < entitySize; counter++)
			{
				if (entity_manager.EntityList[counter]->inuse == 0)
				{
					deltax++;
					entity_manager.EntityList[counter]->inuse = 1;
					entity_manager.EntityList[counter]->maxFrames = 3;
					entity_manager.EntityList[counter]->frame = 0;
					entity_manager.EntityList[counter]->delta = 0.07;
					entity_manager.EntityList[counter]->pos.x = 1050;
					entity_manager.EntityList[counter]->pos.y = 650;
					entity_manager.EntityList[counter]->rise_run.x = deltax+AI2_speed;
					entity_manager.EntityList[counter]->rise_run.y = 1;
					entity_manager.EntityList[counter]->scale = 1.0;
					break;

				}

				

				if (180 < deltax)
					deltax = 1;




				entity_manager.EntityList[0]->maxFrames = 1;
			}
			for (counter; counter < entitySize; counter++)
			{
				if (entity_manager.EntityList[counter]->inuse == 0)
				{
					deltax++;
					entity_manager.EntityList[counter]->inuse = 1;
					entity_manager.EntityList[counter]->maxFrames = 3;
					entity_manager.EntityList[counter]->frame = 0;
					entity_manager.EntityList[counter]->delta = 0.07;
					entity_manager.EntityList[counter]->pos.x = 20;
					entity_manager.EntityList[counter]->pos.y = 650;
					entity_manager.EntityList[counter]->scale = 1;
					entity_manager.EntityList[counter]->rise_run.x = -deltax + AI2_speed;
					entity_manager.EntityList[counter]->rise_run.y = -1.0;
					break;

				}

				if (180 < deltax)
					deltax = 1;
			}
			
		}
	}
	if (AI_Pattern == 2)
	{
		AI_Type = 2;
		for (counter; counter < entitySize; counter++)
		{
			if (entity_manager.EntityList[counter]->inuse == 0)
			{
				deltax++;
				entity_manager.EntityList[counter]->inuse = 1;
				entity_manager.EntityList[counter]->maxFrames = 3;
				entity_manager.EntityList[counter]->frame = 0;
				entity_manager.EntityList[counter]->delta = 0.07;
				entity_manager.EntityList[counter]->pos.x = spawner_x + AI2_leftx;
				entity_manager.EntityList[counter]->pos.y = spawner_y + AI2_y;
				entity_manager.EntityList[counter]->rise_run.x = deltax + AI2_speed;
				entity_manager.EntityList[counter]->rise_run.y = 1;
				entity_manager.EntityList[counter]->scale = 1.0;
				break;
				
			}

			
			
			if (deltamax < deltax)
				deltax = 1;




			entity_manager.EntityList[0]->maxFrames = 1;
		}
		for (counter; counter < entitySize; counter++)
		{
			if (entity_manager.EntityList[counter]->inuse == 0)
			{
				deltax++;
				entity_manager.EntityList[counter]->inuse = 1;
				entity_manager.EntityList[counter]->maxFrames = 3;
				entity_manager.EntityList[counter]->frame = 0;
				entity_manager.EntityList[counter]->delta = 0.07;
				entity_manager.EntityList[counter]->pos.x = spawner_x + AI2_rightx;
				entity_manager.EntityList[counter]->pos.y = spawner_y + AI2_y;
				entity_manager.EntityList[counter]->scale = 1;
				entity_manager.EntityList[counter]->rise_run.x = deltax + AI2_speed;
				entity_manager.EntityList[counter]->rise_run.y = 1.0;
				break;

			}
			if (deltamax < deltax)
				deltax = 1;




			entity_manager.EntityList[0]->maxFrames = 1;

		}
	}


	if (AI_Pattern == 3)
	{
		AI_Type = 3;
		if (AItype == 0)
		{
			

			for (counter; counter < entitySize; counter++)
			{
				if (entity_manager.EntityList[counter]->inuse == 0)
				{
					deltax++;
					entity_manager.EntityList[counter]->inuse = 1;
					entity_manager.EntityList[counter]->maxFrames = 3;
					entity_manager.EntityList[counter]->frame = 0;
					entity_manager.EntityList[counter]->delta = 0.07;
					entity_manager.EntityList[counter]->pos.x = spawner_x + AI3_x;
					entity_manager.EntityList[counter]->pos.y = spawner_y + AI3_y;
					entity_manager.EntityList[counter]->rise_run.x = deltax + AI2_speed;
					entity_manager.EntityList[counter]->rise_run.y = 1;
					entity_manager.EntityList[counter]->scale = 1.0;
					break;
					
				}

				

				
			
				if (deltamax < deltax)
					deltax = 1;




				entity_manager.EntityList[0]->maxFrames = 1;
			}
			for (counter; counter < entitySize; counter++)
			{
				if (entity_manager.EntityList[counter]->inuse == 0)
				{
					deltax++;
					entity_manager.EntityList[counter]->inuse = 1;
					entity_manager.EntityList[counter]->maxFrames = 3;
					entity_manager.EntityList[counter]->frame = 0;
					entity_manager.EntityList[counter]->delta = 0.07;
					entity_manager.EntityList[counter]->pos.x = spawner_x + AI3_x;
					entity_manager.EntityList[counter]->pos.y = spawner_y + AI3_y2;
					entity_manager.EntityList[counter]->scale = 1;
					entity_manager.EntityList[counter]->rise_run.x = -deltax + AI2_speed;
					entity_manager.EntityList[counter]->rise_run.y = -1.0;
					break;

				}
				if (deltamax < deltax)
					deltax = 1;




				entity_manager.EntityList[0]->maxFrames = 1;

			}


			for (counter = 3; counter<5; counter++)
			{
				if (entity_manager.EntityList[counter]->inuse == 0)
				{
					deltax++;
					entity_manager.EntityList[counter]->inuse = 1;
					entity_manager.EntityList[counter]->maxFrames = 5;
					entity_manager.EntityList[counter]->frame = 0;
					entity_manager.EntityList[counter]->delta = 0.07;
					entity_manager.EntityList[counter]->pos.x = 400;
					entity_manager.EntityList[counter]->pos.y = 715;
					entity_manager.EntityList[counter]->scale = 199;
					entity_manager.EntityList[counter]->rise_run.x = 0;
					entity_manager.EntityList[counter]->rise_run.y = -3;
					break;

				}
			}
			
		}
	}

	if (AI_Pattern == 4)
	{
		AI_Type = 4;
		for (counter; counter < entitySize; counter++)
		{
			if (entity_manager.EntityList[counter]->inuse == 0)
			{
				deltax++;
				entity_manager.EntityList[counter]->inuse = 1;
				entity_manager.EntityList[counter]->maxFrames = 3;
				entity_manager.EntityList[counter]->frame = 0;
				entity_manager.EntityList[counter]->delta = 0.07;
				entity_manager.EntityList[counter]->pos.x = 500;
				entity_manager.EntityList[counter]->pos.y = spawner_y + AI2_y;
				entity_manager.EntityList[counter]->rise_run.x = deltax + AI2_speed;
				entity_manager.EntityList[counter]->rise_run.y = 1;
				entity_manager.EntityList[counter]->scale = 1.0;
				break;

			}

			

			if (deltamax < deltax)
				deltax = 1;




			entity_manager.EntityList[0]->maxFrames = 1;
		}
		for (counter; counter < entitySize; counter++)
		{
			if (entity_manager.EntityList[counter]->inuse == 0)
			{
				deltax++;
				entity_manager.EntityList[counter]->inuse = 1;
				entity_manager.EntityList[counter]->maxFrames = 3;
				entity_manager.EntityList[counter]->frame = 0;
				entity_manager.EntityList[counter]->delta = 0.07;
				entity_manager.EntityList[counter]->pos.x = 600;
				entity_manager.EntityList[counter]->pos.y = spawner_y + AI2_y;
				entity_manager.EntityList[counter]->scale = 1;
				entity_manager.EntityList[counter]->rise_run.x = -deltax + AI2_speed;
				entity_manager.EntityList[counter]->rise_run.y = -1.0;
				break;

			}
			if (deltamax < deltax)
				deltax = 1;




			entity_manager.EntityList[0]->maxFrames = 1;

		}
	}

}


void drawEntity(int mf, int boss, int endgame)
{
	Vector4D mouseColor = { 255, 100, 255, 200 };
	int counter = 0;
	

	for (counter; counter<entitySize; counter++)
	{
		
		if (endgame == 1 && counter>1)
			return;
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
			else if (entity_manager.EntityList[counter]->delta == 30.3)
			{
				entity_manager.EntityList[counter]->img = gf2d_sprite_load_all("images/projectiles/beam.png", 215, 743, 5);
			}
			else 
				entity_manager.EntityList[counter]->img = gf2d_sprite_load_all("images/projectiles/ball_2.png", 102, 115, 3);

			if (!test1)
			{
				//gf2d_sprite_draw_image(entity_manager.EntityList[counter]->img, vector2d(12, 350));
				test1++;
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

		if (entity_manager.EntityList[counter]->inuse == 1)
		{
			if (AI_Type==1)
				AI_Function1_Move(entity_manager.EntityList[counter], counter);
			if (AI_Type==2)
				AI_Function2_Move(entity_manager.EntityList[counter], counter);
			if (AI_Type == 3)
			{
				AI_Function3_Move(entity_manager.EntityList[counter], counter);
				if (counter>4)
				entity_manager.EntityList[counter]->pos.x += 5;
			}
			if (AI_Type == 4)
			{
				AI_Function4_Move(entity_manager.EntityList[counter], counter);
				entity_manager.EntityList[counter]->pos.y += 3.3;
			}
		}
			

		//gf2d_sprite_draw_image(entity_manager.EntityList[counter]->img, vector2d(250, 300));
	}

	entity_manager.EntityList[0]->pos.x = mx;
	entity_manager.EntityList[0]->pos.y = my;
	entity_manager.EntityList[1]->pos.x = 360;
	entity_manager.EntityList[1]->pos.y = 100;

}

int Ent_Hit()
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
		
		

			entity_manager.EntityList[0]->health = entity_manager.EntityList[0]->health-2;
			return entity_manager.EntityList[0]->health;
		}
     

		
	}
	return entity_manager.EntityList[0]->health;
}


/*
*@ frees all memory in the structure minus player
*@
*/

void gf2d_entity_free()
{
	int counter = 0;
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
	if (xf < -150 || xf>1150)
	{
		gf2d_entity_free_one(ent);
	}
	else
	{
		ent->pos.x = xf;
	}
	if (yf < -150 || yf>719)
	{
		gf2d_entity_free_one(ent);
	}
	else
	{
		ent->pos.y = yf;
	}

}



void AI_Function2_Move(Entity *ent, int location)
{
	
	if (ent->pos.x < -150 || ent->pos.x>1150)
	{
		gf2d_entity_free_one(location);
	}
	else
	{
		ent->pos.x =  cos(ent->rise_run.x) * 3 + ent->pos.x;
		
	}
	if (ent->pos.y < -150 || ent->pos.y>719)
	{
		gf2d_entity_free_one(location);
	}
	else
	{
		ent->pos.y = sin(ent->rise_run.x) * 3 + ent->pos.y;
	}




}


void AI_Function4_Move(Entity *ent, int location)
{

	if (ent->pos.x < -150 || ent->pos.x>1150)
	{
		gf2d_entity_free_one(location);
	}
	else
	{
		ent->pos.x = cos(ent->rise_run.x) * 3 + ent->pos.x;

	}
	if (ent->pos.y < -150 || ent->pos.y>719)
	{
		gf2d_entity_free_one(location);
	}
	else
	{
		ent->pos.y = sin(ent->rise_run.x) * 3 + ent->pos.y;
	}




}

void AI_Function1_Move(Entity *ent, int location)
{
	if (ent->pos.x < -150 || ent->pos.x>1150)
	{
		gf2d_entity_free_one(location);
	}
	else
	{
		ent->pos.x = cos(ent->rise_run.x) * 3 + ent->pos.x;

	}
	if (ent->pos.y < -150 || ent->pos.y>719)
	{
		gf2d_entity_free_one(location);
	}
	else
	{
		ent->pos.y = sin(ent->rise_run.x) * 3 + ent->pos.y;
	}

}


void AI_Function3_Move(Entity *ent, int location)
{
	if (location > 5)
	{
		if (ent->pos.x < -150 || ent->pos.x>1150)
		{
			gf2d_entity_free_one(location);
		}
		else
		{
			ent->pos.x = cos(ent->rise_run.x) * 3 + ent->pos.x;

		}
		if (ent->pos.y < -150 || ent->pos.y>719)
		{
			gf2d_entity_free_one(location);
		}
		else
		{
			ent->pos.y = sin(ent->rise_run.x) * 3 + ent->pos.y;
		}
	}
	else if (location >2)
	{
		if (ent->pos.x < -150 || ent->pos.x>1300)
		{
			gf2d_entity_free_one(location);
		}
		
		if (ent->pos.y < -150 )
		{
			return;
		}
		else
		{
			ent->pos.y = ent->pos.y + ent->rise_run.y;
		}
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
	if (xf < -150 && xf>1280)
	{
		gf2d_entity_free(ent);
	}
	else
	{
		ent->pos.x = xf;
	}
	if (yf < -150 && yf>1280)
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





