#include <iostream>
#include <raylib.h>

using namespace std;

Color Green = Color{ 38, 185, 154, 255 };
Color Dark_Green = Color{ 20, 160, 133, 255 };
Color Light_Green = Color{ 129, 204, 184, 255 };
Color Yellow = Color{ 243, 213, 91, 255 };

int player_score = 0;
int cpu_score = 0;

class Ball
{
public:
    float x, y;
    int speed_x, speed_y;
    int radius;

    void Draw()
    {
        DrawCircle(x, y, radius, Yellow);
    }

    void Update()
    {
        x += speed_x;
        y += speed_y;

        // top and bottom collision
        if (y + radius >= GetScreenHeight() || y - radius <= 0)
        {
            speed_y *= -1;
        }
        // left and right collision
        if (x + radius >= GetScreenWidth())    // CPU Wins
        {
            cpu_score++;
            ResetBall();
        }
        if (x - radius <= 0)    // Player Wins
        {
            player_score++;
            ResetBall();
        }
    }

    void ResetBall()
    {
        x = GetScreenWidth() / 2;
        y = GetScreenHeight() / 2;

        int speed_choices[2] = { -1, 1 };
        speed_x *= speed_choices[GetRandomValue(0, 1)];
        speed_y *= speed_choices[GetRandomValue(0, 1)];
    }
};

class Paddle
{
protected:
    void LimitMovement()
    {
        if (y <= 0)
        {
            y = 0;
        }
        if (y + height >= GetScreenHeight())
        {
            y = GetScreenHeight() - height;
        }
    }

public:
    float x, y;
    float width, height;
    int speed;

    void Draw()
    {
        // DrawRectangle(x, y, width, height, WHITE);
        DrawRectangleRounded(Rectangle{ x, y, width, height }, 0.8, 0, WHITE);
    }

    void Update()
    {
        // paddle movement
        if (IsKeyDown(KEY_UP))
        {
            y -= speed;
        }
        if (IsKeyDown(KEY_DOWN))
        {
            y += speed;
        }

        // paddle top down collision
        LimitMovement();
    }
};

class CpuPaddle : public Paddle
{
public:
    void Update(int ball_y)
    {
        if (y + height / 2 > ball_y)
        {
            y = y - speed;
        }
        if (y + height / 2 <= ball_y)
        {
            y = y + speed;
        }

        // top down collision
        LimitMovement();
    }
};

Ball ball;
Paddle player;
CpuPaddle cpu;


int main()
{
    cout << "Starting the Game!!!!" << endl;
    const int screen_width = 1280;
    const int screen_height = 800;
    InitWindow(screen_width, screen_height, "Ping Pong");
    SetTargetFPS(60);

    // initializing the ball
    ball.radius = 20;
    ball.x = GetScreenWidth() / 2;
    ball.y = GetScreenHeight() / 2;
    ball.speed_x = 7;
    ball.speed_y = 7;

    // initializing the player
    player.width = 25;
    player.height = 120;
    player.x = GetScreenWidth() - player.width - 10;
    player.y = GetScreenHeight() / 2 - player.height / 2;
    player.speed = 6;

    // initializing the cpu
    cpu.width = 25;
    cpu.height = 120;
    cpu.x = 10;
    cpu.y = GetScreenHeight() / 2 - cpu.height / 2;
    cpu.speed = 6;

    // game loop
    while (WindowShouldClose() == false)
    {
        BeginDrawing();

        // updating
        ball.Update();
        player.Update();
        cpu.Update(ball.y);

        // check for collisions
        if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ player.x, player.y, player.width, player.height }))
        {
            ball.speed_x *= -1;
        }
        if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ cpu.x, cpu.y, cpu.width, cpu.height }))
        {
            ball.speed_x *= -1;
        }

        // drawing
        ClearBackground(Dark_Green);
        DrawRectangle(screen_width / 2, 0, screen_width / 2, screen_height, Green);
        DrawCircle(screen_width / 2, screen_height / 2, 150, Light_Green);
        DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);
        ball.Draw();
        cpu.Draw();
        player.Draw();
        DrawText(TextFormat("%i", cpu_score), screen_width / 4 - 20, 20, 80, WHITE);
        DrawText(TextFormat("%i", player_score), (3 * screen_width / 4) - 20, 20, 80, WHITE);
        EndDrawing();

    }

    CloseWindow();
    return 0;

}
