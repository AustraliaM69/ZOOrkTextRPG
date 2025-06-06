
#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"

class Player;

class Enemy: public Character {
public:
    Enemy(const std::string &name, const std::string &desc, int hp, int attack,int goldReward);

    bool isAlive() const;

    void takeDamage(int dmg);

    int getHP() const;

    int getAttackPower() const;

    void attack(Player *player);

    int getReward() const;

private:
    int health;
    int attackPower;
    int goldReward;
};




#endif //ENEMY_H
