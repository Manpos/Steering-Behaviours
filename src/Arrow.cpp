#include "Arrow.h"

Arrow::Arrow() {};
Arrow::Arrow() {
	loadImage("../res/whiteArrow.png");
};

Arrow::~Arrow() {};

bool Arrow::loadImage(char *path) {
	
	SDL_Surface *image = IMG_Load(path);
	if (!image) {
		cout << "IMG_Load: " << IMG_GetError() << endl;
		return false;
	}

	arrowImage = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);

	sprite_h = image->h;
	sprite_w = image->w;

	if (image) SDL_FreeSurface(image);

	return true;
}

void Arrow::Draw(Vector2D origin, Vector2D target) {
	srcrect = { 0,0, sprite_w, sprite_h };
	dstrect = {}
}