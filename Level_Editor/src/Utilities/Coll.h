#ifndef COLL_H
#define COLL_H

#include "../Level_Structure/Tile.h"
#include "../Level_Structure/Tiles.h"

#include <vector>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

class Coll{

public:
	bool check_collision(SDL_Rect &box, std::vector<Tile> &tileSet, SDL_Rect &posOffset);
	bool check_up_collision(SDL_Rect &box, std::vector<Tile> &tileSet, SDL_Rect &posOffset);
	bool check_down_collision(SDL_Rect &box, std::vector<Tile> &tileSet, SDL_Rect &posOffset);
	bool check_left_collision(SDL_Rect &box, std::vector<Tile> &tileSet, SDL_Rect &posOffset);
	bool check_right_collision(SDL_Rect &box, std::vector<Tile> &tileSet, SDL_Rect &posOffset);
	bool check_grounded(SDL_Rect &box, std::vector<Tile> &tileSet, SDL_Rect &posOffset);

	bool check_collision(SDL_Rect &box, std::vector<Enemy_Unit> &enemySet, SDL_Rect &posOffset);
	bool check_up_collision(SDL_Rect &box, std::vector<Enemy_Unit> &enemySet, SDL_Rect &posOffset);
	bool check_down_collision(SDL_Rect &box, std::vector<Enemy_Unit> &enemySet, SDL_Rect &posOffset);
	bool check_left_collision(SDL_Rect &box, std::vector<Enemy_Unit> &enemySet, SDL_Rect &posOffset);
	bool check_right_collision(SDL_Rect &box, std::vector<Enemy_Unit> &enemySet, SDL_Rect &posOffset);
	bool check_grounded(SDL_Rect &box, std::vector<Enemy_Unit> &enemySet, SDL_Rect &posOffset);
};

#endif