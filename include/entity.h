#include "gf2d_sprite.h"
#include "gf2d_vector.h"

//entity based game
typedef struct Entity_S
{
	Sprite *img;/** pointer to the entity img*/
	int health;/** how much health player has*/
	int scale;/** how uch to scale null will indicate no change*/
	int theta;/** */
    Vector2D pos;/** current location .x for x pos .y for y pos*/
	int velocity;/**how fast it can go */
	double time;/**checks how long certain enitities have to live boss abilities have this */
	int invcib;/**<invcibility to the player*/
	int damaging;/**<enemy bullet able to dmg*/
	int inuse;/**checks to see if memory is in use */
	int type;/**<0 is player, 1 is boss else bullet*/
}Entity;


/*
*@ mallocs and memsets array of x entities to 0
*@
*/
void gf2d_entity_init();

/*
*@ spawns the enemies 
*@ right now since there are no spawning conditons will just spawn as many as possible if they are not in use 
*/
void gf2d_entity_spawn();

/*
*@ checks if the entity is in use if true will draw them
*@
*/
drawEntity(int mf);


/*
*@ changes x and y positions of each entity using the correct function if ai based
*@if player will just get mouse location
*/
updateEnt();


/*
*@ checks to see if any entity is hitting the player 
*@
*/
Ent_Hit();

/*
*@ frees all memory in the structure except the player
*@
*/
void gf2d_entity_free();

/*
*@ frees specific memory in the structure
*@
*/
void gf2d_entity_free_one(int remove);


/*
*@ gives the player invicibility frames if damaged
*/
void damageplayer(int dmg);



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
