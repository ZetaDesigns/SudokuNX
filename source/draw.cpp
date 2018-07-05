#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h>
#include "draw.hpp"
#include "switch.h"

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* textures[10];

SDL_Surface* mainImage;
SDL_Texture* mainTexture;

SDL_Surface* oneImage;

SDL_Surface* twoImage;

SDL_Surface* threeImage;

SDL_Surface* fourImage;

SDL_Surface* fiveImage;

SDL_Surface* sixImage;
SDL_Texture* sixTexture;

SDL_Surface* sevenImage;

SDL_Surface* eightImage;

SDL_Surface* nineImage;

SDL_Surface* frameImage;
SDL_Texture* frameTexture;

void loadTextures() {
	// Window init
	window = SDL_CreateWindow("Sudoku", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);
	// Renderer init
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

	mainImage = IMG_Load("romfs:/main.png");
	mainTexture = SDL_CreateTextureFromSurface(renderer, mainImage);

	oneImage = IMG_Load("romfs:/1.png");
	textures[1] = SDL_CreateTextureFromSurface(renderer, oneImage);

	twoImage = IMG_Load("romfs:/2.png");
	textures[2] = SDL_CreateTextureFromSurface(renderer, twoImage);

	threeImage = IMG_Load("romfs:/3.png");
	textures[3] = SDL_CreateTextureFromSurface(renderer, threeImage);

	fourImage = IMG_Load("romfs:/4.png");
	textures[4] = SDL_CreateTextureFromSurface(renderer, fourImage);

	fiveImage = IMG_Load("romfs:/5.png");
	textures[5] = SDL_CreateTextureFromSurface(renderer, fiveImage);

	sixImage = IMG_Load("romfs:/6.png");
	textures[6] = SDL_CreateTextureFromSurface(renderer, sixImage);

	sevenImage = IMG_Load("romfs:/7.png");
	textures[7] = SDL_CreateTextureFromSurface(renderer, sevenImage);

	eightImage = IMG_Load("romfs:/8.png");
	textures[8] = SDL_CreateTextureFromSurface(renderer, eightImage);

	nineImage = IMG_Load("romfs:/9.png");
	textures[9] = SDL_CreateTextureFromSurface(renderer, nineImage);

	frameImage = IMG_Load("romfs:/frame.png");
	frameTexture = SDL_CreateTextureFromSurface(renderer, frameImage);

} 

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h) {

	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	dest.w = w - 1;
	dest.h = h - 1;

	if (w == -1 || h == -1) {
		SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h); //if w and h not set get texture w and h
	}
	SDL_RenderCopy(ren, tex, NULL, &dest); // render the texture
}
