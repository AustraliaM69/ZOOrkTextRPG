
#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"

class Player;

class Enemy: public Character {
public:
    Enemy(const std::string &name, const std::string &desc, int hp, int attack);

    bool isAlive() const;

    void takeDamage(int dmg);

    int getHP() const;

    int getAttackPower() const;

    void attack(Player *player);


private:
    int health;
    int attackPower;
};




#endif //ENEMY_H
