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
	SDL_Surface* screen;
	SDL_Rect posOffset;
	std::vector<Tile> tile_set;
public:
	Tiles(SDL_Rect &tposOffset, SDL_Surface* tScreen);
	SDL_Rect clips[1];
	void display();
	void displayTile(SDL_Rect clip);
	void addTile(int x, int y, int w, int h, int type);
	std::vector<Tile> &get_tileSet();
	bool load_tiles();
};

#endif