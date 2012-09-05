#include "Tiles.h"
#include "Tile.h"
#include "../Entities/Object.h"
#include <iostream>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"


Tiles::Tiles(SDL_Rect &tposOffset, SDL_Surface* tScreen){
	image = load_image("res/groundtiles.png");
	screen = tScreen;
	posOffset = tposOffset;
	set_clips();
}
void Tiles::display(){
	for(int i = 0; i < tile_set.size(); ++i){
		show(tile_set[i].get_box().x + posOffset.x, tile_set[i].get_box().y + posOffset.y, image, screen, &clips[tile_set[i].getClip()]);
	}
}

void Tiles::displayTile(SDL_Rect clip){
	show(0 + posOffset.x, 0 + posOffset.y, image, screen, &clip);
}

void Tiles::addTile(int x, int y, int w, int h, int type){
	Tile temp(x, y, w, h, type);
	tile_set.push_back(temp);
}

std::vector<Tile> &Tiles::get_tileSet(){
	return tile_set;
}

bool Tiles::load_tiles(){

	addTile(0,400,clips[0].w, clips[0].h, 0);
	int i;
	for(i = 1; i < 100; i++)
		addTile(tile_set[i-1].get_box().x + tile_set[i-1].get_box().w, tile_set[i-1].get_box().y, clips[0].w, clips[0].h, 0);
	//for(; i < 23; i++)
	//	addTile(tile_set[i-1].get_box().x + tile_set[i-1].get_box().w, tile_set[i-1].get_box().y - 10, clips[0].w, clips[0].h, 0);
	addTile(100, 300, clips[0].w, clips[0].h, 0);
	i++;
	addTile(tile_set[i-1].get_box().x + tile_set[i-1].get_box().w, tile_set[i-1].get_box().y, clips[0].w, clips[0].h, 0);
	i++;

	addTile(200, 200, clips[0].w, clips[0].h, 0);
	i++;
	addTile(tile_set[i-1].get_box().x + tile_set[i-1].get_box().w, tile_set[i-1].get_box().y, clips[0].w, clips[0].h, 0);

	return true;
}

void Tiles::set_clips(){
	clips[0].x = 154;
	clips[0].y = 99;
	clips[0].w = 16;
	clips[0].h = 16;
}