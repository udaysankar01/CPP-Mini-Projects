#include <iostream>
#include <raylib.h>
#include "game.h"

using namespace std;

int main() {

	Color darkBlue = { 44, 44, 127, 255 };
	InitWindow(300, 600, "Tetris");
	SetTargetFPS(60);

	Game game = Game();

	// game loop
	while (WindowShouldClose() == false)
	{	
		game.HandleInput();
		game.MoveBlockDown();
		BeginDrawing();
		ClearBackground(darkBlue);
		game.Draw();
		EndDrawing();
	}

	CloseWindow();
	return 0;
}