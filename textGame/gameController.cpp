#include <iostream>

#include "Enemy.h"
#include "gameView.h"
#include "textModel.h"
#include "gameController.h"
#include "item.h"
#include "GroundType.h"

using namespace std;

int waitGetInt() { 
    int input;
    printPleaseInput();
    wcin >> input;
    return input;
}

wstring waitGetString() {
	wstring input;
	printPleaseInput();
	wcin >> input;
	return input;
}

void gameController::refreshScene() {
	clearScene();
	if (isTuto) return;
	printStatusData(getPlayerStatus(), getName());
	printGold(getGold());
}

gameController::gameController() {
}

void gameController::startTutorial() {
	refreshScene();
	loadCharacterInfo();
	loadTitle(0, curStage, curChapter);
	setGold( 0 );

	int inputNum = waitGetInt() - 1;
	setClass(inputNum);
	isTuto = false;

	//이름 설정
	loadStory( 8 );
	wstring name = waitGetString();
	setName(name);
}

void gameController::goRandomEvent() {
	refreshScene();
	loadTitle(2, curStage, curChapter);

	int sumMax = 0;
	for ( int i = 0; i < randomRatio.size(); i++ ) {
		sumMax += randomRatio[ i ].first;
	}

	int roll = rand() % sumMax;  // ← 랜덤값 추가
	int idx = 0;
	while ( roll > -1 ) {
		roll -= randomRatio[ idx++ ].first;
	}
	idx--;

	RandomType& curType = randomRatio[ idx ].second;
	randomStoryMapper[curType]();
}

void gameController::goGamble() {
	refreshScene();
	loadTitle(1 , curStage , curChapter );
	loadStory(25);

	int targetMoney[] = { 100, 200, 300, 400 };
	int chance[] = {80, 60, 50, 40};
	wstring sb;

	for ( int i = 0; i < 4; i++ ) {
		sb.clear();
		sb += L"1. ";
		sb += to_wstring( targetMoney[ i ] );
		sb += L"골드를 내고 도박에 응한다.(확률 : ";
		sb += to_wstring( chance[ i ] );
		sb += L"%)";
		printWString(sb.c_str());
		printWString( L"2. 무시한다." );
		int inputNum = waitGetInt();
		while ( inputNum != 1 && inputNum != 2 ) {
			inputNum = waitGetInt();
		}
		if ( inputNum == 1 ) {
			int playerRand = rand() % 100 + 1;
			if ( playerRand < chance[ i ] ) {
				addGold( targetMoney[i]);
				refreshScene();
				printWString( L"당신은 성공했습니다." );
				sb.clear();
				sb += to_wstring( targetMoney[ i ]);
				sb += L"골드를 획득하셨습니다.";
				printWString( sb.c_str() );
				printWString( L"도박꾼이 다시 도박을 제시합니다." );
				printWString( L"" );	//\n용
			}
			else {
				minusGold( targetMoney[ i ] );
				refreshScene();
				printWString( L"당신은 패배했습니다." );
				sb.clear();
				sb += to_wstring( targetMoney[ i ]);
				sb += L"골드를 잃었습니다.";
				printWString( sb.c_str() );
				loadStory( 4 );
				inputNum = waitGetInt();
				return;
			}
		}
		else {
			loadStory( 4 );
			inputNum = waitGetInt();
			return;
		}
	}
	loadStory( 28 );
	int inputNum = waitGetInt();
	if ( inputNum == 1 ) {
		int randNum = rand() % 100;
		if ( randNum < 45 ) {
			setGold( getGold() * 2 );
			refreshScene();
			printWString( L"당신은 성공했습니다." );
			printWString( to_wstring( getGold() ) + L"골드를 획득하셨습니다." );
			loadStory( 4 );
			inputNum = waitGetInt();
			return;
		}
		else {
			setGold(0);
			refreshScene();
			printWString( L"당신은 패배했습니다." );
			loadStory( 4 );
			inputNum = waitGetInt();
			return;
		}
	}
	else {
		refreshScene();
		printWString( L"당신은 도망쳤습니다." );
		loadStory( 4 );
		inputNum = waitGetInt();
		return;
	}
}

