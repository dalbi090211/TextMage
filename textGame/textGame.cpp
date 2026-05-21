#include <windows.h>
#include <locale>
#include <io.h>
#include <fcntl.h>
#include "gameController.h"

int curStatus = 1;

void SetConsoleSize( int cols , int lines )
{
	HANDLE hOut = GetStdHandle( STD_OUTPUT_HANDLE );

	SMALL_RECT minRect = { 0, 0, 1, 1 };
	SetConsoleWindowInfo( hOut , TRUE , &minRect );

	COORD size = { (SHORT)cols, (SHORT)1000 };
	SetConsoleScreenBufferSize( hOut , size );

	SMALL_RECT rect = { 0, 0, (SHORT)(cols - 1), (SHORT)(lines - 1) };
	SetConsoleWindowInfo( hOut , TRUE , &rect );

	system( "mode con cols=200 lines=50" );
	srand( time( NULL ) );
}

int main() {
	SetConsoleSize( 200 , 50 );
	SetConsoleOutputCP( CP_UTF8 );
	SetConsoleCP( CP_UTF8 );                              // ← 입력 코드페이지도 UTF-8

	_setmode( _fileno( stdout ) , _O_U8TEXT );
	_setmode( _fileno( stdin ) , _O_U8TEXT );               // ← stdin도 wide 모드
	_setmode( _fileno( stderr ) , _O_U8TEXT );

	gameController game = gameController();
	game.startGame();
}