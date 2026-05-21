#include "MiniConfig.h"
#include "DoubleBuffereing.h"

static HANDLE g_hScreen[ 2 ];
static int g_ScreenIndex = 0;

void ScreenPrintUI( SHORT x , SHORT y , const char* _String )
{
	DWORD dw = 0;
	COORD Pos = { x, y };
	SetConsoleCursorPosition( g_hScreen[ g_ScreenIndex ] , Pos );
	WriteFile( g_hScreen[ g_ScreenIndex ] , _String , strlen( _String ) , &dw , NULL );
}

void ScreenFlipping()
{
	SetConsoleActiveScreenBuffer( g_hScreen[ g_ScreenIndex ] );
	g_ScreenIndex = !g_ScreenIndex;
}

void ScreenInit()
{
	g_hScreen[ 0 ] = CreateConsoleScreenBuffer(
		GENERIC_READ | GENERIC_WRITE ,
		0 , NULL ,
		CONSOLE_TEXTMODE_BUFFER , NULL );
	g_hScreen[ 1 ] = CreateConsoleScreenBuffer(
		GENERIC_READ | GENERIC_WRITE ,
		0 , NULL ,
		CONSOLE_TEXTMODE_BUFFER , NULL );

	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 1;
	cci.bVisible = FALSE;

	SetConsoleCursorInfo( g_hScreen[ 0 ] , &cci );
	SetConsoleCursorInfo( g_hScreen[ 1 ] , &cci );
}

void ScreenEnd() {
	HANDLE hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
	SetConsoleActiveScreenBuffer( hStdOut );
}

void ScreenClear()
{
	int BG_SIZE_X = miniMaxX - miniStartX + 1;
	int BG_SIZE_Y = miniMaxY - miniStartY + 1;

	DWORD dw = 0;
	for ( int y = miniStartY; y <= miniMaxY; y++ ) {
		COORD pos = { (SHORT)miniStartX, (SHORT)y };
		FillConsoleOutputCharacter(
			g_hScreen[ g_ScreenIndex ] , ' ' ,
			BG_SIZE_X ,
			pos , &dw );
	}
}