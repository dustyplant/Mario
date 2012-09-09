#include "Enemies.h"
#include "Enemy_Unit.h"

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

Enemies::Enemies(SDL_Rect &camera){
	posOffset = camera;
	set_clips();
}

void Enemies::set_clips(){
	
}