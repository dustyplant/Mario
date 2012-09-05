#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

#include "src/Level_Structure/Tiles.h"
#include "src/Level_Structure/Tile.h"
#include "src/Entities/Object.h"
#include "src/Utilities/Timer.h"

#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

const int FRAMES_PER_SECOND = 60;

SDL_Surface* screen = NULL;

SDL_Event event;

SDL_Rect posOffset;

bool cap = true;

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
	return true;
}

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination){
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(source, NULL, destination, &offset);
}

void cleanup(){
	SDL_Quit();
}

void initVars(){
	posOffset.x = 0;
	posOffset.y = 0;
}

int main(int argc, char* args[]){
	std::cout << '2' << std::endl;
	Tiles tiles(posOffset, screen);
	std::cout << '3' << std::endl;
	tiles.addTile(0,400, tiles.clips[0].w, tiles.clips[0].h, 0);
	std::cout << '4' << std::endl;
	//tiles.load_tiles();
	bool quit = false;
	if(init() == false)
		return 1;

	std::cout << '5' << std::endl;

	if(load_files() == false)
		return 1;

	Timer fps;

	while(!quit){

		while(SDL_PollEvent(&event)){
			if(event.type == SDL_QUIT){
				quit = true;
			}
		}

		fps.start();

		SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0,0xFF,0xFF));
std::cout << '6' << std::endl;
		//tiles.displayTile(tiles.clips[0]);
		tiles.display();
std::cout << '7' << std::endl;
		if(SDL_Flip(screen) == -1)
			return 1;

		if(cap == true && fps.get_ticks() < 1000.f / FRAMES_PER_SECOND){
			SDL_Delay((1000.0/FRAMES_PER_SECOND) - fps.get_ticks());
		}

	}

	cleanup();
	return 0;
}