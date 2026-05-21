#pragma once

#include "Skill.h"

class WitchBolt : public Skill {
private:
	float dt;
	MPlayer player;
	float skillLimitTime;
	float enemySpeed;
	int spawnTick;
	int spawnTickLimit;
	std::vector<MEnemy> enemies;

	int EnemySizeX = 10;
	int EnemySizeY = 5;

	void init(int dif);
	void spawnEnemy();
	void setPlayerPos( float x , float y );
	void playerDraw();
	void enemyDraw();
	bool checkClear();
	void playerTick();
	void enemyTick();
	bool checkCollision();
	void tick();
	void draw();

public:
	WitchBolt() : Skill( 12 , 5 , 100 , 35 ) {}
	int execute( int difficulty ) override;
};