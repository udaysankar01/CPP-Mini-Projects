#include <iostream>
#include <raylib.h>
#include <deque>
#include <raymath.h>

using namespace std;

Color Green = { 173, 204, 96, 255 };
Color DarkGreen = { 43, 51, 24, 255 };

int cellSize = 30;
int cellCount = 25;

double lastUpdateTime = 0;

bool eventTriggered(double interval)
{
	double currentTime = GetTime();
	if (currentTime - lastUpdateTime > interval)
	{
		lastUpdateTime = currentTime;
		return true;
	}
	return false;
}

bool elementInDeque(Vector2 element, deque<Vector2> deque)
{
	for (unsigned int i = 0; i < deque.size(); i++)
	{
		if (Vector2Equals(deque[i], element))
		{
			return true;
		}
	}
	return false;
}

class Snake
{
public:
	deque<Vector2> body = { Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9} };
	Vector2 direction = { 1, 0 };
	bool addSegment = false;

	void Draw()
	{
		for (unsigned int i = 0; i < body.size(); i++)
		{
			float x = body[i].x;
			float y = body[i].y;
			Rectangle segment = Rectangle{ x * cellSize, y * cellSize, (float)cellSize, (float)cellSize };
			DrawRectangleRounded(segment, 0.5, 6, DarkGreen);
		}
	}

	void Update()
	{	
		body.push_front(Vector2Add(body[0], direction));
		if (addSegment)
		{
			addSegment = false;
		}
		else
		{
			body.pop_back();
		}
	}

	void Reset()
	{
		body = { Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9} };
		direction = { 1, 0 };
	}
};

class Food
{

public:
	Vector2 position;
	Texture2D texture;

	Food(deque<Vector2> snakeBody)
	{
		Image image = LoadImage("food.png");
		texture = LoadTextureFromImage(image);
		UnloadImage(image);
		position = GenerateRandomPos(snakeBody);
	}

	~Food()
	{
		UnloadTexture(texture);
	}

	void Draw()
	{
		//DrawRectangle(position.x * cellSize, position.y * cellSize, cellSize, cellSize, DarkGreen);
		DrawTexture(texture, position.x * cellSize, position.y * cellSize, WHITE);
	}

	Vector2 GenerateRandomCell()
	{
		float x = GetRandomValue(0, cellCount - 1);
		float y = GetRandomValue(0, cellCount - 1);
		Vector2 position = { x, y };
		return position;
	}

	Vector2 GenerateRandomPos(deque<Vector2> snakeBody )
	{
		Vector2 position = GenerateRandomCell();
		while (elementInDeque(position, snakeBody))
		{
			position = GenerateRandomCell();
		}
		return position;
	}
};

class Game
{
public:
	Snake snake = Snake();
	Food food = Food(snake.body);

	void Draw()
	{
		food.Draw();
		snake.Draw();
	}

	void Update()
	{
		snake.Update();
		CheckCollisionWithFood();
		CheckCollisionWithEdges();
	}

	void CheckCollisionWithFood()
	{
		if (Vector2Equals(snake.body[0], food.position))
		{	
			food.position = food.GenerateRandomPos(snake.body);
			snake.addSegment = true;

		}
	}

	void CheckCollisionWithEdges()
	{
		if (snake.body[0].x == cellCount || snake.body[0].x == -1)
		{
			GameOver();
		}
		if (snake.body[0].y == cellCount || snake.body[0].y == -1)
		{
			GameOver();
		}
	}

	void GameOver()
	{
		snake.Reset();
		food.position = food.GenerateRandomPos(snake.body);
	}
};

int main()
{

	cout << "Starting the game..." << endl;
	InitWindow(cellSize * cellCount, cellSize * cellCount, "Snake Game");
	SetTargetFPS(60);

	Game game = Game();

	// game loop
	while (WindowShouldClose() == false)
	{
		BeginDrawing();

		// update
		if (eventTriggered(0.2))
		{
			game.Update();
		}

		if (IsKeyPressed(KEY_UP) && game.snake.direction.y != 1)
		{
			game.snake.direction = { 0, -1 };
		}
		if (IsKeyPressed(KEY_DOWN) && game.snake.direction.y != -1)
		{
			game.snake.direction = { 0, 1 };
		}
		if (IsKeyPressed(KEY_RIGHT) && game.snake.direction.x != -1)
		{
			game.snake.direction = { 1, 0 };
		}
		if (IsKeyPressed(KEY_LEFT) && game.snake.direction.x != 1)
		{
			game.snake.direction = { -1, 0 };
		}

		// drawing
		ClearBackground(Green);
		game.Draw();

		EndDrawing();
	}

	CloseWindow();
	return 0;
}