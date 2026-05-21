#pragma once

#include "stageMaker.h"
#include "BattleResult.h"
#include "Ground.h"
#include <unordered_map>

int waitInput();

class gameController {
private:
	int chapterLen = 3;	//챕터 한계값, 안쓰긴함
	int stageLen = 5;	//스테이지 한계값, 애도 안쓰긴함
	int choiceLen = 3;	//스테이지 진입 시 랜덤으로 생성되는 맵의 최대 갯수
	int curStage = 0;	//현재 스테이지 번호
	int curChapter = 0;	//현재 챕터 번호

	//StoryType에 매핑하여 메인 로직이 되는 함수를 실행
	std::unordered_map<StoryType , StageFunc> storyMapper = {
		{ StoryType::Tutorial,   [this] { startTutorial(); } },
		{ StoryType::Battle1,     [this] { goDungeon(1); } },
		{ StoryType::Battle2,     [this] { goDungeon(2); } },
		{ StoryType::Battle3,    [this] { goDungeon(3); } },
		{ StoryType::Boss1,		 [this] { goBoss(1); } },
		{ StoryType::Store,      [this] { goStore(); } },
		{ StoryType::RandomEvent,      [this] { goRandomEvent(); }}
	};

	//RandomType에 매핑하여 메인 로직이 되는 함수를 실행
	std::unordered_map<RandomType , StageFunc> randomStoryMapper = {
		{ RandomType::Gamble, [this] { goGamble(); }},
		{ RandomType::Grannie, [this] { goGrannie(); }},
		{ RandomType::Chemist, [this] { goChemist(); }},
	};

	//stage진입 시 int값에 따른 확률을 가짐(ex : 1-4 스테이지의 확률 = stageRatio[0][3] 내의 모든 int / 자신의 int)
	std::vector<std::vector<std::vector<StageRate>>> stageRatio = { 
		{
			{
				{ 1, StoryType::Tutorial },
			},
			{
				{ 5, StoryType::Battle1 },
				{ 5, StoryType::Battle2  },
			},
			{
				{ 5, StoryType::Battle1 },
				{ 5, StoryType::Battle2 },
				{ 5, StoryType::RandomEvent },
			},
			{
				{ 5, StoryType::Battle1 },
				{ 5, StoryType::Battle2  },
				{ 5, StoryType::Battle3 },
			},
			{
				{ 5, StoryType::Battle1 },
				{ 5, StoryType::Battle2  },
				{ 5, StoryType::Store  },
			},
			{
				{ 5, StoryType::Battle1 },
				{ 5, StoryType::Battle3 },
				{ 5, StoryType::Battle2  },
				{ 5, StoryType::Store  },
				{ 5, StoryType::RandomEvent },
			},
			{
				{ 5, StoryType::Battle1 },
				{ 5, StoryType::Battle3 },
				{ 5, StoryType::Battle2  },
				{ 5, StoryType::Store  },
				{ 5, StoryType::RandomEvent },
			},
			{
				{ 5, StoryType::Battle3 },
				{ 5, StoryType::Battle2  },
				{ 5, StoryType::RandomEvent },
			},
			{
				{ 5, StoryType::Store  },
			},
			{
				{ 10, StoryType::Boss1 },
			},
		} ,
	};

	//랜덤이벤트 발생 시 int값에 따른 확률을 가짐.(한 이벤트의 발생확률 = 전체 int의 합 / 자신의 int)
	std::vector<std::pair<int, RandomType>> randomRatio = {
		{ 1, RandomType::Gamble  },
		{ 1, RandomType::Grannie },
		{ 1, RandomType::Chemist },
	};

    bool endTrigger = false;	//게임 루프 제어용, 엔딩 시 true

	//메인로직
	void gameInit();
	void nextStage();
	void startTutorial();

	//ui용
	void refreshScene();

	//던전용
	void goDungeon(int DungeonNum);
	void moveGround();
	void fightChoice();
	void goCave();
	void goCastle();
	void goForest();
	void goBoss( int bossNum );

	//random 이벤트용
	void goRandomEvent();
	void goGamble();
	void goGrannie();
	void goChemist();

	//그 외
	void goStore();
	void loopStore();

public:
    gameController();
	bool isTuto = true;	//튜토리얼 진입 시 ui안보이도록 설정하기 위한 값.
    void startGame();	//메인 플레이 루프, nextStage()를 통해 stage를 spone하여 게임을 제어함
};