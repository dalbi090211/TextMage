#pragma once

#include <string>
#include "character.h"
#include "BattleResult.h"
#include "GroundType.h"
#include "item.h"
#include "Enemy.h"
#include "Skill.h"

Status getPlayerStatus();
std::vector<std::tuple<int, int, std::wstring>> getSkills();
std::vector<std::pair<ItemInfo , int>> getStore();
bool checkBuy(int idx);
void setName(std::wstring name);
void setWildTrigger();
int spawnEnemy();
int spawnBoss( int idx );
void setClass(int classNum);
void setGround(GroundType type);
void checkLevelUp();
int getGold();
void plusAtk( int attack );
void spawnStore();
void healHp( int hp );
void plusHp(int hp);
void minusAtk( int attack );
void minusHp( int hp );
void setGold( int gol );
void addGold( int gol );
void minusGold( int gol );
void plusExp( int exp );
void plusDif( int dif );
void statUpTrigger();
void plusMagicInit( int num );
void minusDif( int dif );
std::wstring getName();
Enemy* getEnemyStatus();
BattleResult getBattle(int magicSeq);