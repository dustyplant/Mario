#include "Mario_Unit.h"
#include "Object.h"
#include "Killable.h"
#include <vector>

Mario_Unit::Mario_Unit(){
	currentClip = 0;
	set_clips();
	box.x = 0;
	box.y = clips[currentClip].h;
}

Mario_Unit::Mario_Unit(int x, int y){
	currentClip = 0;
	set_clips();
	box.x = x;
	box.y = y;
}

Mario_Unit::Mario_Unit(int x, int y, int starting){
	if(starting > 0 && starting < sizeof(clips)/sizeof(clips[0]))
		currentClip = starting;
	else
		current = 0;
	set_clips();
	box.x = x;
	box.y = y;
}

void Mario_Unit::set_clips(){
	clips[ 0 ].x = 58;
	clips[ 0 ].y = 0;
	clips[ 0 ].w = 34;
	clips[ 0 ].h = 32;

	clips[ 1 ].x = 120;
	clips[ 1 ].y = 0;
	clips[ 1 ].w = 28;
	clips[ 1 ].h = 32;

	clips[ 2 ].x = 178;
	clips[ 2 ].y = 0;
	clips[ 2 ].w = 32;
	clips[ 2 ].h = 32;

	clips[ 3 ].x = 242;
	clips[ 3 ].y = 0;
	clips[ 3 ].w = 24;
	clips[ 3 ].h = 32;

	clips[ 4 ].x = 300;
	clips[ 4 ].y = 0;
	clips[ 4 ].w = 28;
	clips[ 4 ].h = 30;

	clips[ 5 ].x = 362;
	clips[ 5 ].y = 0;
	clips[ 5 ].w = 26;
	clips[ 5 ].h = 32;

	clips[ 6 ].x = 422;
	clips[ 6 ].y = 0;
	clips[ 6 ].w = 26;
	clips[ 6 ].h = 32;

	clips[ 7 ].x = 482;
	clips[ 7 ].y = 0;
	clips[ 7 ].w = 28;
	clips[ 7 ].h = 30;

	clips[ 8 ].x = 544;
	clips[ 8 ].y = 0;
	clips[ 8 ].w = 24;
	clips[ 8 ].h = 32;

	clips[ 9 ].x = 600;
	clips[ 9 ].y = 0;
	clips[ 9 ].w = 32;
	clips[ 9 ].h = 32;

	clips[ 10 ].x = 662;
	clips[ 10 ].y = 0;
	clips[ 10 ].w = 28;
	clips[ 10 ].h = 32;

	clips[ 11 ].x = 718;
	clips[ 11 ].y = 0;
	clips[ 11 ].w = 34;
	clips[ 11 ].h = 32;
}