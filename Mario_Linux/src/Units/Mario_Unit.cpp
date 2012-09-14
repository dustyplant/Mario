#include "Mario_Unit.h"
#include "MarioAnimation.h"
#include "../Entities/Object.h"
#include "../Level_Structure/Tile.h"
#include "../Level_Structure/Tiles.h"

#include <vector>
#include <iostream>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

Mario_Unit::Mario_Unit(SDL_Event &temp, SDL_Surface* sprite_sheet, int screenw, int screenh, SDL_Surface *tScreen, SDL_Rect &tPosOffset){
	loaded = true;
	setClip(0);
	set_clips();
	box.x = 0;
	box.y = 0;
	jumping = false;
	falling = true;
	grounded = false;
	posOffset = &tPosOffset;

	goingRight = true;
	goingLeft = false;
	event = temp;
	velocity = 3;
	boost = rightClips[currentClip].h/4;
	yVel = boost;
	gravity = .2;
	jumpCap = rightClips[currentClip].h * 4;
	upChuck = jumpCap;

	moveFramer = 0;
	jumpFramer = 0;
	
	image = load_image("res/mario19_alpha.png");
	if(image == NULL)
		loaded = false;
	flippedImage = load_image("res/mario19_alpha_flipped.png");
	if(flippedImage == NULL)
		loaded = false;

	SCREEN_WIDTH = screenw;
	SCREEN_HEIGHT = screenh;

	screen = tScreen;
}

bool Mario_Unit::getLeft(){
	return goingLeft;
}

bool Mario_Unit::getRight(){
	return goingRight;
}

void Mario_Unit::display(bool jump){
	//if(middle)
	if(!goingLeft){
		show(box.x + posOffset->x, box.y + posOffset->y, image, screen, &rightClips[currentClip]);
		//std::cout << box.x + posOffset->x << ": " << box.y + posOffset->y << std::endl;
		//std::cout << currentClip << std::endl;
	}
	else
		show(box.x + posOffset->x, box.y + posOffset->y , flippedImage, screen, &leftClips[currentClip]);
	if(posOffset->x < -100000 || posOffset->y < -10000){
		alive = false;
	}
	//show(box.x, SCREEN_HEIGHT/2, image, screen , &clips[currentClip]);
}

void Mario_Unit::move(SDL_Surface* background, bool jump){
	Uint8* keystates = SDL_GetKeyState(NULL);
	box.w = rightClips[currentClip].w;
	box.h = rightClips[currentClip].h;


	if(keystates[SDLK_RIGHT] && !keystates[SDLK_LEFT]){
		
		if(goingRight){
			if(moveFramer == 0){
				if(currentClip+1 > 13 || currentClip+1 < 7){
					setClip(7);
				}
				else{
					setClip(currentClip+1);
				}
				/*
				box.y += box.h - rightClips[currentClip].h;
				//std::cout << "First box.x: " << box.x << std::endl;
				box.x += box.w - rightClips[currentClip].w;
				//box.x -= 5;
				//std::cout << "Second box.x: " << box.x << std::endl;
				*/
			}
		}
		else{
			setClip(0);
			//box.y += box.h - rightClips[currentClip].h;
			//box.x += box.w - rightClips[currentClip].w;
			goingRight = true;
			goingLeft = false;
		}
		box.x += velocity;
		if( box.x + rightClips[currentClip].w + posOffset->x > SCREEN_WIDTH  || check_right_collision() ) {
			box.x-=velocity;
		}

	}
	if(keystates[SDLK_LEFT] && !keystates[SDLK_RIGHT]){
		box.x -= velocity;
		if( box.x + posOffset->x < 0 || check_left_collision()){
			box.x += velocity;

		}
		if(goingLeft){
			if(moveFramer == 0){
				if(currentClip+1 > 13 || currentClip+1 < 7){
					setClip(7);
				}
				else{
					setClip(currentClip+1);
				}
			}
		}
		else{
			setClip(0);
			goingRight = false;
			goingLeft = true;
		}
		//box.y += box.h - rightClips[currentClip].h;
	}
	if( ((!keystates[SDLK_RIGHT] && !keystates[SDLK_LEFT]) || (keystates[SDLK_RIGHT] && keystates[SDLK_LEFT]) ) && grounded ){
		setClip(0);
	}
	
	moveFramer++;
	if(moveFramer == 5){
		moveFramer = 0;
	}

	jumper(jump);
	

}

