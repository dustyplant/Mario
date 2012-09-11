#ifndef ENEMY_UNIT_H
#define ENEMY_UNIT_H

#include "../../Entities/Killable.h"

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

class Enemy_Unit: public Killable{
public:
	int type;
	int sheet;
	int currentClip;
	int max;
	SDL_Rect *clips;
	SDL_Surface *screen;
	SDL_Surface *img;
	SDL_Rect *posOffset;
public:
	Enemy_Unit(int x, int y, int ttype, int tSheet, SDL_Rect *clipper, SDL_Rect *camera, SDL_Surface *im, SDL_Surface *tScreen);
	SDL_Rect get_box();
	int get_type();
	int get_sheet();
	int get_currentClip();
	void move(int frame);
	void display(int screen_width, int screen_height);
};

#endif