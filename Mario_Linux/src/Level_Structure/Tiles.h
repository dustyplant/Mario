#ifndef TILES_H
#define TILES_H

#include "../Entities/Object.h"
#include "Tile.h"

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

#include <vector>

class Tiles: public Object{
private:
	void set_clips();
	SDL_Rect clips[1];
	std::vector<Tile> tile_set;
	void addTile(int x, int y, int w, int h, int type);
public:
	Tiles();
	//void move();
	void display(SDL_Rect &posOffset, SDL_Surface* screen);
	std::vector<Tile> get_tileSet();
	bool load_tiles();
};

#endif