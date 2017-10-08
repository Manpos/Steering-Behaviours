#include "Arrow.h"

Arrow::Arrow() {

};

Arrow::~Arrow() {};

void Arrow::SetColor(int r, int g, int b) {
	color.r = r;
	color.g = g;
	color.b = b;
}

void Arrow::Draw(Vector2D origin, Vector2D target) {
	SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), color.r, color.g, color.b, 255);
	SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), (int)origin.x, (int)origin.y, (int)(target.x), (int)(target.y));
}