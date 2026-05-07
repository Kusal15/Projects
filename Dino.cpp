#include "raylib.h"
#include <iostream>
#include <string>
#include <cmath>
#include <vector>

struct Dino;
struct Obstacle;
using namespace std;
double gravity = 0;
double speed = 0;

enum Direction
{
	STOP,
	UP,
	
};

struct Dino
{
	bool isGameOver;
	
	Rectangle dino;
	Direction direction;
	vector<int> score;

	Dino()
	{
		dino = { 100,400,70,70 };
		isGameOver = false;
		direction = STOP;
	}

	void DinoJump();
	void Collision(Obstacle obstacle);
	void Ground();

};
struct Obstacle
{
	Rectangle obstacle;
	Obstacle()
	{
		obstacle = { 1200, 420 , 30 , 50};
	}
	void ObstacleMove(Dino &obj);
};

void Obstacle::ObstacleMove(Dino &obj)
{
	
	speed += 0.1;
	obstacle.x -= 8 + (speed * 0.05);
	if (obstacle.x <= 0)
	{
		obstacle.x = GetRandomValue(1050,1300);
		obj.score.push_back(1);
	}
}
void Dino::Collision(Obstacle obstacle)
{
	if (CheckCollisionRecs(dino, obstacle.obstacle) )
	{
		isGameOver = true;
	}
}
void Dino::DinoJump()
{
	if (IsKeyPressed(KEY_SPACE))
	{
		direction = UP;
	}
	if (direction == UP)
	{
		gravity += 0.2;
		dino.y -= 6 - (1* gravity);
	}
}
void Dino::Ground()
{
	if (dino.y == 400)
	{
		
		direction = STOP;
		gravity = 0;
	}

}





int main()
{


	
	InitWindow(1000,800,"DINO");
	SetTargetFPS(60);

	Dino dino;
	Obstacle obstacle;
	while (WindowShouldClose() == false)
	{
		if (dino.isGameOver == false)
		{

			dino.DinoJump();
			dino.Ground();
			obstacle.ObstacleMove(dino);
			dino.Collision(obstacle);
	


		}
		else
		{
			DrawText("Nacisnij 'R' aby rozpoczac ponownie", 120, 300, 40, BLACK);
			if (IsKeyPressed(KEY_R))
			{
				dino.dino.y = 400;
				obstacle.obstacle.x = 1200;
				gravity = 0;
				speed = 0;
				dino.score.clear();
				dino.isGameOver = false;
			}
		}
		BeginDrawing();
		ClearBackground(WHITE);

		DrawLine(0, 471, 1000, 471, BLACK);



		DrawRectangle(dino.dino.x, dino.dino.y, dino.dino.height, dino.dino.width, RED);
		DrawRectangle(obstacle.obstacle.x, obstacle.obstacle.y, obstacle.obstacle.width, obstacle.obstacle.height, GREEN);
		DrawText(TextFormat("Score: %i ", dino.score.size()), 300 , 200 , 20 , BLACK);

		EndDrawing();
		
	}

	return 0;
}
