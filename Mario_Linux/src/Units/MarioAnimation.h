#ifndef MARIOANIMATION_H
#define MARIOANIMATION_H

#include <vector>
#include <iostream>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

class MarioAnimation{
public:
	int currentClip;
	MarioAnimation();
	void idle();
	void walk();
	/*void run();
	void jump();
	void die();*/
};

#endif