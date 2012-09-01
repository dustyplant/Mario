#ifndef MARIO_UNIT_H
#define MARIO_UNIT_H

#include "../Entities/Object.h"
#include "../Level_Structure/Tile.h"

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

	bool jumping;
	int velocity;
	int yVel;
	int jumpCap;
	int upChuck;
	bool grounded;

	bool falling;
	bool check_collision(std::vector<Tile> &tileSet, SDL_Rect &posOffset);
	bool check_up_collision(std::vector<Tile> &tileSet, SDL_Rect &posOffset);
	bool check_down_collision(std::vector<Tile> &tileSet, SDL_Rect &posOffset);
	bool check_left_collision(std::vector<Tile> &tileSet, SDL_Rect &posOffset);
	bool check_right_collision(std::vector<Tile> &tileSet, SDL_Rect &posOffset);

	bool jumpingFunc(std::vector<Tile> &tileSet, SDL_Rect &posOffset);
	bool fallingFunc(std::vector<Tile> &tileSet, SDL_Rect &posOffset);
	bool check_grounded(std::vector<Tile> &tileSet, SDL_Rect &posOffset);

	int framer;
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;

public:
	Mario_Unit(SDL_Event &temp, SDL_Surface* sprite_sheet, int screenw, int screenh);

	//~Mario_Unit();

	void display(SDL_Surface* screen, SDL_Surface* background, SDL_Rect &posOffset, bool jump);
	void move(SDL_Surface* background, SDL_Rect &posOffset, bool jump, std::vector<Tile> tileSet);
	bool loaded;
	void jumper(bool jump, std::vector<Tile> &tileSet, SDL_Rect &posOffset);
};

#endif