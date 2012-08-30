#ifndef MARIO_UNIT_H
#define MARIO_UNIT_H

class Mario_Unit: protected Killable, protected Object{
private:
	//Full size is 82 Marios.
	SDL_Rect clips[26];
	int currentClip;
	SDL_Rect pos;
	void set_clips();
public:
	Mario_Unit();

};

#endif