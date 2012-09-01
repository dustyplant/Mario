#include "Mario_Unit.h"
#include "../Entities/Object.h"
#include "../Level_Structure/Tile.h"

#include <vector>
#include <iostream>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

Mario_Unit::Mario_Unit(SDL_Event &temp, SDL_Surface* sprite_sheet, int screenw, int screenh){
	loaded = true;
	currentClip = 0;
	set_clips();
	box.x = 0;
	box.y = 0;
	jumping = false;
	falling = true;
	grounded = false;

	goingRight = true;
	goingLeft = false;
	event = temp;
	velocity = 3;
	yVel = 7;
	jumpCap = 150;
	upChuck = jumpCap;

	framer = 0;
	
	image = load_image("res/smb3_mario_sheet.png");
	if(image == NULL)
		loaded = false;

	SCREEN_WIDTH = screenw;
	SCREEN_HEIGHT = screenh;

}	

void Mario_Unit::display(SDL_Surface* screen, SDL_Surface* background, SDL_Rect &posOffset, bool jump){
	//if(middle)
	show(box.x + posOffset.x, posOffset.y + box.y, image, screen, &clips[currentClip]);
	//show(box.x, SCREEN_HEIGHT/2, image, screen , &clips[currentClip]);
}

void Mario_Unit::move(SDL_Surface* background, SDL_Rect &posOffset, bool jump, std::vector<Tile> tileSet){
	Uint8* keystates = SDL_GetKeyState(NULL);
	box.h = clips[currentClip].h;
	box.w = clips[currentClip].w;
	if(keystates[SDLK_RIGHT] ){
		box.x += velocity;
		if( box.x + clips[currentClip].w + posOffset.x > SCREEN_WIDTH  || check_right_collision(tileSet, posOffset) ) {
			box.x -= velocity;
		}
		if(goingRight){
			if(framer == 0){
				currentClip++;
				if(currentClip > 11)
					currentClip = 7;
			}
		}
		else{
			currentClip = 6;
			goingRight = true;
			goingLeft = false;
		}
		box.y += box.h - clips[currentClip].h;
		//box.x += box.w - clips[currentClip].w;

	}
	if(keystates[SDLK_LEFT]){
		box.x -= velocity;
		if( box.x + posOffset.x < 0 || check_left_collision(tileSet, posOffset)){
			box.x += velocity;

		}
		if(goingLeft){
			if(framer == 0){
				currentClip--;
				if(currentClip < 0)
					currentClip = 4;
			}
		}
		else{
			currentClip = 5;
			goingRight = false;
			goingLeft = true;
		}
		box.y += box.h - clips[currentClip].h;
	}
	if(!keystates[SDLK_RIGHT] && !keystates[SDLK_LEFT]){
		if(goingRight){
			currentClip = 6;
		}
		else{
			currentClip = 5;
		}
		box.y += box.h - clips[currentClip].h;
	}
	framer++;
	if(framer == 15){
		framer = 0;
	}

	jumper(jump, tileSet, posOffset);

}

void Mario_Unit::jumper(bool jump, std::vector<Tile> &tileSet, SDL_Rect &posOffset){
	if(jump && !jumping && !falling && grounded){
		jumping = true;
		falling = false;
		grounded = false;
	}

	if(jumping){
		jumping = jumpingFunc(tileSet, posOffset);
		falling = !jumping;
	}
	if(!jumping && !check_grounded(tileSet, posOffset)){
		grounded = fallingFunc(tileSet, posOffset);
		falling = !grounded;
	}

	framer++;
	if(framer >= 30){
		framer = 0;
	}
}

bool Mario_Unit::jumpingFunc(std::vector<Tile> &tileSet, SDL_Rect &posOffset){
	upChuck -= yVel;
	box.y -= yVel;
	if(upChuck <= 0 || check_up_collision(tileSet, posOffset)){
		upChuck = jumpCap;
		return false;
	}
	return true;
}

bool Mario_Unit::fallingFunc(std::vector<Tile> &tileSet, SDL_Rect &posOffset){
	box.y += yVel;
	bool bl = false;
	while(check_down_collision(tileSet, posOffset) || box.y + clips[currentClip].h > SCREEN_HEIGHT){
		box.y--;
		bl = true;
	}
	box.y--;
	return bl;
}

bool Mario_Unit::check_collision(std::vector<Tile> &tileSet, SDL_Rect &posOffset){
	box.w = clips[currentClip].w;
	box.h = clips[currentClip].h;

	for(int i = 0; i < tileSet.size(); i++){
		SDL_Rect temp = tileSet[i].get_box();

		if( (box.x + box.w  > temp.x && box.x < temp.x + temp.w) && ( (box.y + box.h > temp.y && box.y < temp.y) || (box.y < temp.y + temp.h && box.y + box.h > temp.y + temp.h) ) ){
			return  true;
		}
	}
	return false;
}

bool Mario_Unit::check_grounded(std::vector<Tile> &tileSet, SDL_Rect &posOffset){
	box.w = clips[currentClip].w;
	box.h = clips[currentClip].h;

	for(int i = 0; i < tileSet.size(); i++){
		SDL_Rect temp = tileSet[i].get_box();

		if( (box.x + box.w  > temp.x && box.x < temp.x + temp.w) && (box.y + box.h +1 >= temp.y && box.y +1 <= temp.y) ){
			return  true;
		}
	}
	return false;
}

bool Mario_Unit::check_up_collision(std::vector<Tile> &tileSet, SDL_Rect &posOffset){
	box.w = clips[currentClip].w;
	box.h = clips[currentClip].h;

	for(int i = 0; i < tileSet.size(); i++){
		SDL_Rect temp = tileSet[i].get_box();

		if( (box.x + box.w  > temp.x && box.x < temp.x + temp.w) && (box.y < temp.y + temp.h && box.y + box.h > temp.y + temp.h)){
			return  true;
		}
	}
	return false;
}

