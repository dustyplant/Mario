#ifndef ENEMIES_H	
#define ENEMIES_H

#include "Enemy_Unit.h"
#include "../../Entities/Object.h"

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

class Enemies: public Object{
private:
	std::vector<Enemy_Unit> unitsList;
	SDL_Rect *posOffset;
	SDL_Surface *screen;
	SDL_Rect **clips;
	int frame;
	void set_clips();

public:
	Enemies(SDL_Rect &camera, SDL_Surface *tScreen);
	void addEnemy(int x, int y, int type);
	std::vector<Enemy_Unit> getUnitList();
	void show_enemies(int screen_width, int screen_height);
};

#endif