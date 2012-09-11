#include "Enemies.h"
#include "Enemy_Unit.h"
#include "../../Entities/Object.h"

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

Enemies::Enemies(SDL_Rect &camera, SDL_Surface *tScreen){
	posOffset = &camera;
	screen = tScreen;
	image = load_image("res/smb_enemies_sheet.png");
	frame = 0;
	int size = 1;
	clips = new SDL_Rect*[size];
	for(int i = 0; i < size; i++){
		clips[i] = new SDL_Rect[3];
	}

	set_clips();
}

void Enemies::addEnemy(int x, int y, int type){
	Enemy_Unit temp(x,y, type, 0, clips[type], posOffset, image, screen);
	unitsList.push_back(temp);
}

std::vector<Enemy_Unit> Enemies::getUnitList(){
	return unitsList;
}

void Enemies::show_enemies(int screen_width, int screen_height){
	for(int i = 0; i < unitsList.size(); i++){
		//show(unitsList[i].get_box().x + posOffset->x, unitsList[i].get_box().y + posOffset->y, image, screen, clips[unitsList[i].get_type()]);
		unitsList[i].move(frame);
		unitsList[i].display(screen_width, screen_height);
	}
	frame++;
	if(frame >= 60){
		frame = 0;
	}
}

void Enemies::set_clips(){
	clips[0][0].x = 0;
	clips[0][0].y = 4;
	clips[0][0].w = 16;
	clips[0][0].h = 16;

	clips[0][1].x = 30;
	clips[0][1].y = 4;
	clips[0][1].w = 16;
	clips[0][1].h = 16;

	clips[0][2].x = 66;
	clips[0][2].y = 8;
	clips[0][2].w = 16;
	clips[0][2].h = 8;
}