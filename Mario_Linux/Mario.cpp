/*
Shane Satterfield
Started: 8-29-2012
Mario Clone
*/

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

#include "src/Units/Mario_Unit.h"
#include "src/Utilities/Timer.h"
#include "src/Level_Structure/Tiles.h"

#include <string>
#include <iostream>
#include <vector>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

const int FRAMES_PER_SECOND = 60;

SDL_Rect camera;

SDL_Surface* screen = NULL;
SDL_Surface* background = NULL;
SDL_Surface* mar = NULL;

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

void dispMario(Mario_Unit &player, bool jump){
	SDL_Rect temp = player.get_rects();

	bool middle = false;
	
	if(temp.x <= SCREEN_WIDTH/2){
		posOffset.x = 0;
		posOffset.y = 0;
	}
	else{
		posOffset.x = (temp.x - SCREEN_WIDTH/2 ) * -1;
		middle = true;
	}


	player.display(posOffset, jump);
}



int main(int argc, char* argv[]){
	bool quit = false;
	if(init() == false)
		return 1;

	if(load_files() == false)
		return 1;

	bool jump = false;

	initVars();

	Mario_Unit player(event, mar, SCREEN_WIDTH, SCREEN_HEIGHT, screen);
	Tiles tiles(posOffset, screen);
	tiles.load_tiles();

	std::cout << player.loaded << std::endl;	
	Timer fps;
	while(!quit && player.alive){
		fps.start();
		
		while(SDL_PollEvent(&event)){
			if(event.type == SDL_QUIT){
				quit = true;
			}
			if(event.type = SDL_KEYUP){
				switch(event.key.keysym.sym){
					case SDLK_SPACE:
						jump = true;
						break;
				}
			}
		}

		SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0,0,0));
		//apply_surface(posOffset.x, posOffset.y, background, screen);

		tiles.display();

		player.move(background, posOffset, jump, tiles.get_tileSet());
		dispMario(player, jump);

		jump = false;

		if(SDL_Flip(screen) == -1){
			return 1;
		}

		if(cap == true && fps.get_ticks() < 1000.f / FRAMES_PER_SECOND){
			SDL_Delay((1000.0/FRAMES_PER_SECOND) - fps.get_ticks());
		}
	}

	cleanup();
	return 0;
}