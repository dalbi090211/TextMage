#pragma once

class Enemy {
	private:
		int damage;
		int hp;
		int exp;
		int storyNum;
		int spriteNum;

	public:
		Enemy(int damage, int hp, int exp, int storyNum, int spriteNum)
			: damage(damage) , hp(hp) , exp(exp), storyNum(storyNum), spriteNum(spriteNum){
		}

		int getDamage() const {
			return damage;
		}

		int getHp() const {
			return hp;
		}

		void setHp(int curHp){
			hp = curHp;
		}

		int getExp() const {
			return exp;
		}

		int getStoryNum() const {
			return storyNum;
		}

		int getSpriteNum() const {
			return spriteNum;
		}
};

class Oak : public Enemy {
	public:
		Oak() : Enemy(7, 30, 5, 2, 0) {
		}
};

class Elf : public Enemy {
public:
	Elf() : Enemy(7 , 30 , 5, 17, 1) {
	}
};

class Bat : public Enemy {
public:
	Bat() : Enemy( 7 , 35 , 6 , 19 , 2) {
	}
};

class Troll : public Enemy {
public:
	Troll() : Enemy( 7 , 20 , 6 , 20, 3) {
	}
};

class Goblin : public Enemy {
public:
	Goblin() : Enemy( 9 , 17 , 6 , 21, 4) {
	}
};

class Knight : public Enemy {
public:
	Knight() : Enemy( 7 , 28 , 7 , 22, 5 ) {
	}
};

class Warlock : public Enemy {
public:
	Warlock() : Enemy( 14 , 35 , 7 , 23 , 6 ) {
	}
};

class Wraith : public Enemy {
public:
	Wraith() : Enemy( 12 , 35 , 7 , 24 , 7) {
	}
};

class Ogre : public Enemy {
public:
	Ogre() : Enemy( 15 , 120 , 10, 10 , 8 ) {
	}
};

class Girl : public Enemy {
public:
	Girl() : Enemy( 12, 50, 20, 27, 9) {
	}
};