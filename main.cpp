#include <iostream>
#include <raylib.h>

using namespace std;

class Ball
{
	public:
	float x, y;
	int speed_x, speed_y;
	int radius;
	
	void Draw()
	{	
		DrawCircle(x, y, radius, WHITE);
	}

	void update()
	{
		x += speed_x;
		y += speed_y;
		
		if(x + radius >= GetScreenWidth() || x - radius <= 0)
		{
			speed_x *= -1;
		}
		if(y + radius >= GetScreenHeight() || y - radius <= 0)
		{
			speed_y *= -1;
		}
	}
};

class Paddle
{
	protected:
	void LimitMovement()
	{
		if(y <= 0) y = 0;
      if(y + height >= GetScreenHeight()) y = GetScreenHeight() - height;
	}

	public:
	float x, y;
	float width, height;
	int speed;

	void Draw()
	{
		DrawRectangle(x, y, width, height, WHITE);
	}

	void update()
	{
		if(IsKeyDown(KEY_UP)) y -= speed;
		if(IsKeyDown(KEY_DOWN)) y += speed;
		LimitMovement();
	}

};

class CpuPaddle: public Paddle
{
	public:
	void update(int ball_y)
	{
		if(y + height/2 > ball_y) y -= speed;
		else y += speed;
		LimitMovement();
	}
};


Ball ball;
Paddle player;
CpuPaddle cpu;

int main()
{
	const int screen_width = 1280;
	const int screen_height = 800;

	InitWindow(screen_width, screen_height, "Pong Game!");
	
	SetTargetFPS(60);
	
	// ball
	ball.x = screen_width/2;
	ball.y = screen_height/2;
	ball.radius = 10;
	ball.speed_x = 7;
	ball.speed_y = 7;

	// player
	player.width = 25;
	player.height = 120;
	player.x = screen_width - 10 - player.width;
	player.y = screen_height/2 - player.height/2;
	player.speed = 6;

	// cpu
	cpu.width = 25;
	cpu.height = 120;
	cpu.x = 10;
	cpu.y = screen_height/2 - cpu.height/2;
	cpu.speed = 6;
	while(!WindowShouldClose()) 
	{
		BeginDrawing();

		// updating 
		ball.update();
		player.update();
		cpu.update(ball.y);
		
		// Drawing
		ClearBackground(BLACK);
		DrawLine(screen_width/2, 0, screen_width/2, screen_height, WHITE);				
		ball.Draw();
		player.Draw();
		cpu.Draw();
		EndDrawing();
	}

	CloseWindow();
	return 0;
}
