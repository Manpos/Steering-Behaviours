#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "SDL_SimpleApp.h"

using namespace std;

class Arrow {

	struct colorRGB {
		int r = 255;
		int g = 255;
		int b = 255;
	};

private:
	colorRGB color;

public:
	Arrow();
	~Arrow();

	void SetColor(int r, int g, int b);
	void Draw(Vector2D origin, Vector2D target);
	
};