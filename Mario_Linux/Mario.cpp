/*
Shane Satterfield
8-29-2012
Mario Clone
*/

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

#include "src/Units/Mario_Unit.h"

#include <string>
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

SDL_Rect camera;

SDL_Surface* screen = NULL;
SDL_Surface* background = NULL;
SDL_Surface* mar = NULL;

SDL_Event event;

SDL_Rect posOffset;

SDL_Surface* load_image(std::string filename){
	SDL_Surface* loadedImage = NULL;
	SDL_Surface* optimizedImage = NULL;
	loadedImage = IMG_Load(filename.c_str());
	if(loadedImage != NULL){
		optimizedImage = SDL_DisplayFormat(loadedImage);
		SDL_FreeSurface(loadedImage);
	}
	return optimizedImage;
}

bool init(){
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1){
		return false;
	}
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	if(screen == NULL){
		return false;
	}
	return true;
}

bool load_files(){
	background = load_image("res/test_world1-1.png");
	if(background == NULL)
		return false;
	mar = load_image("res/scaled_smb_mario_sheet.png");
	if(mar == NULL)
		return false;

	return true;
}

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination){
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(source, NULL, destination, &offset);
}

void cleanup(){
	SDL_FreeSurface(background);
	SDL_FreeSurface(mar);
	SDL_Quit();
}

void initVars(){
	camera.x = 0;
	camera.y = 0;
	posOffset.x = 0;
	posOffset.y = 0;
}

int main(int argc, char* argv[]){
	bool quit = false;
	if(init() == false)
		return 1;

	if(load_files() == false)
		return 1;

	initVars();

	Mario_Unit player(event);

	std::cout << player.loaded << std::endl;	
	while(!quit){
		while(SDL_PollEvent(&event)){
			if(event.type == SDL_QUIT){
				quit = true;
			}
		}
		SDL_Rect temp = player.get_rects();

		bool middle = false;
		//apply_surface(camera.x,camera.y,background, screen);
		if(temp.x <= SCREEN_WIDTH/2){
			posOffset.x = 0;
			posOffset.y = 0;
		}
		else if(temp.x > background->w - SCREEN_WIDTH/2){
			posOffset.x = (background->w - SCREEN_WIDTH) * -1;
		}
		else{
			posOffset.x = (temp.x - SCREEN_WIDTH/2 ) * -1;
			middle = true;
		}

		apply_surface(posOffset.x, posOffset.y, background, screen);

		//player.move(middle, SCREEN_WIDTH, SCREEN_HEIGHT);
		player.display(screen, background, SCREEN_WIDTH, SCREEN_HEIGHT, posOffset);

		//apply_surface(0,0,mar, screen);


		//handleScroll();


		if(SDL_Flip(screen) == -1){
			return 1;
		}
	}

	cleanup();
	return 0;
}