void Mario_Unit::setClip(int newClip){
	currentClip = newClip;
	//Note: Must do this before resetting box.w and box.h to their new values.
	//If not, you will always get 0, even when you wnat it to be different.
	//This will result in a bug that lets him climb up walls and over the top of the screen.
	box.y += box.h - rightClips[currentClip].h;
	if(goingRight && !(jumping && check_left_collision())){
		box.x += box.w - rightClips[currentClip].w;
	}
	if(goingLeft && jumping && check_right_collision()){
		box.x += box.w - leftClips[currentClip].w;
	}
	//Do this second.
	box.w = rightClips[currentClip].w;
	box.h = rightClips[currentClip].h;
	/*
	while(goingRight && !grounded && check_left_collision()){
		box.x++;
	}
	while(goingLeft && !grounded && check_right_collision()){
		box.x--;
	}*/
}

void Mario_Unit::jumper(bool jump){
	if(jump && !jumping && !falling && grounded){
		jumping = true;
		falling = false;
		grounded = false;
		yVel = boost;
	}

	if(jumping){
		setClip(14);
		jumping = jumpingFunc();
		falling = !jumping;
	}
	if(!jumping && !check_grounded()){
		if(!grounded){
			setClip(16);
		}
		grounded = fallingFunc();
		/*
		while(goingRight && !grounded && check_left_collision()){
			box.x++;
		}
		while(goingLeft && !grounded && check_right_collision()){
			box.x--;
		}*/
		falling = !grounded;
	}
	if(yVel < 4 && currentClip != 15){
		setClip(15);
	}
	
	//Use this to control frames for animations and movements.
	jumpFramer++;
	if(jumpFramer >= 60){
		jumpFramer = 0;
	}
}

bool Mario_Unit::jumpingFunc(){
	box.y -= yVel;
	yVel -= gravity;
	if(yVel <= 0 || check_up_collision()){
		yVel = 0;
		upChuck = jumpCap;
		setClip(15);	
		while(check_up_collision()){
			box.y++;
		}
		return false;
	}
	while(goingRight && !grounded && check_left_collision()){
		box.x++;
	}
	while(goingLeft && !grounded && check_right_collision()){
		box.x--;
	}
	return true;
}

bool Mario_Unit::fallingFunc(){
	box.y += yVel;
	yVel += gravity;
	if(yVel > boost){
		yVel = boost;
	}
	bool bl = false;
	if(!grounded && falling && check_down_collision()){
		setClip(0);
	}

	while(check_down_collision()/* || box.y + rightClips[currentClip].h > SCREEN_HEIGHT*/){
		box.y--;

		bl = true;
	}
	return bl;
}

bool Mario_Unit::check_collision(){
	for(int i = 0; i < Tiles::tileSet.size(); i++){
		SDL_Rect temp = Tiles::tileSet[i].get_box();

		if( (box.x + box.w  > temp.x && box.x < temp.x + temp.w) && ( (box.y + box.h > temp.y && box.y < temp.y) || (box.y < temp.y + temp.h && box.y + box.h > temp.y + temp.h) ) ){
			
			return  true;
		}
	}
	return false;
}

bool Mario_Unit::check_grounded(){
	for(int i = 0; i < Tiles::tileSet.size(); i++){
		SDL_Rect temp = Tiles::tileSet[i].get_box();

		if( (box.x + box.w  > temp.x && box.x < temp.x + temp.w) && (box.y + box.h == temp.y && box.y  == temp.y) ){
			return  true;
		}
	}
	return false;
}

