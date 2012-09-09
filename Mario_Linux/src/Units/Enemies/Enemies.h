#ifndef ENEMIES_H	
#define ENEMIES_H

class Enemies{
private:
	std::vector<Enemy_Unit> unitsList;
	SDL_Rect *posOffset;
	SDL_Rect arr[1][1];
	void set_clips();
	bool load_files();

public:
	Enemies(SDL_Rect &camera);
	void addEnemy(int x, int y, int type, SDL_Rect &clipSet);
	
};

#endif