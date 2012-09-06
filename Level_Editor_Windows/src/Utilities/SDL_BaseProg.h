#ifndef SDL_BASEPROG_H
#define SDL_BASEPROG_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

#include <string>

class SDL_BaseProg{
public:
	void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clipper = NULL);
	SDL_Surface* load_image(std::string filename);
};

#endif