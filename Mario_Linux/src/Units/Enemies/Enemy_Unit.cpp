#include "../../Entities/Killable.h"
#include "Enemy_Unit.h"

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

Enemy_Unit::Enemy_Unit(int x, int y, int ttype, int tSheet, SDL_Rect *clipper, SDL_Rect *camera, SDL_Surface *im, SDL_Surface *tScreen){
	type = ttype;
	sheet = tSheet;
	currentClip = 0;
	clips = clipper;
	max = 3;

	img = im;
	screen = tScreen;

	posOffset = camera;

	box.x = x;
	box.y = y;
	box.w = clips[currentClip].w;
	box.h = clips[currentClip].h;
}
/*
Enemy_Unit::~Enemy_Unit(){
	SDL_FreeSurface(img);
}*/

SDL_Rect Enemy_Unit::get_box(){
	return box;
}

int Enemy_Unit::get_type(){
	return type;
}

int Enemy_Unit::get_sheet(){
	return sheet;
}

int Enemy_Unit::get_currentClip(){
	return currentClip;
}

void Enemy_Unit::move(int frame){
	if(frame%12 == 0){
		currentClip++;
		if(currentClip >= max-1){
			currentClip = 0;
		}
	}
	if(!alive){
		currentClip = 2;
	}
}

void Enemy_Unit::display(int screen_width, int screen_height){
	if(box.x + box.w + posOffset->x > 0 && box.x  + posOffset->x < screen_width){
		if(box.y + box.h + posOffset->y > 0 && box.y  + posOffset->y < screen_height){
			show(box.x + posOffset->x, box.y + posOffset->y, img, screen, &clips[currentClip]);
		}
	}
}