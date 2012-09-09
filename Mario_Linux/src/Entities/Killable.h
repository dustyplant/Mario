#ifndef KILLABLE_H
#define KILLABLE_H

#include "Object.h"

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

class Killable: public Object{
public:
	Killable();
	bool alive;
	
};

#endif