// MagicMissile.cpp
#include "MagicMissile.h"

void MagicMissile::init( int dif ) {
	stopped = false;
	direction = 1;
	moveTimer = 0.0f;
	playerPosX = barStartX;

	// 난이도에 따라 정답 구간 축소
	int corSize = correctSize;
	for ( int i = 0; i < dif; i++ )
		corSize = (int)(corSize * difCoeff);
	corSize = max( corSize , 2 );  // 최소 크기 보장

	int corStartX = barStartX + rand() % (barSize - corSize);
	correctArr = { corStartX, corStartX + corSize };

	// 난이도에 따라 커서 속도 증가
	moveSpeed = max( 0.005f , 0.01f - dif * 0.001f );
}

void MagicMissile::move() {
	if ( stopped ) return;

	moveTimer += 1.0f / GetFPS();
	if ( moveTimer < moveSpeed ) return;
	moveTimer = 0.0f;

	playerPosX += direction;

	if ( playerPosX >= barStartX + barSize - 1 ) {
		playerPosX = barStartX + barSize - 1;
		direction = -1;
	}
	else if ( playerPosX <= barStartX ) {
		playerPosX = barStartX;
		direction = 1;
	}
}

void MagicMissile::drawBar() {
	int barY = miniStartY + miniMaxY/5;
	char buf[ 256 ];

	// 전체 바 출력
	for ( int x = barStartX; x < barStartX + barSize; x++ ) {
		if ( x >= correctArr.first && x < correctArr.second )
			ScreenPrintUI( (SHORT)x , (SHORT)barY , "=" );
		else
			ScreenPrintUI( (SHORT)x , (SHORT)barY , "-" );
	}

	// 커서
	ScreenPrintUI( (SHORT)playerPosX , (SHORT)barY , "|" );

	// 안내 텍스트
	ScreenPrintUI( (SHORT)barStartX , (SHORT)(miniStartY + 2) , "PRESS SPACE!" );
}

void MagicMissile::checkClear() {
	stopped = true;
}

void MagicMissile::playerTick() {
	if ( stopped ) return;
	if ( _kbhit() ) {
		char PressKey = _getch();
		if ( PressKey == SPACE_KEY )
			checkClear();
	}
}

int MagicMissile::execute( int difficulty ) {
	float skillLimitTime = 10 + difficulty * 0.7f;
	UIDraw();         // FPS 측정 및 UI 등장 애니메이션
	init( difficulty );
	int clock = 0;

	while ( clock <= (int)skillLimitTime ) {
		clock = FPSUpdate() ? clock + 1 : clock;  // 1초마다 clock++
		ScreenClear();
		printFullUI();

		playerTick();
		move();       // GetFPS() 기반으로 속도 결정
		drawBar();
		ScreenFlipping();
		if ( stopped ) {
			bool success = (playerPosX >= correctArr.first && playerPosX < correctArr.second);
			ScreenClear();
			printFullUI();
			drawBar();
			ScreenPrintUI( (SHORT)barStartX , (SHORT)((miniStartY + miniMaxY) / 2 + 2) ,
				success ? "SUCCESS!" : "FAILED!" );
			ScreenFlipping();
			Sleep( 800 );
			return success ? 1 : 0;
		}

		Sleep( 10 );
	}

	ScreenClear();
	printFullUI();
	drawBar();
	ScreenPrintUI( (SHORT)barStartX , (SHORT)((miniStartY + miniMaxY) / 2 + 2) , "TIME OVER!" );
	ScreenFlipping();
	Sleep( 800 );
	return 0;
}
