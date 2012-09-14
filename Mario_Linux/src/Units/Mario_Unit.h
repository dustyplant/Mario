#ifndef MARIO_UNIT_H
#define MARIO_UNIT_H

#include "../Entities/Killable.h"
#include "../Level_Structure/Tile.h"
#include "../Level_Structure/Tiles.h"
#include "MarioAnimation.h"

#include <vector>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

class Mario_Unit: public Killable, public MarioAnimation{
private:
	//Full size is 82 Marios.
	SDL_Rect rightClips[26];
	SDL_Rect leftClips[26];
	bool goingRight;
	bool goingLeft;
	void set_clips();
	SDL_Event event;
	SDL_Surface *screen;

	SDL_Rect *posOffset;
	
	bool jumping;
	double gravity;
	int velocity;
	double yVel;
	int boost;
	int jumpCap;
	int upChuck;
	bool grounded;

	bool falling;
	bool check_collision();
	bool check_up_collision();
	bool check_down_collision();
	bool check_left_collision();
	bool check_right_collision();

	bool jumpingFunc();
	bool fallingFunc();
	bool check_grounded();

	int jumpFramer;
	int moveFramer;
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;

public:
	Mario_Unit(SDL_Event &temp, SDL_Surface* sprite_sheet, int screenw, int screenh, SDL_Surface *tScreen, SDL_Rect &tPosOffset);

	//~Mario_Unit();

	void display(bool jump);
	void move(SDL_Surface* background, bool jump);
	bool loaded;
	void jumper(bool jump);
	bool getLeft();
	bool getRight();
	void setClip(int newClip);
};

#endif