
#ifndef WEAPON_H
#define WEAPON_H


#include "Item.h"

class Weapon : public Item {
public:
    Weapon(const std::string& name, const std::string& description, int damage)
        : Item(name, description), damage(damage) {}

    int getDamage() const { return damage; }

private:
    int damage;
};




#endif //WEAPON_H
