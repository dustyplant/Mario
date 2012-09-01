#include "SDL_BaseProg.h"

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

#include <string>

void SDL_BaseProg::apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clipper /* = NULL */){
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(source, clipper, destination, &offset);
}

SDL_Surface* SDL_BaseProg::load_image(std::string filename){
	SDL_Surface* loadedImage = NULL;
	SDL_Surface* optimizedImage = NULL;
	loadedImage = IMG_Load(filename.c_str());
	if(loadedImage != NULL){
		optimizedImage = SDL_DisplayFormat(loadedImage);
		SDL_FreeSurface(loadedImage);
	}
	return optimizedImage;
}