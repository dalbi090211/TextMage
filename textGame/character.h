#pragma once

#include "Status.h"
#include <vector>
#include <string>

class Character{
private :
	void levelUp() {
		stat.level++;
		stat.maxExp = stat.maxExp * (1 + 0.3f);
		stat.maxHp += 5;
		stat.hp += 5;
		stat.power += 3;
	}
protected :
	Status stat;

public : 
	Status getStatus() const {
		return stat;
	}

	int getLevel() {
		return stat.level;
	}

	int getDamage() {
		return stat.power;
	}

	void playerHeal(int hp) {
		stat.hp += hp;
		if ( stat.hp > stat.maxHp ) stat.hp = stat.maxHp;
	}

	void setHp(int curHp) {
		stat.hp = curHp;
	}
	void plusExp(int exp) {
		stat.exp += exp;
	}

	void plusAtkStat( int attack ) {
		stat.power += attack;
	}

	void plusHpStat( int hp ) {
		stat.maxHp += hp;
		stat.hp += hp;
	}

	void minusAtkStat( int attack ) {
		stat.power -= attack;
	}

	void minusHpStat( int hp ) {
		stat.maxHp -= hp;
		stat.hp -= hp;
	}
	
	bool checkLevelUp(){
		if (stat.maxExp <= stat.exp) {
			stat.exp -= stat.maxExp;
			levelUp();
			return true;
		}
		else return false;
	}
};

class NormalClass : public Character {
public:
	NormalClass();
};

class BlackClass : public Character {
public:
	BlackClass();
};

class WildClass : public Character {
public:
	WildClass();
};