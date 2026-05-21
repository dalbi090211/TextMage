#include <vector>
#include "Enemy.h"
#include "textModel.h"
#include "gameView.h"
#include "Skill.h"
#include "Mingame.h"
#include "inventory.h"
#include <unordered_map>
#include "Ground.h"

using namespace std;

Character* player = new WildClass();
MinigameManager mm = MinigameManager();
Enemy* enemy;
wstring playerName;
Inventory inven;
Ground* ground = nullptr;
int gold = 0;
int curStoreSize = 5;

std::vector<std::pair<ItemInfo , int>> curStore = {};

void spawnStore() {
	curStore = inven.spawnStore( curStoreSize );
}

vector<pair<ItemInfo , int>> getStore() {
	return curStore;
}

void plusMagicInit(int num) {
	mm.plusDefaultDif( num );
}

void setWildTrigger() {
	mm.setWildTrigger();
}

void buyItem( int idx ) {
	ItemType type = curStore[ idx ].first.type;

	gold -= curStore[ idx ].first.price;
	inven.executeItem( curStore[ idx ].second );

	if ( type == ItemType::Consumable ) {
	}
	else if ( type == ItemType::Disposable ) {
		int infoIdx = curStore[ idx ].second;
		curStore[ idx ].second = -1;
		inven.erase(infoIdx);
		for ( auto& store : curStore ) {
			if ( store.second > infoIdx ) store.second--;
		}
	}
	else if ( type == ItemType::Stat ) {
		curStore[ idx ].second = -1;
	}
}

bool checkBuy( int idx ) {
	if ( curStore[ idx ].second == -1 ) return false;

	if ( gold >= curStore[ idx ].first.price ) {
		buyItem( idx );
		return true;
	}
	return false;
}

int spawnBoss(int idx) {
	switch ( idx ) {
	case 1 : 
		enemy = (*ground).spawnGroundBoss( Forest );
		break;

	case 2:
		enemy = (*ground).spawnGroundBoss( Town );
		break;
	}
	return (*enemy).getStoryNum();
}

int spawnEnemy() {
	enemy = (*ground).spawnGroundEnemy();
	return (*enemy).getStoryNum();
}

void plusAtk( int attack ) {
	player->plusAtkStat( attack );
}

void healHp( int hp ) {
	player->playerHeal( hp );
}

void plusHp( int hp ) {
	player->plusHpStat( hp );
}

void minusAtk( int attack ) {
	player->minusAtkStat( attack );
}

void minusHp( int hp ) {
	player->minusHpStat( hp );
}

void setGold(int gol) {
	gold = gol;
}

void addGold( int gol ) {
	gold += gol;
}

void minusGold( int gol ) {
	gold -= gol;
}

int getGold() {
	return gold;
}

vector<tuple<int, int, wstring>> getSkills() {
	return mm.spawnSkill((*player).getDamage());
}

void setName(wstring name) {
	playerName = name;
}

wstring getName() {
	return playerName;
}

void setClass(int classNum) {
	delete(player);
	switch (classNum) {
		case 0 :
			player = new NormalClass();
			break;
		case 1:
			player = new BlackClass();
			break;
		case 2:
			player = new WildClass();
			break;
		default : 
			player = new WildClass();
			break;
	}
}

Status getPlayerStatus() {
	return player->getStatus();
}

void checkLevelUp() {
	while (player->checkLevelUp()) {	//모델쪽 작업이 뷰랑 직결되서 분리하기 힘듬, 
		printLevelUp(player->getLevel());
	}
}

void plusExp( int exp ) {
	player->plusExp( exp );
	checkLevelUp();
}

void plusDif( int dif ) {
	mm.levelUpDif(dif);
}

void minusDif( int dif ) {
	mm.levelDownDif( dif );
}

void statUpTrigger() {
	inven.itemTrigger = true;
}

Enemy* getEnemyStatus(){
	return enemy;
}

void setGround( GroundType type ) {
	if ( ground == nullptr || ground->getType() != type ) {
		delete ground;
		ground = new Ground( type );
	}
}

BattleResult getBattle(int magicSeq) {	//스킬 공격
	BattleResult result = BattleResult();
	result.playerDamage = mm.playSkill( magicSeq );
	result.monsterDamage = enemy->getDamage();
	player->setHp(player->getStatus().hp - result.monsterDamage);
	result.playerHp = player->getStatus().hp;
	enemy->setHp(enemy->getHp() - result.playerDamage);
	result.monsterHp = enemy->getHp();

	if (result.playerHp <= 0) result.exp = -1;
	else if ( result.monsterHp <= 0 ) {
		result.exp = enemy->getExp();
		player->plusExp(result.exp);
	}
	else result.exp = 0;
	printEnemyStatusData(enemy->getHp(), enemy->getDamage());
	return result;
}