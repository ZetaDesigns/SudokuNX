#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Texture* textures[10];
extern SDL_Surface* mainImage;
extern SDL_Texture* mainTexture;

extern SDL_Surface* oneImage;

extern SDL_Surface* twoImage;

extern SDL_Surface* threeImage;

extern SDL_Surface* fourImage;

extern SDL_Surface* fiveImage;

extern SDL_Surface* sixImage;

extern SDL_Surface* sevenImage;

extern SDL_Surface* eightImage;

extern SDL_Surface* nineImage;

extern SDL_Surface* frameImage;
extern SDL_Texture* frameTexture;

extern void loadTextures();

extern void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);

extern void drawGrid();

extern void drawLine(SDL_Renderer* renderer, int x, int y, int w, int h, Uint8 r = 0, Uint8 g = 255, Uint8 b = 0, Uint8 a = 255);
