#include "Tile.h"

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"


Tile::Tile(int x, int y, int w, int h, int type){
	box.x = x;
	box.y = y;
	box.w = w;
	box.h = h;
	clip = type;
}
int Tile::getClip(){
	return clip;
}
SDL_Rect Tile::get_box(){
	return box;
}