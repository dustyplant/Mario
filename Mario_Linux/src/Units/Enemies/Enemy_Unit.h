#ifndef ENEMY_UNIT_H
#define ENEMY_UNIT_H

#include "../../Entities/Killable.h"

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

class Enemy_Unit: public Killable{
public:
	SDL_Rect box;
	int type;
	SDL_Rect *clips;
	void animate();
public:
	Enemy_Unit(int x, int y, int type, SDL_Rect &clipSet);
	int getClip();
	SDL_Rect get_box();
	void move();
};

#endif