bool Mario_Unit::check_up_collision(){
	for(int i = 0; i < Tiles::tileSet.size(); i++){
		SDL_Rect temp = Tiles::tileSet[i].get_box();

		if( (box.x + box.w  > temp.x && box.x < temp.x + temp.w) && (box.y < temp.y + temp.h && box.y + box.h > temp.y + temp.h)){
			return  true;
		}
	}
	return false;
}

bool Mario_Unit::check_down_collision(){
	for(int i = 0; i < Tiles::tileSet.size(); i++){
		SDL_Rect temp = Tiles::tileSet[i].get_box();

		if( (box.x + box.w  >= temp.x && box.x < temp.x + temp.w) && (box.y + box.h > temp.y && box.y < temp.y) ){
			return  true;
		}
	}
	return false;
}

bool Mario_Unit::check_left_collision(){
	for(int i = 0; i < Tiles::tileSet.size(); i++){
		SDL_Rect temp = Tiles::tileSet.at(i).get_box();

		if( !(box.y + box.h <= temp.y || box.y >= temp.y + temp.h ) ){
			if( box.x <= temp.x + temp.w && box.x + box.w >= temp.x + temp.h){
				//std::cout << "hey_left" << std::endl;
				return  true;
			}
		}
	}
	return false;
}

bool Mario_Unit::check_right_collision(){
	box.w = rightClips[currentClip].w;
	box.h = rightClips[currentClip].h;
	for(int i = 0; i < Tiles::tileSet.size(); i++){
		SDL_Rect temp = Tiles::tileSet[i].get_box();

		if( !(box.y + box.h <= temp.y || box.y >= temp.y + temp.h) ){
			if( box.x + box.w >= temp.x && box.x <= temp.x){
				//std::cout << "hey_right" << std::endl;
				return  true;
			}
		}
	}
	return false;
}

