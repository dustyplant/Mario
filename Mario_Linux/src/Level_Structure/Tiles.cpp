#include "Tiles.h"
#include "Tile.h"
#include "../Entities/Object.h"
#include <iostream>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"


Tiles::Tiles(){
	image = load_image("res/groundtiles.png");
	set_clips();
}
void Tiles::display(SDL_Rect &posOffset, SDL_Surface* screen){
	for(int i = 0; i < tile_set.size(); ++i){
		show(tile_set[i].get_box().x + posOffset.x, tile_set[i].get_box().y + posOffset.y, image, screen, &clips[tile_set[i].getClip()]);
	}
}
void Tiles::addTile(int x, int y, int w, int h, int type){
	Tile temp(x, y, w, h, type);
	tile_set.push_back(temp);
}
std::vector<Tile> Tiles::get_tileSet(){
	return tile_set;
}

bool Tiles::load_tiles(){

	addTile(0,400,clips[0].w, clips[0].h, 0);
	int i;
	for(i = 1; i < 20; i++)
		addTile(tile_set[i-1].get_box().x + tile_set[i-1].get_box().w, tile_set[i-1].get_box().y, clips[0].w, clips[0].h, 0);
	for(; i < 23; i++)
		addTile(tile_set[i-1].get_box().x + tile_set[i-1].get_box().w, tile_set[i-1].get_box().y - 10, clips[0].w, clips[0].h, 0);

	return true;
}

void Tiles::set_clips(){
	clips[0].x = 154;
	clips[0].y = 99;
	clips[0].w = 16;
	clips[0].h = 16;
}
/*
void move();

*/