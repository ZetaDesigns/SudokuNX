#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h>
#include "draw.hpp"
#include "switch.h"
#include "field.hpp"

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* textures[10];
SDL_Texture* texturesedit[10];
SDL_Surface* mainImage;
SDL_Texture* mainTexture;

SDL_Surface* oneImage;

SDL_Surface* twoImage;

SDL_Surface* threeImage;

SDL_Surface* fourImage;

SDL_Surface* fiveImage;

SDL_Surface* sixImage;

SDL_Surface* sevenImage;

SDL_Surface* eightImage;

SDL_Surface* nineImage;

SDL_Surface* oneeditImage;

SDL_Surface* twoeditImage;

SDL_Surface* threeeditImage;

SDL_Surface* foureditImage;

SDL_Surface* fiveeditImage;

SDL_Surface* sixeditImage;

SDL_Surface* seveneditImage;

SDL_Surface* eighteditImage;

SDL_Surface* nineeditImage;

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
	
	oneeditImage = IMG_Load("romfs:/1edit.png");
	texturesedit[1] = SDL_CreateTextureFromSurface(renderer, oneeditImage);

	twoeditImage = IMG_Load("romfs:/2edit.png");
	texturesedit[2] = SDL_CreateTextureFromSurface(renderer, twoeditImage);

	threeeditImage = IMG_Load("romfs:/3edit.png");
	texturesedit[3] = SDL_CreateTextureFromSurface(renderer, threeeditImage);

	foureditImage = IMG_Load("romfs:/4edit.png");
	texturesedit[4] = SDL_CreateTextureFromSurface(renderer, foureditImage);

	fiveeditImage = IMG_Load("romfs:/5edit.png");
	texturesedit[5] = SDL_CreateTextureFromSurface(renderer, fiveeditImage);

	sixeditImage = IMG_Load("romfs:/6edit.png");
	texturesedit[6] = SDL_CreateTextureFromSurface(renderer, sixeditImage);

	seveneditImage = IMG_Load("romfs:/7edit.png");
	texturesedit[7] = SDL_CreateTextureFromSurface(renderer, seveneditImage);

	eighteditImage = IMG_Load("romfs:/8edit.png");
	texturesedit[8] = SDL_CreateTextureFromSurface(renderer, eighteditImage);

	nineeditImage = IMG_Load("romfs:/9edit.png");
	texturesedit[9] = SDL_CreateTextureFromSurface(renderer, nineeditImage);

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
	SDL_RenderCopy(ren, tex, NULL, &dest); // render the texture}
}
void drawLine(SDL_Renderer* renderer, int x, int y, int w, int h, Uint8 r, Uint8 g, Uint8 b, Uint8 a) { //funtion to draw a line x, y, w, h, with a rgb color of red, green, blue, alpha  
	SDL_SetRenderDrawColor(renderer, r, g, b, a); //set the render color to r,g,b,a
	SDL_RenderDrawLine(renderer, x, y, w, h); //draw the line
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); //set the render color back to transparent
}

void drawGrid() {
	int r = 42;
	int g = 42;
	int b = 42;

	//outline
	drawLine(renderer, fieldZeroX, fieldZeroY, fieldZeroX + (9 * tileLength), fieldZeroY, r, g, b);
	drawLine(renderer, fieldZeroX, fieldZeroY, fieldZeroX, fieldZeroY + (9 * tileLength), r, g, b);
	drawLine(renderer, fieldZeroX, fieldZeroY + (9 * tileLength), fieldZeroX + (9 * tileLength), fieldZeroY + (9 * tileLength), r, g, b);
	drawLine(renderer, fieldZeroX + (9 * tileLength), fieldZeroY, fieldZeroX + (9 * tileLength), fieldZeroY + (9 * tileLength), r, g, b);
	//outline thickness
	drawLine(renderer, fieldZeroX, fieldZeroY + 1, fieldZeroX + (9 * tileLength), fieldZeroY + 1, r, g, b);
	drawLine(renderer, fieldZeroX + 1, fieldZeroY, fieldZeroX + 1, fieldZeroY + (9 * tileLength), r, g, b);
	drawLine(renderer, fieldZeroX, fieldZeroY + (9 * tileLength) + 1, fieldZeroX + (9 * tileLength), fieldZeroY + (9 * tileLength) + 1, r, g, b);
	drawLine(renderer, fieldZeroX + (9 * tileLength) + 1, fieldZeroY, fieldZeroX + (9 * tileLength) + 1, fieldZeroY + (9 * tileLength), r, g, b);

	for(int i = 0; i < 9; i++) {
		if (i == 3 || i == 6) {
			drawLine(renderer, fieldZeroX, fieldZeroY + i * tileLength, fieldZeroX + (9 * tileLength), fieldZeroY + i * tileLength, r, g, b);
			drawLine(renderer, fieldZeroX, fieldZeroY + i * tileLength + 1, fieldZeroX + (9 * tileLength), fieldZeroY + i * tileLength + 1, r, g, b);
		}
		else {
			drawLine(renderer, fieldZeroX, fieldZeroY + i * tileLength, fieldZeroX + (9 * tileLength), fieldZeroY + i * tileLength, r, g, b);
		}
	}
	for (int i = 0; i < 9; i++) {
		if (i == 3 || i == 6) {
			drawLine(renderer, fieldZeroX + i * tileLength, fieldZeroY, fieldZeroX + i * tileLength, fieldZeroY + (9 * tileLength), r, g, b);
			drawLine(renderer, fieldZeroX + i * tileLength + 1, fieldZeroY, fieldZeroX + i * tileLength + 1, fieldZeroY + (9 * tileLength), r, g, b);
		}
		else {
			drawLine(renderer, fieldZeroX + i * tileLength, fieldZeroY, fieldZeroX + i * tileLength, fieldZeroY + (9 * tileLength), r, g, b);
		}
	}
}
