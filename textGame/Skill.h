#pragma once

#include "MiniGameStruct.h"
#include "KeyType.h"
#include "MiniView.h"
#include "MiniConfig.h"
#include "Fps.h"
#include "DoubleBuffereing.h"

#include <vector>
#include <string>
#include <conio.h>

class Skill {
protected:
	Skill( int startX , int startY , int endX , int endY )
		: startX( startX ) , startY( startY ) , endX( endX ) , endY( endY )
	{
		miniStartX = startX;
		miniStartY = startY;
		miniMaxX = endX;
		miniMaxY = endY;
	}

public:
	const int startX;
	const int startY;
	const int endX;
	const int endY;
	virtual int execute( int difficulty ) = 0;
};