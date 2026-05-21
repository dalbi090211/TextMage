#pragma once

#include "IStatusEvent.h"
#include "item.h"
#include <unordered_map>
#include <vector>

//target* 주입받고 실행하는 방식이 이상적
class ExpUpCommand : public IStatusEvent {
private:
	int Exp;

public:
	ExpUpCommand( int Exp ) {
		this->Exp = Exp;
	}

	void execute() {
		plusExp( Exp );
	}
};

class DifficultyUpCommand : public IStatusEvent {
private:
	int dif;

public:
	DifficultyUpCommand( int dif ) {
		this->dif = dif;
	}

	void execute() {
		plusDif( dif );
	}
};

class DifficultyDownCommand : public IStatusEvent {
private:
	int dif;

public:
	DifficultyDownCommand( int dif ) {
		this->dif = dif;
	}

	void execute() {
		minusDif( dif );
	}
};

class StatUpCommand : public IStatusEvent {
private:

public:
	StatUpCommand() {
	}

	void execute() {
		statUpTrigger();
	}
};

class AttackUpCommand : public IStatusEvent {
private :
	int attack;

public:
	AttackUpCommand(int attack) {
		this->attack = attack;
	}

	void execute() {
		plusAtk(attack);
	}
};

class HpUpCommand : public IStatusEvent {
private:
	int hp;

public:
	HpUpCommand(int hp) {
		this->hp = hp;
	}

	void execute() {
		plusHp(hp);
	}
};

class HealCommand : public IStatusEvent {
private:
	int hp;

public:
	HealCommand( int hp ) {
		this->hp = hp;
	}

	void execute() {
		healHp( hp );
	}
};

class Inventory {
private : 
	std::unordered_map<ItemName , std::vector<IStatusEvent*>> commandMap = {
		{
			ItemName::Silver_Sword_of_the_Astral_Plane,
			{
				new AttackUpCommand( 4 ),
				new HpUpCommand( 5 )
			}
		},
		{
			ItemName::Thornwhisper_Staff,
			{
				new AttackUpCommand( 7 ),
				new HpUpCommand( 4 )
			}
		},
		{
			ItemName::Necklace_of_Elemental_Augmentation,
			{
				new DifficultyUpCommand(1),
			}
		},
		{
			ItemName::Soulrender_Axe,
			{
				new AttackUpCommand( 8 ),
				new HpUpCommand( 3 )
			}
		},
		{
			ItemName::Emberveil_Ring,
			{
				new AttackUpCommand( 1 ),
				new HpUpCommand( 3 )
			}
		},
		{
			ItemName::Gravemire_Pendant,
			{
				new AttackUpCommand( 2 ),
				new HpUpCommand( 3 )
			}
		},
		{
			ItemName::Helldusk_Armor,
			{
				new AttackUpCommand( 6 ),
				new HpUpCommand( 9 )
			}
		},
		{
			ItemName::Stormcaller_Amulet,
			{
				new StatUpCommand(),
			}
		},
		{
			ItemName::Duskmantle_Cloak,
			{
				new AttackUpCommand( 4 ),
				new HpUpCommand( 6 )
			}
		},
		{
			ItemName::Heart,
			{
				new HealCommand( 15 ),
			}
		},
		{
			ItemName::Crybabys_Chocker,
			{
				new DifficultyDownCommand( 2 ),
			}
		},
	};

	std::vector<ItemInfo> itemInfoVec = {
		ItemInfo( 30,  ItemType::Consumable, ItemName::Heart, { L"체력을 15 회복합니다." } ),
		ItemInfo( 150, ItemType::Stat, ItemName::Silver_Sword_of_the_Astral_Plane, { L"공격력을 4 올려줍니다.", L"체력을 5 올려줍니다." } ),
		ItemInfo( 250, ItemType::Stat, ItemName::Thornwhisper_Staff, { L"공격력을 7 올려줍니다.", L"체력을 4 올려줍니다." } ),
		ItemInfo( 400, ItemType::Disposable, ItemName::Necklace_of_Elemental_Augmentation, { L"모든 주문의 난이도를", L"1레벨 올립니다." } ),
		ItemInfo( 20, ItemType::Disposable, ItemName::Crybabys_Chocker, { L"모든 주문의 난이도를", L"2레벨 낮춥니다." } ),
		ItemInfo( 60,  ItemType::Stat, ItemName::Emberveil_Ring,     { L"공격력을 1 올려줍니다.", L"체력을 3 올려줍니다." } ),
		ItemInfo( 90,  ItemType::Stat, ItemName::Gravemire_Pendant,  { L"공격력을 2 올려줍니다.", L"체력을 3 올려줍니다." } ),
		ItemInfo( 180, ItemType::Stat, ItemName::Duskmantle_Cloak,   { L"공격력을 4 올려줍니다.", L"체력을 6 올려줍니다." } ),
		ItemInfo( 500, ItemType::Disposable, ItemName::Stormcaller_Amulet, { L"모든 스탯형 아이템이", L"2번 적용됩니다." } ),
		ItemInfo( 320, ItemType::Stat, ItemName::Soulrender_Axe,     { L"공격력을 8 올려줍니다.", L"체력을 3 올려줍니다." } ),
		ItemInfo( 400, ItemType::Stat, ItemName::Helldusk_Armor,     { L"공격력을 6 올려줍니다.", L"체력을 9 올려줍니다." } ),
	};
	
	void executePattern( ItemName item ) {
		for (IStatusEvent* ptr : commandMap[item]) {
			ptr->execute();
		}
	}

public : 
	bool itemTrigger = false;

	void executeItem( int infoIdx ) {
		ItemInfo& info = itemInfoVec[ infoIdx ];

		switch ( info.type ) {
		case ItemType::Stat:
			executePattern( info.name);
			if( itemTrigger ) executePattern( info.name );
			break;
		case ItemType::Consumable:
			executePattern( info.name);
			break;
		case ItemType::Disposable:
			executePattern(info.name);
			break;
		}
	}

	std::vector<std::pair<ItemInfo , int>> spawnStore( int num ) {
		std::vector<int> indices;
		for ( int i = 1; i < (int)itemInfoVec.size(); i++ ) {
			indices.push_back( i );
		}

		for ( int j = (int)indices.size() - 1; j >= 1; j-- ) {
			int target = rand() % (j + 1);
			std::swap( indices[ j ] , indices[ target ] );
		}

		int count = min( num , (int)indices.size() );
		std::vector<std::pair<ItemInfo , int>> result;
		for ( int i = 0; i < count; i++ ) {
			result.push_back( { itemInfoVec[ indices[ i ] ], indices[ i ] } );
		}

		result.push_back( { itemInfoVec[ 0 ], 0 } );
		return result;
	}

	void erase( int idx ) {
		itemInfoVec.erase( itemInfoVec.begin() + idx );
	}

};