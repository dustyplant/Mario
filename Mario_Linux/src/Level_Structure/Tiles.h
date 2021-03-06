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
	SDL_Rect *posOffset;
	int screen_width;
	int screen_height;
public:
	Tiles(SDL_Rect &tposOffset, SDL_Surface* tScreen, int screen_width, int screen_height);
	//void move();
	SDL_Rect clips[967];
	void display();
	void displayTile(int clipper, int x);
	void addTile(int x, int y, int w, int h, int type);
	std::vector<Tile> &get_tileSet();
	bool load_tiles(std::string filename = "src/Level_Structure/Levels/test_level.txt");
	static std::vector<Tile> tileSet;
};

#endif