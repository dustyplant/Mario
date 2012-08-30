/*
Shane Satterfield
8-29-2012
Mario Clone
*/

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <string>
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

SDL_Rect camera;

SDL_Surface* screen = NULL;
SDL_Surface* background = NULL;

SDL_Event event;

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
	SDL_Quit();
}

void initVars(){
	camera.x = 0;
	camera.y = 0;
}

void handleScroll(){
	Uint8* keystates = SDL_GetKeyState(NULL);
	if(keystates[SDLK_RIGHT] && abs(camera.x) <  background->w - SCREEN_WIDTH ){
		camera.x -= 10;
		if(abs(camera.x) >  background->w - SCREEN_WIDTH ){
			camera.x = (background->w - SCREEN_WIDTH) * -1;
		}
	}
	if(keystates[SDLK_LEFT] && camera.x < 0 ){
		camera.x += 10;
		if(camera.x > 0){
			camera.x = 0;
		}
	}
}

int main(int argc, char* argv[]){
	bool quit = false;
	if(init() == false)
		return 1;

	if(load_files() == false)
		return 1;

	initVars();


	while(!quit){
		while(SDL_PollEvent(&event)){
			if(event.type == SDL_QUIT){
				quit = true;
			}
		}
		
		handleScroll();

		apply_surface(camera.x,camera.y,background, screen);

		if(SDL_Flip(screen) == -1){
			return 1;
		}
	}

	cleanup();
	return 0;
}