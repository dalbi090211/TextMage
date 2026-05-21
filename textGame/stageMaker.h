#pragma once

#include <functional>
#include <string>

using StageFunc = std::function<void()>;

enum StoryType {
	Tutorial ,
	Battle1 ,
	Battle2 ,
	Battle3 ,
	RandomEvent ,
	Store,
	Boss1,
};

enum RandomType {
	Gamble,
	Grannie,
	Chemist
};

struct StageRate {
	int ratio;
	StoryType story;
};

inline const std::wstring StoryNameToString( StoryType type )
{
	switch ( type )
	{
	case Tutorial:
		return L"튜토리얼";

	case Battle1:
		return L"숲 (쉬운 난이도의 전투)";

	case Battle2:
		return L"동굴 (중간 난이도의 전투)";

	case Battle3:
		return L"성 (어려운 난이도의 전투)";

	case Boss1:
		return L"오우거";

	case Store:
		return L"상점";

	case RandomEvent:
		return L"랜덤 이벤트";
	}
}