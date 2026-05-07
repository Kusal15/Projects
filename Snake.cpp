#include <iostream>
#include <vector>
#include <string>
#include "raylib.h"
#include <cstdlib>
using namespace std;

struct Apple;
enum Direction
{
	STOP,
	UP,
	DOWN,
	RIGHT,
	LEFT,
};


struct Snake
{

	Rectangle snake;
	vector<Rectangle> body;
	Direction direction;
	bool isgamestopped = false;

	Snake()
	{
		snake = { 495, 405 , 15 ,15 };
		direction = STOP;

	}

	void MoveSnake();
	void ChangeDirection();
	void EatApple(Apple& fruit);
	void DrawTail();
	void Collision();


};
struct Apple
{
	Rectangle fruit;
	Apple()
	{
		fruit = { 0,0,15,15 };
		SpawnApple();

	}
	void DrawApple()
	{

		DrawRectangle(fruit.x, fruit.y, fruit.height, fruit.width, BLUE);
	}
	void SpawnApple()
	{
		float randomX = GetRandomValue(0, 65);
		float randomY = GetRandomValue(0, 53);

		fruit.x = randomX * 15;
		fruit.y = randomY * 15;
	}

};
void Snake::DrawTail()
{
	for (int i = 0; i < body.size(); i++)
	{
		DrawRectangle(body[i].x, body[i].y, 15, 15, RED);
	}

}

void Snake::EatApple(Apple& fruit)
{


	if (snake.x == fruit.fruit.x && snake.y == fruit.fruit.y)
	{
		body.push_back(snake);

		fruit.SpawnApple();



	}

}
void Snake::Collision()
{
	for (int i = 0; i < body.size(); i++)
	{
		if ((snake.x == body[i].x && snake.y == body[i].y))
		{
			isgamestopped = true;
			direction = STOP;

		}
	}
	if ((snake.x == 0 || snake.x >= 1000 || snake.y >= 810 || snake.y == 0))
	{
		direction = STOP;
		isgamestopped = true;

	}

}

void Snake::MoveSnake()
{
	
	
	if (body.size() > 0)
	{

		for (int i = body.size() - 1; i > 0;i--)
		{
			body[i] = body[i - 1];
		}
		body[0] = snake;

	}
	if (direction == UP)
	{
		snake.y -= 15;
	}
	if (direction == DOWN)
	{
		snake.y += 15;
	}
	if (direction == LEFT)
	{
		snake.x -= 15;
	}
	if (direction == RIGHT)
	{
		snake.x += 15;
	}
	

}
void Snake::ChangeDirection()
{
	if (IsKeyPressed(KEY_W) && direction != DOWN)
	{
		direction = UP;
	}
	if (IsKeyPressed(KEY_S) && direction != UP)
	{
		direction = DOWN;
	}
	if (IsKeyPressed(KEY_A) && direction != RIGHT)
	{
		direction = LEFT;
	}
	if (IsKeyPressed(KEY_D) && direction != LEFT)
	{
		direction = RIGHT;
	}
}

int main()
{
	InitWindow(1000, 810, "Snake");
	SetTargetFPS(15);


	
		Snake snake1;
		Apple fruit;
		
		while (WindowShouldClose() == false)
		{

			if (snake1.isgamestopped == false)
			{
				snake1.MoveSnake();
				snake1.Collision();
				snake1.ChangeDirection();
				fruit.DrawApple();
				snake1.EatApple(fruit);
				
			}
			else
			{
				
				if (IsKeyPressed(KEY_R))
				{
					snake1.snake = {495, 405 , 15 ,15 };
					snake1.direction = STOP;
					snake1.body.clear();
					snake1.isgamestopped = false;
				}
			}
				BeginDrawing();
				ClearBackground(DARKGREEN);
				for (int i = 0; i < 1000; i += 15)
				{
					DrawLine(15 + i, 0, 15 + i, 810, BLACK);
				}
				for (int i = 0; i < 810; i += 15)
				{
					DrawLine(0, 15 + i, 1000, 15 + i, BLACK);
				}
				DrawRectangle(snake1.snake.x, snake1.snake.y, snake1.snake.height, snake1.snake.width, RED);
				snake1.DrawTail();
				if(snake1.isgamestopped == true)
					DrawText("Przegrana, nacisnij 'R' zeby rozpoczac ponownie", 50, 300, 40, BLACK);


				EndDrawing();
			
			
		}




		return 0;

	
}