void gameController::goGrannie() {
	refreshScene();
	loadTitle( 1 , curStage , curChapter );
	loadStory( 26 );
	
	int inputNum = waitGetInt();
	refreshScene();
	switch ( inputNum ) {
	case 1 :
		printWString( L"당신이 다가가자" );
		printWString( L"소녀는 전투태세를 갖춥니다." );
		spawnBoss( 2 );
		fightChoice();
		break;

	case 2:
		minusGold( 100 );
		refreshScene();
		printWString( L"당신은 말없이 동전을 소녀의 손에 쥐어줍니다." );
		printWString( L"소녀는 웃으며 골목 안으로 뛰어갑니다." );
		printWString( L"" );
		printWString( L"150골드를 잃었습니다." );
		loadStory( 4 );
		inputNum = waitGetInt();
		break;

	case 3:
		addGold( 200 );
		refreshScene();
		printWString( L"당신은 소녀의 주머니를 탈탈 털어냅니다." );
		printWString( L"소녀가 울상을 지으며 골목 안으로 도망칩니다." );
		printWString( L"" );
		printWString( L"200골드를 획득했습니다." );
		loadStory( 4 );
		inputNum = waitGetInt();
		break;

	case 4:
		printWString( L"당신이 다가가자" );
		printWString( L"소녀는 전투태세를 갖춥니다." );
		spawnBoss( 2 );
		fightChoice();
		break;
	}
}

void gameController::goChemist() {
	refreshScene();
	loadTitle( 1 , curStage , curChapter );
	loadStory( 29 );

	int inputNum = waitGetInt();
	switch ( inputNum ) {
	case 1:
		if ( rand() % 2 <= 1 ) {
			plusAtk( 10 );
			plusHp( 10 );
			refreshScene();

			printWString( L"약물이 몸에 스며들어 " );
			printWString( L"전투력이 끓어오르는 걸 느낍니다." );
			printWString( L"공격력과 체력이 10씩 올랐습니다." );
			loadStory( 4 );
			inputNum = waitGetInt();
			break;
		}
		else {
			minusAtk( 7 );
			minusHp( 7 );
			addGold( 200 );
			refreshScene();

			printWString( L"약물이 몸에 스며들어 " );
			printWString( L"온몸에 기운이 빠지기 시작합니다." );
			printWString( L"공격력과 체력이 7씩 줄었습니다." );
			printWString( L"노인은 불쌍하다는듯이 200골드를 던져주고 갔습니다." );
			printWString( L"" );
			loadStory( 4 );
			inputNum = waitGetInt();
			break;
		}
		break;

	case 2:
		addGold( 200 );
		refreshScene();
		printWString( L"당신은 불쌍한 노인을 학대했습니다." );
		printWString( L"200골드를 획득했습니다." );
		printWString( L"" );
		loadStory( 4 );
		inputNum = waitGetInt();
		break;

	case 3:
		refreshScene();
		printWString( L"당신은 경찰을 열심히 찾았지만" );
		printWString( L"이곳은 판타지 세계. 그런 건 없습니다." );
		printWString( L"주위를 둘러보자 어느새 노인도 사라졌습니다." );
		printWString( L"" );
		loadStory( 4 );
		inputNum = waitGetInt();
		break;

	case 4:
		refreshScene();
		printWString( L"당신이 도망가자" );
		printWString( L"할아버지의 손녀가" );
		printWString( L"당신을 뒤쫓습니다." );
		spawnBoss( 2 );
		fightChoice();
		break;
	}
}

void gameController::goStore() {
	spawnStore();
	loopStore();
}

void gameController::loopStore() {
	refreshScene();
	loadTitle(3 , curStage , curChapter );
	loadStory(13);
	printStore(getStore());

	int inputNum = waitGetInt()-1;
	if ( inputNum == -1 ) return;
	checkBuy( inputNum );
	loopStore();
}

void gameController::goForest() {
	refreshScene();
	loadTitle(2 , curStage , curChapter );
	setGround( GroundType::Forest );
	moveGround();	//입력 분기에 따라 따로 적용되게 만들어야할부분
}

void gameController::goCave() {
	refreshScene();
	loadTitle( 4 , curStage , curChapter );
	setGround( GroundType::Cave );
	moveGround();	//입력 분기에 따라 따로 적용되게 만들어야할부분
}

void gameController::goCastle() {
	refreshScene();
	loadTitle( 5 , curStage , curChapter );
	setGround( GroundType::Castle );
	moveGround();	//입력 분기에 따라 따로 적용되게 만들어야할부분
}

void gameController::goBoss( int bossNum ) {
	switch ( bossNum ) {
	case 1:
		refreshScene();
		loadTitle( 5 , curStage , curChapter );
		loadStory( spawnBoss(bossNum) );
		fightChoice();
		endTrigger = true;
		break;
	}
}

