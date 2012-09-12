#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

#include "src/Level_Structure/Tiles.h"
#include "src/Level_Structure/Tile.h"
#include "src/Entities/Object.h"
#include "src/Utilities/Timer.h"
#include "src/Utilities/Coll.h"

#include <iostream>
#include <sstream>
#include <fstream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

const int FRAMES_PER_SECOND = 60;

const int GRID_SIZE = 16;

SDL_Surface* screen = NULL;
SDL_Event event;
SDL_Rect posOffset;

Coll coller;

int currentClip = 0;
int maxClip = 0;

std::vector<SDL_Rect> grid;

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

int search_grid(int x, int y){
	int bl = -1;
	for(int i = 0; i < grid.size(); i++){
		if(grid[i].x == x && grid[i].y == y){
			bl = i;
			break;
		}
	}
	return bl;
}

void placeTile(int tx, int ty, Tiles &tiles){
	int origin_x = ( (tx - posOffset.x)/GRID_SIZE) * GRID_SIZE;
	int origin_y = ( (ty - posOffset.y)/GRID_SIZE) * GRID_SIZE;

	int x = origin_x;
	int y = origin_y;
	bool bl = false;
	while(x - origin_x < tiles.clips[currentClip].w && y - origin_y < tiles.clips[currentClip].h){
		if( search_grid(x,y) != -1 ){
			bl = true;
			break;
		}
		if( (x + GRID_SIZE) - origin_x <= tiles.clips[currentClip].w  ){
			x += GRID_SIZE;
		}
		else if( (y + GRID_SIZE) - origin_y <= tiles.clips[currentClip].h ){
			y+= GRID_SIZE;
		}

	}
	if(!bl){
		x = origin_x;
		y = origin_y;
		tiles.addTile(x, y, tiles.clips[currentClip].w, tiles.clips[currentClip].w, currentClip);
		while(x - origin_x < tiles.clips[currentClip].w && y - origin_y < tiles.clips[currentClip].h){
			SDL_Rect temp;
			temp.x = x;
			temp.y = y;
			temp.w = GRID_SIZE;
			temp.h = GRID_SIZE;
			grid.push_back(temp);
			if( (x + GRID_SIZE) - origin_x <= tiles.clips[currentClip].w  ){
				x += GRID_SIZE;
			}
			else if( (y + GRID_SIZE) - origin_y <= tiles.clips[currentClip].h ){
				y+= GRID_SIZE;
			}
		}
	}
	else{
		int num = search_grid(origin_x, origin_y);
		if(num != -1){
			grid.erase(grid.begin() + num);
			for(int i = 0; i < tiles.get_tileSet().size(); i++){
				if(tiles.get_tileSet()[i].get_box().x == origin_x && tiles.get_tileSet()[i].get_box().y == origin_y){
					tiles.get_tileSet().erase( tiles.get_tileSet().begin() + i );
					i--;
				}
			}
		}
	}
}

void set_camera(Tiles &tiles){
	int x, y;
	SDL_GetMouseState(&x, &y);
	if(x > SCREEN_WIDTH - SCREEN_WIDTH/8){
		posOffset.x -= 3;
	}
	if(x < SCREEN_WIDTH/8){
		posOffset.x += 3;
		if(posOffset.x  > 0){
			posOffset.x = 0;
		}
	}
	if(y > SCREEN_HEIGHT - SCREEN_HEIGHT/8){
		posOffset.y -= 3;
	}
	if(y < SCREEN_HEIGHT/8){
		posOffset.y += 3;
		if(posOffset.y > 0)
			posOffset.y = 0;
	}
}

int main(int argc, char* argv[]){
	bool quit = false;
	if(init() == false)
		return 1;

	if(load_files() == false)
		return 1;

	posOffset.x = 0; 
	posOffset.y = 0;
	posOffset.w = SCREEN_WIDTH;
	posOffset.h = SCREEN_HEIGHT;
	Tiles tiles(posOffset, screen);
	std::string location = "src/Level_Structure/Levels/";
	if(argc >= 2){
		location += + argv[1];
		tiles.load_tiles(location);
	}
	if(argc < 2)
		tiles.load_tiles();

	maxClip = sizeof(tiles.clips)/sizeof(tiles.clips[0]);
	Timer fps;

	while(!quit){

		fps.start();
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
			if(event.type == SDL_MOUSEMOTION){
				int x, y;
				SDL_GetMouseState(&x, &y);
				std::stringstream streamer;
				streamer << "X: " << (x - posOffset.x)/GRID_SIZE * GRID_SIZE << "\tY: " << (y - posOffset.y)/GRID_SIZE * GRID_SIZE;
				SDL_WM_SetCaption(streamer.str().c_str(), NULL);
				
				
			}
			if(event.type == SDL_MOUSEBUTTONDOWN){
				if(event.button.button == SDL_BUTTON_WHEELUP){
					currentClip--;
					if(currentClip < 0)
						currentClip = maxClip - 1;
				}
				if(event.button.button == SDL_BUTTON_WHEELDOWN){
					currentClip++;
					if(currentClip >= maxClip)
						currentClip = 0;
				}
			}
		}
		set_camera(tiles);


		SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0,0xFF,0xFF));
		int tempClipPos = 0;
		for(int i = 0, posx = 2; posx < SCREEN_WIDTH; i++ ){
			tempClipPos = currentClip + i;
			if(tempClipPos < 0){
				tempClipPos += maxClip;
			}
			if(tempClipPos > maxClip - 1){
				tempClipPos = tempClipPos - maxClip;
			}
			tiles.displayTile(tempClipPos, posx);
			posx += tiles.clips[tempClipPos].w + 2;
		}
		//tiles.displayTile(1060, 0);
		tiles.display();
		if(SDL_Flip(screen) == -1)
			return 1;

		if(cap == true && fps.get_ticks() < 1000.f / FRAMES_PER_SECOND){
			SDL_Delay((1000.0/FRAMES_PER_SECOND) - fps.get_ticks());
		}

	}

	//Saving the level.
	location = "src/Level_Structure/Levels/";
	if(argc >= 3){
		location += argv[2];
	}
	else{
		location += "test_level.txt";
	}
	std::ofstream file;
	file.open(location.c_str());
	std::vector<Tile> vec = tiles.get_tileSet();

	for(int i = 0; i < vec.size(); i++){
		SDL_Rect temp = vec[i].get_box();
		file << temp.x << '#' << temp.y << '#' << vec[i].getClip();
		if(i+1 < vec.size())
			file << '\n';
	}

	file.close();

	cleanup();
	return 0;
}