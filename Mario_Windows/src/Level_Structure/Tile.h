#ifndef TILE_H
#define TILE_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

#include <vector>

class Tile{
private:
	SDL_Rect box;
	int clip;
public:
	Tile(int x, int y, int w, int h, int type);
	int getClip();
	SDL_Rect get_box();
};

#endif