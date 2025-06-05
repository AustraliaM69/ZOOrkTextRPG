#include "Enemy.h"
#include "Player.h"
#include <iostream>

Enemy::Enemy(const std::string &name, const std::string &desc, int hp, int attack)
        : Character(name, desc), health(hp), attackPower(attack) {}

bool Enemy::isAlive() const {
    return health > 0;
}

void Enemy::takeDamage(int dmg) {
    health -= dmg;
    std::cout << name << " takes " << dmg << " damage. ";
    if (isAlive()) {
        std::cout << "It has " << health << " HP left.\n";
    } else {
        std::cout << name << " has been defeated!\n";
    }
}

int Enemy::getHP() const {
    return health;
}

int Enemy::getAttackPower() const {
    return attackPower;
}

void Enemy::attack(Player *player) {
    std::cout << name << " attacks you for " << attackPower << " damage!\n";
    player->takeDamage(attackPower);
}