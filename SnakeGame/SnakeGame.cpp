#include <iostream>
#include <raylib.h>

using namespace std;

Color Green = { 173, 204, 96, 255 };
Color DarkGreen = { 43, 51, 24, 255 };

int cellSize = 30;
int cellCount = 25;

class Food
{

public:
	Vector2 position = { 5, 6 };

	void Draw()
	{
		DrawRectangle(position.x * cellSize, position.y * cellSize, cellSize, cellSize, DarkGreen);
	}
};

int main()
{

	cout << "Starting the game..." << endl;
	InitWindow(cellSize * cellCount, cellSize * cellCount, "Snake Game");
	SetTargetFPS(60);

	Food food = Food();

	// game loop
	while (WindowShouldClose() == false)
	{
		BeginDrawing();

		// drawing
		ClearBackground(Green);
		food.Draw();

		EndDrawing();
	}

	CloseWindow();
	return 0;
}