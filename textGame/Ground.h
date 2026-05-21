#pragma once

#include "GroundType.h"
#include "Enemy.h"
#include <vector>
#include <functional>
#include <unordered_map>

class Ground {
private:
	std::vector<std::pair<int , Enemy*>> curEnemyEncounter;
	std::vector<int> curEnemy;
	int remainEnemy;
	GroundType curType;

	inline static const std::unordered_map<GroundType , std::vector<std::pair<int , std::function<Enemy* ()>>>> encounterTable = {
		{
			Forest, {
				{4, [] { return new Oak(); }},
				{4, [] { return new Elf(); }}
			}
		},
		{
			Cave, {
				{3, [] { return new Bat(); }},
				{4, [] { return new Troll(); }},
				{4, [] { return new Goblin(); }},
			}
		},
		{
			Castle, {
				{4, [] { return new Knight(); }},
				{4, [] { return new Warlock(); }},
				{4, [] { return new Wraith(); }}
			}
		},
	};

	void reset() {
		curEnemyEncounter.clear();
		for ( auto& [count , factory] : encounterTable.at( curType ) ) {
			curEnemyEncounter.push_back( { count, factory() } );
			remainEnemy += count;
		}
	}

public:
	Ground() {
		curEnemyEncounter.clear();
		for ( auto& [count , factory] : encounterTable.at( GroundType::Forest ) )
			curEnemyEncounter.push_back( { count, factory() } );
	}

	Ground( GroundType type ) : curType( type ) {
		curEnemyEncounter.clear();
		for ( auto& [count , factory] : encounterTable.at( type ) ){
			curEnemyEncounter.push_back( { count, factory() } );
			remainEnemy += count;
		}
	}

	Enemy* spawnGroundEnemy() {
		if ( remainEnemy == 0 ) reset();
		int randNum = rand() % remainEnemy + 1;
		for ( int i = 0; i < curEnemyEncounter.size(); i++ ) {
			randNum -= curEnemyEncounter[ i ].first;
			if ( randNum <= 0 ) {
				curEnemyEncounter[ i ].first--;
				remainEnemy--;
				delete curEnemyEncounter[ i ].second;
				curEnemyEncounter[ i ].second = encounterTable.at( curType )[ i ].second();
				return curEnemyEncounter[ i ].second;
			}
		}
	}

	Enemy* spawnGroundBoss(GroundType type) {
		switch (type) {
		case Forest :
			return new Ogre();
		case Town : 
			return new Girl();
		}
	}

	GroundType getType() { return curType; }
};