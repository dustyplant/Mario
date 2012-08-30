#include "Object.h"
#include "SDL_BaseProg.h"
#include <vector>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

Object::Object(){
	
	per_pixel = false;
	impassable = true;
}

Object::Object(int x, int y, int w, int h){
	box.x = x;
	box.y = y;
	box.w = w;
	box.h = h;
	per_pixel = false;
	impassable = true;
}

bool Object::collision(SDL_Rect &rect){
	//TODO::Write the generic collision detection function.
}

bool Object::collision(std::vector<SDL_Rect> vec){
	//TODO::Write the generic collision detection function.
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