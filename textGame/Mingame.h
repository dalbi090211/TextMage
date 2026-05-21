#pragma once

#include "Skill.h"
#include "FireBall.h"
#include "MagicMissile.h"
#include "BlackHoll.h"
#include "DoubleBuffereing.h"
#include "WitchBolt.h"
#include "IceLance.h"

#include <vector>
#include <unordered_map>
#include <functional>
#include <string>
#include <stdexcept>

struct SkillConfig {
	float difficultyCoeff;
	float baseDamage;
};

class MinigameManager {
private:
	std::unordered_map<std::wstring , std::function<Skill* ()>> skillRegistry;
	std::unordered_map<std::wstring , SkillConfig> skillConfigs;
	std::vector<std::wstring> skillNames;
	std::vector<std::tuple<int , int , std::wstring>> curSkill;
	const int maxDif = 5;
	bool wildTrigger = false;
	int defaultDif = 1;

public:
	MinigameManager() {
		registerSkill<FireBall>( L"FireBall" , { 0.05f, 12.0f } );
		registerSkill<MagicMissile>( L"MagicMissile" , { 0.2f, 12.0f } );
		registerSkill<BlackHoll>( L"BlackHoll" , { 0.2f, 12.0f } );
		registerSkill<IceLance>( L"IceLance", { 0.2f, 12.0f } );
		registerSkill<WitchBolt>( L"WitchBolt" , { 0.2f, 12.0f } );
	}

	template<typename T>
	void registerSkill( const std::wstring& name , SkillConfig config ) {
		skillRegistry[ name ] = []() -> Skill* { return new T(); };
		skillConfigs[ name ] = config;
		skillNames.push_back( name );
	}

	void levelUpDif( int dif ) {
		defaultDif += dif;
	}

	void levelDownDif( int dif ) {
		defaultDif -= dif;
	}

	std::vector<std::tuple<int , int , std::wstring>> spawnSkill(int power) {
		curSkill.clear();

		std::vector<int> randArr( skillNames.size() );
		for ( int i = 0; i < (int)skillNames.size(); i++ )
			randArr[ i ] = i;

		for ( int i = (int)randArr.size() - 1; i > 0; i-- ) {
			int randNum = rand() % (i + 1);
			std::swap( randArr[ i ] , randArr[ randNum ] );
		}

		for ( int i = 0; i < 3; i++ ) {
			const std::wstring& name = skillNames[ randArr[ i ] ];
			const SkillConfig& cfg = skillConfigs[ name ];

			int difficulty;
			difficulty = wildTrigger ?  4 * (int)(rand() % 2) + 1 : (int)(rand() % maxDif) + defaultDif;
			if ( difficulty > maxDif ) difficulty = maxDif;	//default가 1보다 커지면 발생가능
			if ( difficulty <= 0 ) difficulty = 1;
			int damage = (int)((cfg.difficultyCoeff * (difficulty + rand() % 2 )*power) + cfg.baseDamage);

			curSkill.push_back( { difficulty, damage, name } );
		}
		return curSkill;
	}

	int playSkill( int idx ) {
		const auto& [difficulty , damage , name] = curSkill[ idx ];
		auto it = skillRegistry.find( name );

		Skill* skill = it->second();

		ScreenInit();
		int result = skill->execute( difficulty );
		delete skill;
		ScreenEnd();

		//나중에 남은 시간에 따른 데미지 넣으려고 bool이 아닌 int처리
		return result ? damage: 0;
	}

	void plusDefaultDif( int num ) {
		defaultDif += num;
	}

	void setWildTrigger() {
		wildTrigger = true;
	}
};