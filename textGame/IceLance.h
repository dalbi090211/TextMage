#pragma once

#include "Skill.h"
#include "MiniGameStruct.h"

class IceLance : public Skill {
private : 
	Vector2 playerPos;
	std::vector<MEnemy> enemies;
	float spawnTickCount;
	float curTickCount;

	void setPlayerPos( Vector2 pos );
	void playerDraw();
	void playerTick();
	void lineDraw();
	bool checkCollision();
	void enemyTick();
	void spawnEnemy();
	void enemyDraw();

public:
	IceLance() : Skill( 30 , 10 , 80 , 40 ) {}
	int execute( int difficulty ) override;
};