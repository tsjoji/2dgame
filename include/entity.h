#include "gf2d_sprite.h"
#include "gf2d_vector.h"

enum ident{ bullet, player, Boss, powerup1, powerup2, powerup3 };

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
*@brief inits the entity manager and selects the right boss
*@param int boss
*@returns void
*/
void gf2d_entity_init(int boss);






/*
*@brief draw entity
*@param int mf
*@returns void
*/
void drawEntity(int mf);


/*
*@brief updates the entity
*@param void
*@returns void
*/
void updateEnt();


/*
*@brief checks to see if entity is hit and or nar enough to an enemy ot give power shield
*@param void
*@returns int
*/
int Ent_Hit();

/*
*@brief frees all enemies
*@param void
*@returns void
*/
void gf2d_entity_free();

/*
*@brief frees specific enitity
*@param int remove
*@returns void
*/
void gf2d_entity_free_one(int remove);

/*
*@brief resets the ai pattern
*@param void
*@returns void
*/
void resetAI();

/*
*@brief moves enity boss ai
*@param Entity *ent, int location
*@returns void
*/
void AI_Function3_Move(Entity *ent, int location);

/*
*@brief moves entity first ai
*@param Entity *ent, int location
*@returns void
*/
void AI_Function1_Move(Entity *ent, int location);

/*
*@brief moves enity second ai
*@param Entity *ent, int location
*@returns void
*/
void AI_Function2_Move(Entity *ent, int location);

/*
*@brief moves enity boss ai
*@param Entity *ent, int location
*@returns void
*/
void AI_Function4_Move(Entity *ent, int location);


/*
*@brief repositions song
*@param double time
*@returns int
*/
int reposong(double time);

/*
*@brief kills all energy balls
*@param void
*@returns void
*/
void killallbubbles();

/*
*@brief kills all energy balls in a radius 5000 pixels from player
*@param void
*@returns void
*/
void smallcircle();

/*
*@brief gives player random powerup
*@param void
*@returns void
*/
void randompowerup();


/*
*@brief if player has health or powerbar powerup regen it up to their max
*@param void
*@returns void
*/
void regen();

/*
*@brief updates player mouselocation
*@param void
*@returns void
*/
void updateplayermouse();

/*
*@brief if player is using a controller updates their location
*@param int xDir, int yDir
*@returns void
*/
void updateplayer(int xDir, int yDir);

/*
*@brief returns the powerbar
*@param void
*@returns void
*/
int getPowerbar();

/*
*@brief returns the distance from player to bullet squared
*@param float player_x, float player_y, float bulletx, float bullety
*@returns int
*/
int dst(float player_x, float player_y, float bulletx, float bullety);

/*
*@brief returns the distance from player to bullet squared more accurately than dst
*@param float player_x, float player_y, float leftX, float leftY, float rightX, float rightY
*@returns int
*/
int dst2(float player_x, float player_y, float leftX, float leftY, float rightX, float rightY);

/*
*@brief spawns and updates entities
*@param int AI_Pattern
*@returns void
*/
void gf2d_entity_spawn(int AI_Pattern);





