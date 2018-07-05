#include <string.h>
#include <stdio.h>

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include <switch.h>
#include "draw.hpp"
#include "field.hpp"

int playerPosX = 0;
int playerPosY = 0;
int sudoku[9][9] = {0,1,9, 0,0,2, 0,0,0,
					4,7,0, 6,9,0, 0,0,1,
					0,0,0, 4,0,0, 0,9,0,
					
					8,9,4, 5,0,7, 0,0,0,
					0,0,0, 0,0,0, 0,0,0,
					0,0,0, 2,0,1, 9,5,8,

					0,5,0, 0,0,6, 0,0,0,
					6,0,0, 0,2,8, 0,7,9,
					0,0,0, 1,0,0, 8,6,0};
int sudokuedit[9][9];
bool isEditable;

int main(int argc, char **argv)
{
	SDL_Init(SDL_INIT_EVERYTHING); //init sdl
	IMG_Init(IMG_INIT_PNG); //init image lib
	TTF_Init();
	romfsInit();
	loadTextures();
	memcpy(sudokuedit, sudoku, 9 * 9 * sizeof(int)); // int is a POD
    // Main loop
    while(appletMainLoop())
    {
        //Scan all the inputs. This should be done once for each frame
        hidScanInput();

        //hidKeysDown returns information about which buttons have been just pressed (and they weren't in the previous frame)
        u64 kDown = hidKeysDown(CONTROLLER_P1_AUTO);

        if (kDown & KEY_PLUS) break; // break in order to return to hbmenu

		isEditable = false;
		if (sudoku[playerPosY][playerPosX] == 0) {
			isEditable = true;
		}
		if (kDown & KEY_A) {
			if (isEditable) {
				if (sudokuedit[playerPosY][playerPosX] >= 9) {
					continue;
				}
				else {
					sudokuedit[playerPosY][playerPosX]++;
				}
			}
		}
		if (kDown & KEY_B) {
			if (isEditable) {
				if (sudokuedit[playerPosY][playerPosX] <= 0) {
					continue;
				}
				else {
					sudokuedit[playerPosY][playerPosX]--;
				}
			}
		}
		if (kDown & KEY_DRIGHT || kDown & KEY_LSTICK_RIGHT || kDown & KEY_RSTICK_RIGHT) {
			if (playerPosX < 8) {
				playerPosX++;
			}
		}
		if (kDown & KEY_DLEFT || kDown & KEY_LSTICK_LEFT || kDown & KEY_RSTICK_LEFT) {
			if (playerPosX > 0) {
				playerPosX--;
			}
		}
		if (kDown & KEY_DDOWN || kDown & KEY_LSTICK_DOWN || kDown & KEY_RSTICK_DOWN) {
			if (playerPosY < 8) {
				playerPosY++;
			}
		}
		if (kDown & KEY_DUP || kDown & KEY_LSTICK_UP || kDown & KEY_RSTICK_UP) {
			if (playerPosY > 0) {
				playerPosY--;
			}
		}

		SDL_RenderClear(renderer);
		renderTexture(mainTexture, renderer, 0, 0, 1280, 720);
		drawGrid();
		for (int x = 0; x < 9; x++) {
			for (int y = 0; y < 9; y++) {
				int index = sudokuedit[y][x];
				if (index == 0) {
					continue;
				}
				else {
					renderTexture(textures[index], renderer, fieldZeroX + (x * tileLength), fieldZeroY + (y * tileLength), -1, -1);
				}
			}
		}
		renderTexture(frameTexture, renderer, fieldZeroX+(playerPosX * tileLength), fieldZeroY + (playerPosY * tileLength), -1, -1);
		SDL_RenderPresent(renderer); //show renderer on screen
    }

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_DestroyTexture(mainTexture);
	Mix_CloseAudio();
	romfsExit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
    return 0;
}
