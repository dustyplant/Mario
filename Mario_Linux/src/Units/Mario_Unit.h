#ifndef MARIO_UNIT_H
#define MARIO_UNIT_H

#include "Mario_Unit.h"
#include "../Entities/Object.h"
//#include "../Entities/Killable.h"
#include "../Entities/SDL_BaseProg.h"
#include <vector>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

class Mario_Unit: public Object{
private:
	//Full size is 82 Marios.
	SDL_Rect clips[26];
	int currentClip;
	bool goingRight;
	bool goingLeft;
	void set_clips();
	SDL_Event event;
public:
	Mario_Unit(SDL_Event &temp);
	Mario_Unit(int x, int y);
	Mario_Unit(int x, int y, int starting);

	~Mario_Unit();

	void display(SDL_Surface* screen, bool middle, int SCREEN_WIDTH, int SCREEN_HEIGHT);
	void move(bool middle, int SCREEN_WIDTH, int SCREEN_HEIGHT);
	bool loaded;
};

#endif