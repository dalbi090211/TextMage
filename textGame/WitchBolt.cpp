#include "WitchBolt.h"

#include <string>

using namespace std;

void WitchBolt::init(int dif)
{
	player = {};
	dt = 1.0f / 30;
	enemies.clear();
	skillLimitTime = 6.0f + dif * 0.3f;
	enemySpeed = 12 + 2 * dif;
	spawnTickLimit = 100 - dif * 5;
	spawnTick = spawnTickLimit;	//게임 시작 시 무조건 1번 생성
}

void WitchBolt::spawnEnemy() {
	spawnTick++;
	if ( spawnTick < spawnTickLimit ) return;
	else {
		spawnTick -= spawnTickLimit;
	}

	float sizeBorganY = (float)((miniMaxY - miniStartY) / 5);

	MEnemy e = {};
	e.Position.x = (float)(miniMaxX - EnemySizeX);
	e.Position.y = (float)miniStartY + sizeBorganY + rand() % (int)(sizeBorganY * 3);
	e.Direction = { -1.0f, 0.0f };
	e.Speed = enemySpeed;
	e.HP = 1;
	e.Active = true;
	enemies.push_back( e );
}

void WitchBolt::setPlayerPos( float x , float y )
{
	player.Position.x = x;
	player.Position.y = y;
}

void WitchBolt::playerDraw() {
	// 플레이어
	ScreenPrintUI( (SHORT)player.Position.x , (SHORT)player.Position.y , "%->" );
}

void WitchBolt::enemyDraw() {
	for ( const MEnemy& e : enemies ) {
		if ( !e.Active ) continue;
		for ( int curY = miniStartY; curY <= miniMaxY; curY++ ) {
			if ( curY >= (int)e.Position.y && curY < (int)e.Position.y + EnemySizeY ) continue;
			for ( int j = 0; j < EnemySizeX; j++ ) {
				ScreenPrintUI( (SHORT)(e.Position.x + j) , (SHORT)curY , "E" );
			}
		}
	}
}

void WitchBolt::playerTick() {
	while ( _kbhit() ) {
		char PressKey = _getch();
		switch ( PressKey ) {
		case LEFT_KEY:
			--player.Position.x;
			if ( player.Position.x < miniStartX + 1 )
				player.Position.x = (float)(miniStartX + 1);
			break;
		case RIGHT_KEY:
			++player.Position.x;
			if ( player.Position.x > miniMaxX - 4 )
				player.Position.x = (float)(miniMaxX - 4);
			break;
		case UP_KEY:
			--player.Position.y;
			if ( player.Position.y < miniStartY + 1 )
				player.Position.y = (float)(miniStartY + 1);
			break;
		case DOWN_KEY:
			++player.Position.y;
			if ( player.Position.y > miniMaxY - 1 )
				player.Position.y = (float)(miniMaxY - 1);
			break;
		default:
			break;
		}
	}
}

void WitchBolt::enemyTick() {
	float dt = 1.0f / 30.0f;

	for ( int i = 0; i < enemies.size(); i++ ) {
		MEnemy& e = enemies[ i ];
		if ( !e.Active ) continue;

		float nextX = e.Position.x + e.Direction.x * e.Speed * dt;

		if ( nextX < miniStartX + 1) {
			e.Active = false;
		}
		e.Position.x = nextX;
	}
}

bool WitchBolt::checkCollision() {
	for ( auto& e : enemies ) {
		if ( !e.Active ) continue;
		float dx = player.Position.x - e.Position.x;
		float dy = player.Position.y - e.Position.y;
		if ( abs( dx ) <= EnemySizeX-3 && (dy < 0 || dy > EnemySizeY) ) {  // ✅
			return true;
		}
	}
	return false;
}

bool WitchBolt::checkClear() {
	for ( int i = 0; i < enemies.size(); i++ ) {
		if ( enemies[ i ].Active == true ) return false;
	}
	return true;
}

void WitchBolt::tick() {
	playerTick();
	enemyTick();
}

void WitchBolt::draw() {
	playerDraw();
	enemyDraw();
}

int WitchBolt::execute( int difficulty ) {
	init(difficulty);
	UIDraw();
	int clock = 0;
	setPlayerPos( miniStartX + 2 , (miniStartY + miniMaxY) / 2 );
	while ( clock <= skillLimitTime ) {
		if ( FPSUpdate() ) {
			clock += 1;
		}
		spawnEnemy();
		ScreenClear();
		printFullUI();
		tick();
		draw();
		if ( checkCollision() ) return 0;
		ScreenFlipping();
		Sleep(3);
	}
	return 1;
}