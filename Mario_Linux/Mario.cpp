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
#include "src/Units/Enemies/Enemies.h"
#include "src/Units/Enemies/Enemy_Unit.h"	

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
	if(player.getRight() && temp.x + temp.w + posOffset.x > SCREEN_WIDTH/2){
		posOffset.x = ( temp.x + temp.w - SCREEN_WIDTH/2 ) * -1;
		if(posOffset.x > 0){
			posOffset.x = 0;
		}
		middle = true;
	}
	else if(player.getLeft() && temp.x + posOffset.x < SCREEN_WIDTH/2.5){
		posOffset.x = ( temp.x - SCREEN_WIDTH/2.5 ) * -1;
		if(posOffset.x > 0){
			posOffset.x = 0;
		}
		middle = true;
	}

	if(temp.y + temp.h > 2*SCREEN_HEIGHT/3){
		posOffset.y = (temp.y + temp.h - 2*SCREEN_HEIGHT/3) * -1;
	}
	else if(temp.y + temp.h < SCREEN_HEIGHT/3 && posOffset.y < SCREEN_HEIGHT/-3){
		posOffset.y = (temp.y + temp.h - 2*SCREEN_HEIGHT/3) * -1;
	}
	else if(posOffset.y > SCREEN_HEIGHT/ -3){
		posOffset.y = 0;
	}

	player.display(jump);
}



int main(int argc, char* argv[]){
	bool quit = false;
	if(init() == false)
		return 1;

	if(load_files() == false)
		return 1;

	bool jump = false;

	initVars();

	Tiles tiles(posOffset, screen, SCREEN_WIDTH, SCREEN_HEIGHT);
	Mario_Unit player(event, mar, SCREEN_WIDTH, SCREEN_HEIGHT, screen, posOffset);
	Enemies enemies(posOffset, screen);
	enemies.addEnemy(100,100,0);


	std::string location = "src/Level_Structure/Levels/";
	if(argc >= 2){
		location += + argv[1];
		if(tiles.load_tiles(location) == false)
			return 1;
	}
	if(argc < 2)
		if(tiles.load_tiles() == false)
			return 1;

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

		player.move(background, jump);
		dispMario(player, jump);
		enemies.show_enemies(SCREEN_WIDTH, SCREEN_HEIGHT);

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