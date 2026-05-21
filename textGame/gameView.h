#pragma once
#include <vector>
#include <string>
#include "Skill.h"
#include "character.h"
#include "BattleResult.h"
#include "item.h"

//하드코딩용
void printWString( std::wstring str );
void loadEndingScene();

//UI
void loadCharacterInfo();
void loadGraphic();
void loadStageTitle( int chapter , int stage );
void loadStory(int idx);
void loadTitle( int idx , int curStage , int curChpater );
void clearScene();
void printPleaseInput();
void printItemMoneyList( std::vector<std::tuple<std::wstring , bool , int>> items );
void printStatusData( const Status& stat , std::wstring name );

//아이템
void printItemActive( std::wstring itemName );
void printItemInActive( std::wstring itemName );
void printItemSell( int gold );
void printItemList(std::vector<std::pair<std::wstring, bool>> items);
void printGold(int gold);
void printStore( std::vector<std::pair<ItemInfo , int>> items );

//배틀
void printHeal( int heal );
void loadBattle( BattleResult result );
void drawMonster( int idx );
void printLevelUp(int level);
void printEnemyStatusData(int hp , int damage);

//스킬
void printSkillGet( std::wstring skillName);
void printAllSkillGet( std::vector<std::tuple<int, int, std::wstring>> skills );


