#include <string.h>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <cstdlib>

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include <switch.h>
#include "draw.hpp"
#include "field.hpp"

int playerPosX = 0;
int playerPosY = 0;
int sudoku[9][9];
int sudokuedit[9][9];
bool isEditable;

std::vector<int> findRemaining(int board[9][9], int x, int y) {

	std::vector<int> remaining;

	int quadX = x / 3;
	int quadY = y / 3;

	for (int i = 1; i <= 9; i++) {
		remaining.push_back(i);
	}
	for (int rowItem = 0; rowItem < 9; rowItem++) {
		for (int i = 0; i < remaining.size(); i++) {
			if (remaining[i] == board[rowItem][x]) {
				remaining.erase(remaining.begin() + i);
			}
		}
		for (int i = 0; i < remaining.size(); i++) {
			if (remaining[i] == board[y][rowItem]) {
				remaining.erase(remaining.begin() + i);
			}
		}
	}

	for (int k = 0; k < 3; k++) {
		for (int l = 0; l < 3; l++) {
			for (int i = 0; i < remaining.size(); i++) {
				if (remaining[i] == sudoku[quadY * 3 + k][quadX * 3 + l]) {
					remaining.erase(remaining.begin() + i);
				}
			}
		}
	}

	return remaining;
}

bool createBoard(int board[9][9], int x, int y) {
	std::vector<int> fields = findRemaining(board, x, y);
	while (true) {
		if (fields.size() == 0) {
			return false;
		}
		int randomNumber = rand() % fields.size();
		int insert = fields[randomNumber];

		int newX = x;
		int newY = y;

		if (x == 8) {
			newX = 0;
			newY++;
		}
		else {
			newX++;
			newY = y;
		}
		board[y][x] = insert;
		if (newY == 9) {
			return true;
		}

		bool result = createBoard(board, newX, newY);

		if (result == false) {
			fields.erase(fields.begin() + randomNumber);
			board[y][x] = 0;
		}
		else {
			return true;
		}
	}
	return true;
}
bool takeAwayFields(int board[9][9], int count) {
	for (int i = 0; i < count; i++) {
		board[rand() % 9][rand() % 9] = 0;
	}
	return true;
}
int main(int argc, char **argv)
{
	SDL_Init(SDL_INIT_EVERYTHING); //init sdl
	IMG_Init(IMG_INIT_PNG); //init image lib
	TTF_Init();
	romfsInit();
	loadTextures();
	createBoard(sudoku, 0, 0);
	takeAwayFields(sudoku, 25);
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
		if (kDown & KEY_X) {
			for (int f = 0; f < 9; f++) {
				for (int g = 0; g < 9; g++) {
					sudoku[f][g] = 0;
				}
			}
			createBoard(sudoku, 0, 0);
			takeAwayFields(sudoku, 25);
			memcpy(sudokuedit, sudoku, 9 * 9 * sizeof(int));
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
				else if (sudokuedit[y][x] == sudoku[y][x]) {
					renderTexture(textures[index], renderer, fieldZeroX + (x * tileLength), fieldZeroY + (y * tileLength), -1, -1);
				}
				else {
					renderTexture(texturesedit[index], renderer, fieldZeroX + (x * tileLength), fieldZeroY + (y * tileLength), -1, -1);
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
