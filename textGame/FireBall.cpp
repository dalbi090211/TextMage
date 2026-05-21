#include "FireBall.h"

void FireBall::init()
{
	player = {};
	dt = 1.0f / 30;
}

void FireBall::spawnEnemy( int num ) {
	enemies.clear();
	std::vector<int> enemyY( miniMaxY - miniStartY );

	for ( int i = 0; i < miniMaxY - miniStartY - 2; i++ ) {
		enemyY[ i ] = i;
	}

	for ( int i = enemyY.size() - 1; i >= 0; i-- ) {
		int temp = enemyY[ i ];
		int swapNum = rand() % (i + 1);
		enemyY[ i ] = enemyY[ swapNum ];
		enemyY[ swapNum ] = temp;
	}

	for ( int i = 0; i < num; i++ ) {
		MEnemy e = {};
		e.Position.x = (float)(miniMaxX - 3);
		e.Position.y = (float)(miniStartY + 1 + enemyY[ i ]);
		e.Direction = { 0.0f, (rand() % 2 == 0) ? 1.0f : -1.0f };
		e.Speed = 1.5f;
		e.HP = 1;
		e.Active = true;
		enemies.push_back( e );
	}
}

void FireBall::setPlayerPos( float x , float y )
{
	player.Position.x = x;
	player.Position.y = y;
}

void FireBall::playerDraw() {
	// 플레이어
	ScreenPrintUI( (SHORT)player.Position.x , (SHORT)player.Position.y , "%->" );

	// 총알
	for ( const MBullet& b : bullets ) {
		if ( !b.Active ) continue;
		ScreenPrintUI( (SHORT)b.Position.x , (SHORT)b.Position.y , "*" );
	}

	// 적
	for ( const MEnemy& e : enemies ) {
		if ( !e.Active ) continue;
		ScreenPrintUI( (SHORT)e.Position.x , (SHORT)e.Position.y , "M" );
	}
}

void FireBall::playerTick() {
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
		case SPACE_KEY:
		{
			MBullet b = {};
			b.Position = { player.Position.x + 2, player.Position.y };
			b.Direction = { 1.0f, 0.0f };
			b.Speed = 20.0f;
			b.Active = true;
			bullets.push_back( b );
			break;
		}
		default:
			break;
		}
	}
}

void FireBall::enemyTick() {
	float dt = 1.0f / 30.0f;

	for ( int i = 0; i < enemies.size(); i++ ) {
		MEnemy& e = enemies[ i ];
		if ( !e.Active ) continue;

		float nextY = e.Position.y + e.Direction.y * e.Speed * dt;

		if ( nextY < miniStartY + 1 || nextY > miniMaxY - 2 ) {
			e.Direction.y *= -1.0f;
			continue;
		}

		bool blocked = false;
		for ( int j = 0; j < enemies.size(); j++ ) {
			if ( i == j || !enemies[ j ].Active ) continue;
			float dx = enemies[ j ].Position.x - e.Position.x;
			float dy = enemies[ j ].Position.y - nextY;
			if ( abs( dx ) < 1.0f && abs( dy ) < 1.0f ) {
				blocked = true;
				break;
			}
		}

		if ( blocked ) {
			e.Direction.y *= -1.0f;
			continue;
		}

		e.Position.y = nextY;
	}
}

void FireBall::bulletTick() {
	for ( MBullet& b : bullets ) {
		if ( !b.Active ) continue;
		b.Position.x += b.Direction.x * b.Speed * dt;
		if ( b.Position.x > miniMaxX - 1 )
			b.Active = false;
	}
}

void FireBall::checkCollision() {
	for ( MBullet& b : bullets ) {
		if ( !b.Active ) continue;
		for ( auto& e : enemies ) {
			if ( !e.Active ) continue;
			float dx = b.Position.x - e.Position.x;
			float dy = b.Position.y - e.Position.y;
			if ( dx >= 0 && dx < 2 && dy >= -1 && dy <= 1 ) {
				b.Active = false;
				e.HP--;
				if ( e.HP <= 0 )
					e.Active = false;
			}
		}
	}
}

bool FireBall::checkClear() {
	for ( int i = 0; i < enemies.size(); i++ ) {
		if ( enemies[ i ].Active == true ) return false;
	}
	return true;
}

void FireBall::tick() {
	playerTick();
	bulletTick();
	enemyTick();
	checkCollision();
}

int FireBall::execute( int difficulty ) {
	init();
	float skillLimitTime = 4.0f + difficulty * 0.1f;
	UIDraw();
	int clock = 0;
	setPlayerPos( miniStartX + 2 , (miniStartY + miniMaxY) / 2 );
	spawnEnemy( (int)pow( 2 , difficulty * 0.5 ) + 1 );
	while ( clock <= skillLimitTime ) {
		clock = FPSUpdate() ? clock + 1 : clock;
		ScreenClear();
		printFullUI();
		tick();
		playerDraw();
		ScreenFlipping();
		if ( checkClear() ) return 1;
		Sleep( 3 );
	}
	return 0;
}