#include "IceLance.h"
#include <string>

using namespace std;

void IceLance::setPlayerPos( Vector2 pos ) {
	playerPos = pos;
}

bool IceLance::checkCollision() {
	for ( auto& e : enemies ) {
		if ( !e.Active ) continue;
		float dx = abs(playerPos.x - e.Position.x);
		float dy = abs(playerPos.y - e.Position.y);
		if ( dx < 0.5f && dy < 0.5f ) {
			return true;
		}
		
	}
	return false;
}

void IceLance::spawnEnemy() {
	int num = 1;
	curTickCount++;
	if ( spawnTickCount < curTickCount ) {
		curTickCount -= spawnTickCount;
	}
	else {
		return;
	}
	
	int rangeX = miniMaxX - miniStartX - 2;
	std::vector<int> enemyX( rangeX );
	for ( int i = 0; i < rangeX; i++ ) {
		enemyX[ i ] = i;
	}

	for ( int i = enemyX.size() - 1; i >= 0; i-- ) {
		int temp = enemyX[ i ];
		int swapNum = rand() % (i + 1);
		enemyX[ i ] = enemyX[ swapNum ];
		enemyX[ swapNum ] = temp;
	}

	for ( int i = 0; i < num; i++ ) {
		MEnemy e = {};
		e.Position.x = (float)(miniMaxX - enemyX[i] - 1);
		e.Position.y = (float)(miniStartY);
		e.Direction = { 0.0f, 1.0f };
		e.Speed = 5.0f + rand() % 5;
		e.HP = 1;
		e.Active = true;
		enemies.push_back( e );
	}
}

void IceLance::enemyDraw() {
	for ( int i = 0; i < enemies.size(); i++ ) {
		if ( !enemies[ i ].Active ) continue;
		ScreenPrintUI( (SHORT)enemies[i].Position.x , (SHORT)enemies[ i ].Position.y , "@");
	}
}

void IceLance::playerDraw() {
	// 플레이어
	ScreenPrintUI( (SHORT)playerPos.x , (SHORT)playerPos.y , "M" );
}

void IceLance::lineDraw() {
	// 플레이어
	string sb;
	for ( int i = 1; i < miniMaxX - miniStartX; i++ ) {
		sb += "-";
	}
	ScreenPrintUI( (SHORT)startX + 1 , (SHORT)playerPos.y+1, sb.c_str());
}

void IceLance::enemyTick() {
	float dt = 1.0f / 30.0f;

	for ( int i = 0; i < enemies.size(); i++ ) {
		MEnemy& e = enemies[ i ];
		if ( !e.Active ) continue;

		float nextY = e.Position.y + e.Direction.y * e.Speed * dt;

		if ( nextY > miniMaxY - 2 ) {
			e.Active = false;
		}

		e.Position.y = nextY;
	}
}

void IceLance::playerTick() {
	while ( _kbhit() ) {
		char PressKey = _getch();
		switch ( PressKey ) {
		case LEFT_KEY:
			--playerPos.x;
			if ( playerPos.x < miniStartX + 1 )
				playerPos.x = (float)(miniStartX + 1);
			break;
		case RIGHT_KEY:
			++playerPos.x;
			if ( playerPos.x > miniMaxX - 2 )
				playerPos.x = (float)(miniMaxX - 1);
			break;
		default:
			break;
		}
	}
}

int IceLance::execute( int difficulty ) {
	float skillLimitTime = 5 + difficulty * 0.3f;
	spawnTickCount = 5 * pow( 0.8 , difficulty );
	UIDraw();
	enemies.clear();
	int clock = 0;
	setPlayerPos( { (float)(miniStartX + miniMaxX)/2 , (float)( miniMaxY - 3) } );
	while ( clock <= skillLimitTime ) {
		spawnEnemy();
		clock = FPSUpdate() ? clock + 1 : clock;
		ScreenClear();
		printFullUI();
		lineDraw();
		playerTick();
		enemyTick();
		playerDraw();
		enemyDraw();
		if ( checkCollision() ) return 0;
		ScreenFlipping();
		//if ( checkClear() ) return 1;
		Sleep( 3 );
	}
	return 1;
}