bool Mario_Unit::check_down_collision(std::vector<Tile> &tileSet, SDL_Rect &posOffset){
	box.w = clips[currentClip].w;
	box.h = clips[currentClip].h;

	for(int i = 0; i < tileSet.size(); i++){
		SDL_Rect temp = tileSet[i].get_box();

		if( (box.x + box.w  > temp.x && box.x < temp.x + temp.w) && (box.y + box.h > temp.y && box.y < temp.y) ){
			return  true;
		}
	}
	return false;
}

bool Mario_Unit::check_left_collision(std::vector<Tile> &tileSet, SDL_Rect &posOffset){
	box.w = clips[currentClip].w;
	box.h = clips[currentClip].h;

	for(int i = 0; i < tileSet.size(); i++){
		SDL_Rect temp = tileSet[i].get_box();

		if( !(box.y + box.h < temp.y || box.y > temp.y + temp.h ) ){
			if( box.x < temp.x + temp.w && box.x + box.w > temp.x + temp.h){
				return  true;
			}
		}
	}
	return false;
}

bool Mario_Unit::check_right_collision(std::vector<Tile> &tileSet, SDL_Rect &posOffset){
	box.w = clips[currentClip].w;
	box.h = clips[currentClip].h;

	for(int i = 0; i < tileSet.size(); i++){
		SDL_Rect temp = tileSet[i].get_box();

		if( !(box.y + box.h < temp.y || box.y > temp.y + temp.h) ){
			if( box.x + box.w > temp.x && box.x < temp.x){
				return  true;
			}
		}
	}
	return false;
}

//Mario 3 Tanuki sprites
void Mario_Unit::set_clips(){
	clips[ 0 ].x = 2;
	clips[ 0 ].y = 963;
	clips[ 0 ].w = 23;
	clips[ 0 ].h = 26;

	clips[ 1 ].x = 33;
	clips[ 1 ].y = 962;
	clips[ 1 ].w = 22;
	clips[ 1 ].h = 29;

	clips[ 2 ].x = 63;
	clips[ 2 ].y = 962;
	clips[ 2 ].w = 21;
	clips[ 2 ].h = 29;

	clips[ 3 ].x = 91;
	clips[ 3 ].y = 963;
	clips[ 3 ].w = 22;
	clips[ 3 ].h = 27;

	clips[ 4 ].x = 131;
	clips[ 4 ].y = 963;
	clips[ 4 ].w = 23;
	clips[ 4 ].h = 28;

	clips[ 5 ].x = 171;
	clips[ 5 ].y = 963;
	clips[ 5 ].w = 23;
	clips[ 5 ].h = 28;

	clips[ 6 ].x = 212;
	clips[ 6 ].y = 963;
	clips[ 6 ].w = 23;
	clips[ 6 ].h = 28;

	clips[ 7 ].x = 252;
	clips[ 7 ].y = 963;
	clips[ 7 ].w = 23;
	clips[ 7 ].h = 28;

	clips[ 8 ].x = 292;
	clips[ 8 ].y = 963;
	clips[ 8 ].w = 23;
	clips[ 8 ].h = 27;

	clips[ 9 ].x = 322;
	clips[ 9 ].y = 962;
	clips[ 9 ].w = 21;
	clips[ 9 ].h = 29;

	clips[ 10 ].x = 351;
	clips[ 10 ].y = 962;
	clips[ 10 ].w = 22;
	clips[ 10 ].h = 29;

	clips[ 11 ].x = 381;
	clips[ 11 ].y = 963;
	clips[ 11 ].w = 23;
	clips[ 11 ].h = 28;
}

/*
//Super Mario NES normal sprites.
void Mario_Unit::set_clips(){
	clips[ 0 ].x = 58;
	clips[ 0 ].y = 0;
	clips[ 0 ].w = 34;
	clips[ 0 ].h = 32;

	clips[ 1 ].x = 120;
	clips[ 1 ].y = 0;
	clips[ 1 ].w = 28;
	clips[ 1 ].h = 32;

	clips[ 2 ].x = 178;
	clips[ 2 ].y = 0;
	clips[ 2 ].w = 32;
	clips[ 2 ].h = 32;

	clips[ 3 ].x = 242;
	clips[ 3 ].y = 0;
	clips[ 3 ].w = 24;
	clips[ 3 ].h = 32;

	clips[ 4 ].x = 300;
	clips[ 4 ].y = 0;
	clips[ 4 ].w = 28;
	clips[ 4 ].h = 30;

	clips[ 5 ].x = 362;
	clips[ 5 ].y = 0;
	clips[ 5 ].w = 26;
	clips[ 5 ].h = 32;

	clips[ 6 ].x = 422;
	clips[ 6 ].y = 0;
	clips[ 6 ].w = 26;
	clips[ 6 ].h = 32;

	clips[ 7 ].x = 482;
	clips[ 7 ].y = 0;
	clips[ 7 ].w = 28;
	clips[ 7 ].h = 30;

	clips[ 8 ].x = 544;
	clips[ 8 ].y = 0;
	clips[ 8 ].w = 24;
	clips[ 8 ].h = 32;

	clips[ 9 ].x = 600;
	clips[ 9 ].y = 0;
	clips[ 9 ].w = 32;
	clips[ 9 ].h = 32;

	clips[ 10 ].x = 662;
	clips[ 10 ].y = 0;
	clips[ 10 ].w = 28;
	clips[ 10 ].h = 32;

	clips[ 11 ].x = 718;
	clips[ 11 ].y = 0;
	clips[ 11 ].w = 34;
	clips[ 11 ].h = 32;
}*/