// BlackHoll.cpp
#include "BlackHoll.h"

void BlackHoll::init( int dif ) {
	currentTime = 0.0f;
	timeVisible = true;
	targetCount = 3 - dif / 2;
	skillLimitTime = 8.0f + dif * 2.0f;

	targetTime = 0;
	pressedTimes.clear();

	float rangeStart = 7.0f;
	float rangeEnd = skillLimitTime - 2.0f;
	targetTime = rangeStart + rand() % (int)(rangeEnd - rangeStart);
}

void BlackHoll::draw() {
	//현재시간
	std::string timeStr = timeVisible
		? "TIME : " + std::to_string( (int)currentTime ) + "." + std::to_string( (int)(currentTime * 10) % 10 ) + "s   "
		: "TIME : ??????  ";
	ScreenPrintUI( (SHORT)BlackStartX , (SHORT)counterY , timeStr.c_str() );

	//타겟
	ScreenPrintUI( (SHORT)BlackStartX , (SHORT)(targetY) , "TARGET :" );
	ScreenPrintUI( (SHORT)(BlackStartX + 9) , (SHORT)targetY , (std::to_string( targetTime ) + "s  ").c_str() );

	//눌린타이밍
	ScreenPrintUI( (SHORT)BlackStartX , (SHORT)(pressedY - 2) , "PRESSED:" );
	for ( int i = 0; i < targetCount; i++ ) {
		ScreenPrintUI( (SHORT)BlackStartX + intervalX * i , (SHORT)(pressedY - 1) , "-----------" );
	}
	for ( int i = 0; i < (int)pressedTimes.size(); i++ ) {
		std::string s = "[" + std::to_string( i + 1 ) + "] "
			+ std::to_string( (int)pressedTimes[ i ] ) + "."
			+ std::to_string( (int)(pressedTimes[ i ] * 10) % 10 ) + "s  ";
		ScreenPrintUI( (SHORT)(BlackStartX + intervalX * i) , (SHORT)pressedY , s.c_str() );
	}
}

void BlackHoll::playerTick() {
	while ( _kbhit() ) {
		char key = _getch();
		if ( key == SPACE_KEY ) {
			pressedTimes.push_back( currentTime );
		}
	}
}

bool BlackHoll::checkClear() {
	for ( int i = 0; i < pressedTimes.size(); i++ ) {
		if ( abs( pressedTimes[ i ] - targetTime ) <= tolerance )
			return true;
	}
	return false;
}

void BlackHoll::showFail() {
	for ( int i = 0; i < 2; i++ ) {
		ScreenClear();
		printFullUI();
		draw();
		ScreenPrintUI( (SHORT)BlackStartX , (SHORT)(resultY + 2) , "== FAILED!  ==" );
		ScreenFlipping();
	}
}

void BlackHoll::showSuccess() {
	for ( int i = 0; i < 2; i++ ) {
		ScreenClear();
		printFullUI();
		draw();
		ScreenPrintUI( (SHORT)BlackStartX , (SHORT)(resultY + 2) , "== SUCCESSED!  ==" );
		ScreenFlipping();
	}
}

void BlackHoll::showResult() {
	bool success = checkClear();
	if ( success ) showSuccess();
	else showFail();
	Sleep( 1500 );
}

int BlackHoll::execute( int difficulty ) {
	UIDraw();
	init( difficulty );

	while ( currentTime <= skillLimitTime ) {
		FPSUpdate();
		currentTime += 1.0f / GetFPS();

		// 3초 이후 시간 숨김
		if ( currentTime > 3.0f )
			timeVisible = false;

		ScreenClear();
		printFullUI();
		playerTick();
		draw();
		ScreenFlipping();

		if ( (int)pressedTimes.size() == targetCount || checkClear() ) {
			showResult();
			return checkClear() ? 1 : 0;
		}
		Sleep( 3 );
	}

	// 시간 초과
	timeVisible = true;
	showFail();
	Sleep( 1500 );
	return 0;
}