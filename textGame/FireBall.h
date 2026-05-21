#pragma once

#include "Skill.h"

class FireBall : public Skill {
private:
	float dt;
	MPlayer player;
	std::vector<MBullet> bullets;
	std::vector<MEnemy> enemies;

	void init();
	void spawnEnemy( int num );
	void setPlayerPos( float x , float y );
	void playerDraw();
	void bulletTick();
	bool checkClear();
	void playerTick();
	void enemyTick();
	void checkCollision();
	void tick();

public:
	FireBall() : Skill( 24 , 15 , 80 , 30 ) {}
	int execute( int difficulty ) override;
};