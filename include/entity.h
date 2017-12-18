#include "gf2d_sprite.h"
#include "gf2d_vector.h"

enum ident{bullet, player, Boss, powerup1, powerup2, powerup3};

enum gametype{ Mainmenu, Game, Loser, Winner, Options };


//entity based game
typedef struct Entity_S
{
	int healthregen;
	int powerbarregen;
	int armor;
	Sprite *img;/** pointer to the entity img*/
	int health;/** how much health player has*/
	int scale;/** how uch to scale null will indicate no change*/
	int theta;/** */
	Vector2D pos;/** current location .x for x pos .y for y pos*/
	Vector2D rise_run;/** how quickly the rise/run will be .x will be run and .y will be rise*/
	int velocity;/**how fast it can go */
	double time;/**checks how long certain enitities have to live boss abilities have this */
	int invcib;/**<invcibility to the player*/
	int damaging;/**<enemy bullet able to dmg*/
	int inuse;/**checks to see if memory is in use */
	enum ident type;/**<1 is player, 2 is boss, , 3 is beam1, 4 is powerup1, 5 is powerup2, 6 is powerup3, else bullet*/
	float frame;/**<what frame the sprite is on*/
	float delta;/**<how fast to change each frames*/
	int maxFrames;/**<max frames*/
	int identity;/**<unique pattern for rot2x 0-12*/
	int powerup;/**<how much power is available*/
}Entity;


typedef struct gamestate_S{

	void(*input)();
	void(*update)();
	void(*draw)();
	struct gamestate_S *parent;

}gamestate;

/*
*@ mallocs and memsets array of x entities to 0
*@
*/
void gf2d_entity_init(int boss);

void resetAI();

/*
*@ spawns the enemies
*@ right now since there are no spawning conditons will just spawn as many as possible if they are not in use
*/
void gf2d_entity_spawn();


/*
*@ spawns the enemies
*@ if off screen free the ent
*@
*/
void AI_Function2_Move(Entity *ent, int location);

void AI_Function3_Move(Entity *ent, int location);

void AI_Function1_Move(Entity *ent, int location);

void AI_Function4_Move(Entity *ent, int location);

/*
*@ checks if the entity is in use if true will draw them
*@
*/
void drawEntity(int mf);


/*
*@ changes x and y positions of each entity using the correct function if ai based
*@if player will just get mouse location
*/
void updateEnt();


/*
*@ checks to see if any entity is hitting the player
*@
*/
int Ent_Hit();

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