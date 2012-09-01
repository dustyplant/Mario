#ifndef OBJECT_H
#define OBJECT_H

#include "../Utilities/SDL_BaseProg.h"
#include <vector>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

class Object: public SDL_BaseProg{
protected:
	bool impassable;
	bool per_pixel;
	SDL_Rect box;
	std::vector<SDL_Rect> boxes;
	SDL_Surface* image;

public:
	Object();
	Object(int x, int y, int w, int h);

	~Object();

	bool collision(SDL_Rect &rect);
	bool collision(std::vector<SDL_Rect> vec);
	void show(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clipper = NULL);
	SDL_Rect get_rects();
	std::vector<SDL_Rect> getVecRects();
};	

#endif