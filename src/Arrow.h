#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "SDL_SimpleApp.h"

using namespace std;

class Arrow {
private:
	SDL_Texture *arrowImage;
	SDL_Rect srcrect, dstrect;
	int sprite_w, sprite_h;
public:
	Arrow();
	~Arrow();
	bool loadImage(char* path);
	void Draw(Vector2D origin, Vector2D target);
	
};