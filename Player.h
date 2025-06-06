//
// Created by Richard Skarbez on 5/7/23.
//

#ifndef ZOORK_PLAYER_H
#define ZOORK_PLAYER_H

#include "Character.h"
#include "Location.h"
#include "NullRoom.h"

class Weapon;

class Player : public Character {
public:
    static Player *instance() {
        // Note: lazy instantiation of the singleton Player object
        if (!playerInstance) {
            playerInstance = new Player();
        }
        return Player::playerInstance;
    }

    void setCurrentRoom(Room*);

    Room* getCurrentRoom() const;

    Player(const Player &) = delete;

    Player &operator=(const Player &) = delete;

    //Combat Functions
    void takeDamage(int damage);
    int getHealth() const;

    //Inventory functions
    void addItem(std::shared_ptr<Item> item);
    bool removeItem(const std::string& name);
    std::shared_ptr<Item> getItem(const std::string& name);
    void listInventory() const;
    std::vector<std::shared_ptr<Item>>& getInventory() {
        return inventory;
    }

    //Gold
    int getGold()const {return gold;}
    void setGold(int amount){gold = amount;}
    void addGold(int amount){gold += amount;}
    bool spendGold(int amount) {
        if (gold >= amount) {
            gold -= amount;
            return true;
        }else{return false;}
    }

    void equip(const std::shared_ptr<Weapon>& weapon);
    void unequip();
    std::shared_ptr<Weapon> getEquippedWeapon() const;
    int getDamage() const;


private:
    int health = 100;
    int gold = 0;
    std::shared_ptr<Weapon> equippedWeapon = nullptr;
    std::vector<std::shared_ptr<Item>> inventory;
    static Player *playerInstance;
    Room* currentRoom;
    Player() : Character("You", "You are a person, alike in dignity to any other, but uniquely you."),
               currentRoom(new NullRoom()) {}
};

#endif //ZOORK_PLAYER_H
