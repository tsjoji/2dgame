#include "gf2d_sprite.h"
#include "gf2d_vector.h"

//entity based game
typedef struct Entity_S
{
	Sprite *img;
	int health;
	int speed;
	int scale;
	int theta;
    Vector2D pos;
	int velocity;
	double time;
	int invcib;/**<invcibility to the player*/
	int damaging;/**<enemy bullet able to dmg*/
	int inuse;
}Entity;

/*
*@ frees memory in the structure
*@ 
*/
void gf2d_entity_free();

void gf2d_entity_spawn();

/*
*@ frees memory in the structure
*/
Entity *gf2d_new();

/*
*@ frees memory in the structure
*@sets x = 1 if x = 0
*xf=xcostheta-x^2costheta
*yf=xcostheta+x^2costheta
*/
void gf2d_rotTransx2(Entity *ent);

/*
*@ frees memory in the structure
*@sets x = 1 if x = 0
*tan(arccos(x)+arcSin(y))=1
*/
void gf2d_crazyzone(Entity *ent);

