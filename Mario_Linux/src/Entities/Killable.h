#ifndef KILLABLE_H
#define KILLABLE_H

#include "Killable.h"
#include "Object.h"

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

class Killable: Object{
protected:
	bool alive;
public:
	Killable();
	
};

#endif