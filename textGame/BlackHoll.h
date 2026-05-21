// BlackHoll.h
#pragma once
#include "Skill.h"

class BlackHoll : public Skill {
private:
	float skillLimitTime;
	float currentTime = 0.0f;
	bool  timeVisible = true;
	int   targetCount = 0;

	float tolerance = 0.5f;
	int counterY = 9;
	int targetY = 15;
	int pressedY = 21;
	int resultY = 24;
	int BlackStartX = 20;
	int intervalX = 14;

	int targetTime;
	std::vector<float> pressedTimes;  // 플레이어가 누른 시간

	void showFail();
	void showSuccess();
	void   init( int dif );
	void   draw();
	void   playerTick();
	void   showResult();
	bool   checkClear();

public:
	BlackHoll() : Skill( 15 , 5 , 100 , 30 ) {}
	int execute( int difficulty ) override;
};