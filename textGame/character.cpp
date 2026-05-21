#include "character.h"
#include "textModel.h"

NormalClass::NormalClass() {
	stat.type = CharacterClass::NormalMage;
    stat.level = 0;
    stat.power = 10;
    stat.maxHp = 70;
    stat.exp = 0;
	stat.maxExp = 10;
	stat.hp = stat.maxHp;
}

BlackClass::BlackClass() {
	stat.type = CharacterClass::BlackMage;
    stat.level = 1;
    stat.power = 7;
    stat.maxHp = 55;
    stat.exp = 0;
	stat.maxExp = 10;
	stat.hp = stat.maxHp;
	plusMagicInit(3);
}

WildClass::WildClass() {
	stat.type = CharacterClass::WildMage;
	stat.level = 1;
	stat.power = 9;
	stat.maxHp = 60;
	stat.exp = 0;
	stat.maxExp = 7;
	stat.hp = stat.maxHp;
	setWildTrigger();
}