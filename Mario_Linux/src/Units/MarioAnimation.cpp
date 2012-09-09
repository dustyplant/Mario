#include "MarioAnimation.h"

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

MarioAnimation::MarioAnimation(){
	currentClip = 0;
}

void MarioAnimation::idle(){
	currentClip++;
	if(currentClip > 6 || currentClip < 0){
		currentClip = 0;
	}
}

void MarioAnimation::walk(){
	currentClip++;
	if(currentClip > 13 || currentClip < 7){
		currentClip = 7;
	}
}
/*
void MarioAnimation::run(){
	currentClip++;
	if(currentClip > 6 || currentClip < 0){
		currentClip = 0;
	}
}

void MarioAnimation::jump(){
	currentClip++;
	if(currentClip > 2 || currentClip < 0){
		currentClip = 0;
	}
}

void MarioAnimation::die(){
	currentClip++;
	if(currentClip > 1 || currentClip < 0){
		currentClip = 0;
	}
}*/