//New awesome sprites
void Mario_Unit::set_clips(){
	//Idle animation
	rightClips[ 0 ].x = 19;
	rightClips[ 0 ].y = 42;
	rightClips[ 0 ].w = 18;
	rightClips[ 0 ].h = 29;

	rightClips[ 1 ].x = 38;
	rightClips[ 1 ].y = 42;
	rightClips[ 1 ].w = 19;
	rightClips[ 1 ].h = 29;

	rightClips[ 2 ].x = 57;
	rightClips[ 2 ].y = 42;
	rightClips[ 2 ].w = 17;
	rightClips[ 2 ].h = 29;

	rightClips[ 3 ].x = 78;
	rightClips[ 3 ].y = 42;
	rightClips[ 3 ].w = 17;
	rightClips[ 3 ].h = 29;

	rightClips[ 4 ].x = 97;
	rightClips[ 4 ].y = 42;
	rightClips[ 4 ].w = 18;
	rightClips[ 4 ].h = 29;

	rightClips[ 5 ].x = 116;
	rightClips[ 5 ].y = 42;
	rightClips[ 5 ].w = 18;
	rightClips[ 5 ].h = 29;


	rightClips[ 6 ].x = 135;
	rightClips[ 6 ].y = 42;
	rightClips[ 6 ].w = 18;
	rightClips[ 6 ].h = 29;

	//Walking animation
	rightClips[ 7 ].x = 18;
	rightClips[ 7 ].y = 107;
	rightClips[ 7 ].w = 21;
	rightClips[ 7 ].h = 28;


	rightClips[ 8 ].x = 40;
	rightClips[ 8 ].y = 106;
	rightClips[ 8 ].w = 24;
	rightClips[ 8 ].h = 29;

	rightClips[ 9 ].x = 65;
	rightClips[ 9 ].y = 107;
	rightClips[ 9 ].w = 20;
	rightClips[ 9 ].h = 28;

	rightClips[ 10 ].x = 88;
	rightClips[ 10 ].y = 106;
	rightClips[ 10 ].w = 16;
	rightClips[ 10 ].h = 29;

	rightClips[ 11 ].x = 104;
	rightClips[ 11 ].y = 106;
	rightClips[ 11 ].w = 19;
	rightClips[ 11 ].h = 29;

	rightClips[ 12 ].x = 126;
	rightClips[ 12 ].y = 107;
	rightClips[ 12 ].w = 17;
	rightClips[ 12 ].h = 28;

	rightClips[ 13 ].x = 144;
	rightClips[ 13 ].y = 107;
	rightClips[ 13 ].w = 18;
	rightClips[ 13 ].h = 28;

	//Jumping animation
	rightClips[ 14 ].x = 15;
	rightClips[ 14 ].y = 318;
	rightClips[ 14 ].w = 23;
	rightClips[ 14 ].h = 30;

	rightClips[ 15 ].x = 41;
	rightClips[ 15 ].y = 317;
	rightClips[ 15 ].w = 24;
	rightClips[ 15 ].h = 31;

	rightClips[ 16 ].x = 65;
	rightClips[ 16 ].y = 317;
	rightClips[ 16 ].w = 22;
	rightClips[ 16 ].h = 31;

	//For when he is going left.
	//This is using the flipped image of the original,
	//where he is going right.
	leftClips[ 0 ].x = 345;
	leftClips[ 0 ].y = 42;
	leftClips[ 0 ].w = 18;
	leftClips[ 0 ].h = 29;

	leftClips[ 1 ].x = 324;
	leftClips[ 1 ].y = 42;
	leftClips[ 1 ].w = 18;
	leftClips[ 1 ].h = 29;

	leftClips[ 2 ].x = 306;
	leftClips[ 2 ].y = 42;
	leftClips[ 2 ].w = 18;
	leftClips[ 2 ].h = 29;

	leftClips[ 3 ].x = 287;
	leftClips[ 3 ].y = 42;
	leftClips[ 3 ].w = 17;
	leftClips[ 3 ].h = 29;

	leftClips[ 4 ].x = 267;
	leftClips[ 4 ].y = 42;
	leftClips[ 4 ].w = 18;
	leftClips[ 4 ].h = 29;

	leftClips[ 5 ].x = 248;
	leftClips[ 5 ].y = 42;
	leftClips[ 5 ].w = 18;
	leftClips[ 5 ].h = 29;


	leftClips[ 6 ].x = 229;
	leftClips[ 6 ].y = 42;
	leftClips[ 6 ].w = 18;
	leftClips[ 6 ].h = 29;

	leftClips[ 7 ].x = 343;
	leftClips[ 7 ].y = 107;
	leftClips[ 7 ].w = 21;
	leftClips[ 7 ].h = 28;


	leftClips[ 8 ].x = 318;
	leftClips[ 8 ].y = 106;
	leftClips[ 8 ].w = 24;
	leftClips[ 8 ].h = 29;

	leftClips[ 9 ].x = 297;
	leftClips[ 9 ].y = 107;
	leftClips[ 9 ].w = 20;
	leftClips[ 9 ].h = 28;

	leftClips[ 10 ].x = 278;
	leftClips[ 10 ].y = 106;
	leftClips[ 10 ].w = 16;
	leftClips[ 10 ].h = 29;

	leftClips[ 11 ].x = 259;
	leftClips[ 11 ].y = 106;
	leftClips[ 11 ].w = 19;
	leftClips[ 11 ].h = 29;

	leftClips[ 12 ].x = 239;
	leftClips[ 12 ].y = 107;
	leftClips[ 12 ].w = 17;
	leftClips[ 12 ].h = 28;

	leftClips[ 13 ].x = 220;
	leftClips[ 13 ].y = 107;
	leftClips[ 13 ].w = 18;
	leftClips[ 13 ].h = 28;

	leftClips[ 14 ].x = 344;
	leftClips[ 14 ].y = 318;
	leftClips[ 14 ].w = 23;
	leftClips[ 14 ].h = 30;

	leftClips[ 15 ].x = 317;
	leftClips[ 15 ].y = 317;
	leftClips[ 15 ].w = 24;
	leftClips[ 15 ].h = 31;

	leftClips[ 16 ].x = 295;
	leftClips[ 16 ].y = 317;
	leftClips[ 16 ].w = 22;
	leftClips[ 16 ].h = 31;
}

/*Mario 3 Tanuki sprites
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
}*/

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