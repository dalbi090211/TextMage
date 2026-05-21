#pragma once

struct Vector2
{
	float x;
	float y;
};

typedef struct Transform
{
	Vector2 Position;
	Vector2 Direction;
	int HP;
	float Speed;
	bool Active;
	int Type;
} Player , Bullet , Enemy;