void gameController::goDungeon(int DungeonNum ) {
	switch ( DungeonNum ) {
	case 1:
		setGround( GroundType::Forest );
		goForest();
		break;
	case 2:
		setGround( GroundType::Cave );
		goCave();
		break;
	case 3:
		setGround( GroundType::Castle );
		goCastle();
		break;
	}
}

void gameController::moveGround() {
	loadStory(spawnEnemy());
	fightChoice();
}

void gameController::fightChoice() {
	bool spawnSkill = false;
	vector<tuple<int, int, wstring>> skills;
	Enemy* enemy = getEnemyStatus();	//모델에서 받아와야함. 직접 가져오는게 아니라
	drawMonster(enemy->getSpriteNum());
	loadStory(5);
	//받아온 enemy 데이터로 이름 표기
	printEnemyStatusData(enemy->getHp() , enemy->getDamage());

	int inputNum = waitGetInt();
	while ( inputNum != 1 && inputNum != 2 ) {
		inputNum = waitGetInt();
	}

	BattleResult result;
	if ( inputNum == 1 ) {	//스킬
		loadStory( 6 );
		if ( !spawnSkill ) {
			spawnSkill = true;
			skills = getSkills();
			printAllSkillGet(skills);
		}
		else printAllSkillGet( skills );
		inputNum = waitGetInt();
		result = getBattle(inputNum-1);
	}
	else if ( inputNum == 2 ) {	//할복
		result.exp = -1;
		result.playerDamage = -1;
		result.monsterDamage = -99999999;
	}

	refreshScene();
	loadBattle(result);
	if ( result.exp < 0 ) {	//플레이어 사망
		loadStory( 3 );
		int inputNum = waitGetInt();
		if ( inputNum == 1 ) {
			startGame();
		}
	}
	else if ( result.exp >= 1 ) {	//몬스터 사망
		checkLevelUp();
		addGold(150);
		loadStory( 4 );
		int inputNum = waitGetInt();
		if ( inputNum == 1 ) {

		}
	}
	else {
		fightChoice();
	}
}

void gameController::gameInit() {
	isTuto = true;
	curChapter = 0;
	curStage = -1;
	endTrigger = false;
}

void gameController::nextStage() {
	curStage++;
	refreshScene();
	loadStory( 9 );
	loadStageTitle( curChapter , curStage );

	if ( curStage >= (int)stageRatio[ curChapter ].size() ) {
		endTrigger = true;
		return;
	}

	vector<StoryType> curChoices;
	auto& curRatio = stageRatio[curChapter][curStage];
	
	/*	현재 */
	if ( stageRatio[ curChapter ][ curStage ].size() <= choiceLen ) {
		for ( int i = 0; i < stageRatio[ curChapter ][ curStage ].size(); i++ ) {
			curChoices.push_back( stageRatio[ curChapter ][ curStage ][i].story);
		}
	}
	else {
		vector<StageRate> pool;
		for ( StageRate sr : curRatio ) {
			bool found = false;
			for ( StageRate& p : pool ) {
				if ( p.story == sr.story ) {
					p.ratio += sr.ratio;
					found = true;
					break;
				}
			}
			if(!found) pool.push_back( sr );
		}

		while ( (int)curChoices.size() < choiceLen ) {
			int maxChoice = 0;
			for ( StageRate sr : pool ) maxChoice += sr.ratio;
			int roll = rand() % maxChoice;
			int acc = 0;
			for ( int i = 0; i < (int)pool.size(); i++ ) {
				acc += pool[ i ].ratio;
				if ( roll < acc ) {
					curChoices.push_back( pool[ i ].story );
					pool.erase( pool.begin() + i );
					break;
				}
			}
		}
	}

	for ( int i = 0; i < curChoices.size(); i++ ) {
		printWString( std::to_wstring( i + 1 ) + L". " + StoryNameToString(curChoices[i]));
	}

	int inputNum = waitGetInt()-1;
	if ( inputNum < 0 || inputNum >= curChoices.size() ) {
		curStage--;
		nextStage();
	}
	else {
		storyMapper[ curChoices[ inputNum ] ]();
	}
}

void gameController::startGame() {
	gameInit();
	refreshScene();
	while ( !endTrigger ) {
		nextStage();
	}
	loadEndingScene();
	int inputNum = waitGetInt();
	if ( inputNum == 1 ) startGame();
}