#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

#include "src/Level_Structure/Tiles.h"
#include "src/Level_Structure/Tile.h"
#include "src/Entities/Object.h"
#include "src/Utilities/Timer.h"
#include "src/Utilities/Coll.h"

#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

const int FRAMES_PER_SECOND = 60;

SDL_Surface* screen = NULL;
SDL_Event event;
SDL_Rect posOffset;

Coll coller;

int currentType = 0;

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

void placeTile(int tx, int ty, Tiles &tiles){
	int x = tx;
	int y = ty;
	SDL_Rect box;
	box.x = x;
	box.y = y;
	box.w = tiles.clips[0].w;
	box.h = tiles.clips[0].h;

	std::cout << tiles.get_tileSet().size() << std::endl;
	int counter = 0;
	while(coller.check_collision(box, tiles.get_tileSet(), posOffset) ){
		std::cout << 0 << std::endl;
		if(coller.check_up_collision(box, tiles.get_tileSet(), posOffset)){
			box.y++;
			std::cout << 1 << std::endl;
		}
		else if(coller.check_down_collision(box, tiles.get_tileSet(), posOffset)){
			box.y--;
			std::cout << 2 << std::endl;
		}
		else if(coller.check_left_collision(box, tiles.get_tileSet(), posOffset)){
			box.x--;
			std::cout << 3 << std::endl;
		}
		else if(coller.check_right_collision(box, tiles.get_tileSet(), posOffset)){
			box.x++;
			std::cout << 4 << std::endl;
		}
		else{
			box.x++;
			box.y--;
		}
		std::cout << "Counter: " << ++counter << std::endl;
	}
	std::cout << 5 << std::endl;
	tiles.addTile(box.x, box.y, tiles.clips[0].w, tiles.clips[0].h, 0);
	std::cout << 6 << std::endl;
}

int main(int argc, char* args[]){
	bool quit = false;
	if(init() == false)
		return 1;


	if(load_files() == false)
		return 1;

	Tiles tiles(posOffset, screen);
	tiles.load_tiles();

	Timer fps;

	while(!quit){

		while(SDL_PollEvent(&event)){
			if(event.type == SDL_QUIT){
				quit = true;
			}
			if(event.type == SDL_MOUSEBUTTONUP){
				
				if(event.button.button == SDL_BUTTON_LEFT){
					int x = event.button.x;
					int y = event.button.y;

					placeTile(x,y, tiles);

				}
			}
		}

		fps.start();

		SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0,0xFF,0xFF));
		//tiles.displayTile(tiles.clips[0]);
		tiles.display();
		if(SDL_Flip(screen) == -1)
			return 1;

		if(cap == true && fps.get_ticks() < 1000.f / FRAMES_PER_SECOND){
			SDL_Delay((1000.0/FRAMES_PER_SECOND) - fps.get_ticks());
		}

	}

	cleanup();
	return 0;
}