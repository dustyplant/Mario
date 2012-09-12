#include <vector>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "../Level_Structure/Tile.h"
#include "../Level_Structure/Tiles.h"
#include "Coll.h"

bool Coll::check_collision(SDL_Rect &box, std::vector<Tile> &tileSet, SDL_Rect &posOffset){
	for(int i = 0; i < tileSet.size(); i++){
		SDL_Rect temp = tileSet[i].get_box();

		if( (box.x + box.w  > temp.x && box.x < temp.x + temp.w) && ( (box.y + box.h > temp.y && box.y < temp.y) || (box.y < temp.y + temp.h && box.y + box.h > temp.y + temp.h) ) ){
			return  true;
		}
	}
	return false;
}

bool Coll::check_grounded(SDL_Rect &box, std::vector<Tile> &tileSet, SDL_Rect &posOffset){
	for(int i = 0; i < tileSet.size(); i++){
		SDL_Rect temp = tileSet[i].get_box();

		if( (box.x + box.w  > temp.x && box.x < temp.x + temp.w) && (box.y + box.h == temp.y && box.y  == temp.y) ){
			return  true;
		}
	}
	return false;
}

bool Coll::check_up_collision(SDL_Rect &box, std::vector<Tile> &tileSet, SDL_Rect &posOffset){
	for(int i = 0; i < tileSet.size(); i++){
		SDL_Rect temp = tileSet[i].get_box();

		if( (box.x + box.w  > temp.x && box.x < temp.x + temp.w) && (box.y < temp.y + temp.h && box.y + box.h > temp.y + temp.h)){
			return  true;
		}
	}
	return false;
}

bool Coll::check_down_collision(SDL_Rect &box, std::vector<Tile> &tileSet, SDL_Rect &posOffset){
	for(int i = 0; i < tileSet.size(); i++){
		SDL_Rect temp = tileSet[i].get_box();

		if( (box.x + box.w  >= temp.x && box.x < temp.x + temp.w) && (box.y + box.h > temp.y && box.y < temp.y) ){
			return  true;
		}
	}
	return false;
}

bool Coll::check_left_collision(SDL_Rect &box, std::vector<Tile> &tileSet, SDL_Rect &posOffset){
	for(int i = 0; i < tileSet.size(); i++){
		SDL_Rect temp = tileSet[i].get_box();

		if( !(box.y + box.h <= temp.y || box.y >= temp.y + temp.h ) ){
			if( box.x <= temp.x + temp.w && box.x + box.w >= temp.x + temp.h){
				return  true;
			}
		}
	}
	return false;
}

bool Coll::check_right_collision(SDL_Rect &box, std::vector<Tile> &tileSet, SDL_Rect &posOffset){
	for(int i = 0; i < tileSet.size(); i++){
		SDL_Rect temp = tileSet[i].get_box();

		if( !(box.y + box.h <= temp.y || box.y >= temp.y + temp.h) ){
			if( box.x + box.w >= temp.x && box.x <= temp.x){
				return  true;
			}
		}
	}
	return false;
}