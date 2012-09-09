#include "Object.h"
#include "../Utilities/SDL_BaseProg.h"
#include <vector>
#include <iostream>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

Object::Object(){
	
	per_pixel = false;
	impassable = true;
	image = NULL;
	flippedImage = NULL;
}

Object::Object(int x, int y, int w, int h){
	box.x = x;
	box.y = y;
	box.w = w;
	box.h = h;
	per_pixel = false;
	impassable = true;
	image = NULL;
}

Object::~Object(){
	SDL_FreeSurface(image);
	SDL_FreeSurface(flippedImage);
}

bool Object::collision(SDL_Rect &rect){
	if( (box.x > rect.x && box.x + box.w < rect.x + rect.w) && box.y > rect.y && box.y + box.h < rect.y + rect.h ){
		return true;
	}
}

bool Object::collision(std::vector<SDL_Rect> vec){
	//TODO::Write the generic collision detection function.
	return false;
}

void Object::show(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clipper/* = NULL */){
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(source, clipper, destination, &offset);
}

SDL_Rect Object::get_rects(){
	return box;
}

std::vector<SDL_Rect> Object::getVecRects(){
	return boxes;
}