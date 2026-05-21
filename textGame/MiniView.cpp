#include "DoubleBuffereing.h"
#include "MiniConfig.h"

void printFullUI() {
	int centerX = (miniStartX + miniMaxX) / 2;
	int centerY = (miniStartY + miniMaxY) / 2;
	int halfW = (miniMaxX - miniStartX) / 2;
	int halfH = (miniMaxY - miniStartY) / 2;

	for ( int x = centerX - halfW; x <= centerX + halfW; x++ ) {
		ScreenPrintUI( x , centerY - halfH , "-" );
		ScreenPrintUI( x , centerY + halfH , "-" );
	}
	for ( int y = centerY - halfH + 1; y < centerY + halfH; y++ ) {
		ScreenPrintUI( centerX - halfW , y , "|" );
		ScreenPrintUI( centerX + halfW , y , "|" );
	}
}

