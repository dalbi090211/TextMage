#include <string>
#include "Fps.h"
#include "DoubleBuffereing.h"
#include "MiniConfig.h"

using namespace std;

static int m_Fps = 60;
static int m_FpsCount = 0;
static int m_FrameCount = 0;
static ULONGLONG m_StartTick = GetTickCount64();

int GetFPS() { return m_Fps; }

void UIDraw() {
	int centerX = (miniStartX + miniMaxX) / 2;
	int centerY = (miniStartY + miniMaxY) / 2;
	int halfW = (miniMaxX - miniStartX) / 2;
	int halfH = (miniMaxY - miniStartY) / 2;

	m_StartTick = GetTickCount64();
	m_FrameCount = 0;

	float drawRatio = 0.0f;
	while ( drawRatio <= 0.95f ) {
		Sleep( 10 );
		m_FrameCount++;
		drawRatio = (GetTickCount64() - m_StartTick) / 1000.0f;

		int w = (int)(halfW * drawRatio);
		int h = (int)(halfH * drawRatio);
		if ( w < 1 ) w = 1;
		if ( h < 1 ) h = 1;

		for ( int x = centerX - w; x <= centerX + w; x++ ) {
			ScreenPrintUI( x , centerY - h , "-" );
			ScreenPrintUI( x , centerY + h , "-" );
		}
		for ( int y = centerY - h + 1; y < centerY + h; y++ ) {
			ScreenPrintUI( centerX - w , y , "|" );
			ScreenPrintUI( centerX + w , y , "|" );
		}

		ScreenFlipping();
		ScreenClear();
	}

	for ( int x = centerX - halfW; x <= centerX + halfW; x++ ) {
		ScreenPrintUI( x , centerY - halfH , "-" );
		ScreenPrintUI( x , centerY + halfH , "-" );
	}
	for ( int y = centerY - halfH + 1; y < centerY + halfH; y++ ) {
		ScreenPrintUI( centerX - halfW , y , "|" );
		ScreenPrintUI( centerX + halfW , y , "|" );
	}

	ScreenClear();
	ScreenFlipping();
	m_Fps = m_FrameCount;
}

bool FPSUpdate() {
	++m_FrameCount;
	if ( GetTickCount64() - m_StartTick >= 1000 ) {
		m_StartTick = GetTickCount64();
		m_Fps = m_FrameCount;
		m_FrameCount = 0;
		return true;
	}
	return false;
}