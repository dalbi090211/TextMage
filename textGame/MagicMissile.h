// MagicMissile.h
#pragma once
#include "Skill.h"

class MagicMissile : public Skill {
private:
	int playerPosX;
	int barStartX = 25;
	int barSize = 70;
	int correctSize = 30;
	float difCoeff = 0.6f;
	std::pair<int , int> correctArr;

	bool stopped = false;
	int  direction = 1;
	float moveTimer = 0.0f;
	float moveSpeed = 0.08f;

	void drawBar();
	void checkClear();
	void playerTick();
	void init( int dif );
	void move();

public:
	MagicMissile() : Skill(  20 , 10 , 100 , 20 ) {}
	int execute( int difficulty ) override;
};