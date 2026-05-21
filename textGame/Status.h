#pragma once
#include "characterClass.h"

struct Status {
	CharacterClass type;
	int level;
	int power;
	int hp;
	int maxHp;
	int exp;
	int maxExp;
};