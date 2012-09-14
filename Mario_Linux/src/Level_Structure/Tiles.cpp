#include "Tiles.h"
#include "Tile.h"
#include "../Entities/Object.h"

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <vector>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

std::vector<Tile> Tiles::tileSet;

Tiles::Tiles(SDL_Rect &tposOffset, SDL_Surface* tScreen, int screen_width, int screen_height){
	image = load_image("res/tilesfix.png");
	if(image == NULL)
		std::cout << '1' << std::endl;
	screen = tScreen;
	posOffset = &tposOffset;
	set_clips();
	this->screen_width = screen_width;
	this->screen_height = screen_height;
}
void Tiles::display(){
	for(int i = 0; i < tileSet.size(); ++i){
		SDL_Rect temp = tileSet[i].get_box();
		if(temp.x + temp.w + posOffset->x > 0 && temp.x  + posOffset->x < screen_width){
			if(temp.y + temp.h + posOffset->y > 0 && temp.y  + posOffset->y < screen_height){
				show(temp.x + posOffset->x, temp.y + posOffset->y, image, screen, &clips[tileSet[i].getClip()]);
			}
		}
	}
}

void Tiles::displayTile(int clipper, int x){
	show(x, 0, image, screen, &clips[clipper]);
}

void Tiles::addTile(int x, int y, int w, int h, int type){
	Tile temp(x, y, w, h, type);
	tileSet.push_back(temp);
}
/* The member is now static and doesn't need a get function.
std::vector<Tile> &Tiles::get_tileSet(){
	return tileSet;
}*/

bool Tiles::load_tiles(std::string filename){
	/*
	addTile(0,400,clips[0].w, clips[0].h, 0);
	int i;
	for(i = 1; i < 100; i++)
		addTile(tileSet[i-1].get_box().x + tileSet[i-1].get_box().w, tileSet[i-1].get_box().y, clips[0].w, clips[0].h, 0);
	//for(; i < 23; i++)
	//	addTile(tileSet[i-1].get_box().x + tileSet[i-1].get_box().w, tileSet[i-1].get_box().y - 10, clips[0].w, clips[0].h, 0);
	addTile(100, 300, clips[0].w, clips[0].h, 0);
	i++;
	addTile(tileSet[i-1].get_box().x + tileSet[i-1].get_box().w, tileSet[i-1].get_box().y, clips[0].w, clips[0].h, 0);
	i++;

	addTile(200, 200, clips[0].w, clips[0].h, 0);
	i++;
	addTile(tileSet[i-1].get_box().x + tileSet[i-1].get_box().w, tileSet[i-1].get_box().y, clips[0].w, clips[0].h, 0);

	return true;
	*/

	std::ifstream file;
	file.open(filename.c_str());
	if(file.is_open()){

		std::string str;
		std::string tempstr;
		SDL_Rect loader_temp;
		int typer = 0;

		while( !(file.eof()) ){
			getline(file, str);
			for(int i = 0, j = 0; j < 3; j++){
				tempstr = "";
				for(; i < str.size(); i++){
					if(str[i] == '#'){
						i++;
						break;
					}
					tempstr+= str[i];
				}
				switch(j){
					case 0:
						loader_temp.x = atoi(tempstr.c_str());
						break;
					case 1:
						loader_temp.y = atoi(tempstr.c_str());
						break;
					case 2:
						typer = atoi(tempstr.c_str());
						break;
				}
			}
			addTile(loader_temp.x, loader_temp.y, clips[typer].w, clips[typer].h, typer);
		}
		file.close();
	}
	else{
		std::cout << "Unable to open Level file." << std::endl;
	}

	return true;
}

void Tiles::set_clips(){
	/*
	clips[0].x = 154;
	clips[0].y = 99;
	clips[0].w = 16;
	clips[0].h = 16;

	clips[1].x = 137;
	clips[1].y = 99;
	clips[1].w = 16;
	clips[1].h = 16;

	clips[2].x = 171;
	clips[2].y = 99;
	clips[2].w = 16;
	clips[2].h = 16;
	*/
	const int SPACES = 18;
	int i = 0;
	for(int x = 2, y = 2; y <= 398 && i < 967; x += SPACES, i++){
		if(x > 756){
			x = 2;
			y+= SPACES;
		}
		clips[i].x = x;
		clips[i].y = y;
		clips[i].w = SPACES-2;
		clips[i].h = SPACES-2;
	}
}