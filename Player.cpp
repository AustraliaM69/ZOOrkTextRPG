//
// Created by Richard Skarbez on 5/7/23.
//

#include "Player.h"
#include "Weapon.h"

#include <algorithm>

Player *Player::playerInstance = nullptr;
std::shared_ptr<Weapon> equippedWeapon;

void Player::setCurrentRoom(Room* room) {
    currentRoom = room;
}

Room* Player::getCurrentRoom() const {
    return currentRoom;
}

void Player::addItem(std::shared_ptr<Item> item) {
    inventory.push_back(std::shared_ptr<Item>(item));
}

bool Player::removeItem(const std::string& name) {
    auto it = std::find_if(inventory.begin(), inventory.end(),
                          [&name](const std::shared_ptr<Item>& item) {
                              std::string itemName = item->getName();
                              std::string searchName = name;
                              std::transform(itemName.begin(), itemName.end(), itemName.begin(), ::tolower);
                              std::transform(searchName.begin(), searchName.end(), searchName.begin(), ::tolower);
                              return itemName == searchName;
                          });
    if (it != inventory.end()) {
        inventory.erase(it);
        return true;
    }
    return false;
}

std::shared_ptr<Item> Player::getItemExact(const std::string& name) {
    for (auto& item : inventory) {
        if (item->getName() == name) {
            return item;
        }
    }
    return nullptr;
}

void Player::listInventory() const {
    std::cout << "You have " << gold << " gold" << std::endl;

    if (inventory.empty()) {
        std::cout << "You are carrying nothing.\n";
    } else {
        std::cout << "You are carrying:\n";
        for (const std::shared_ptr<Item>& item : inventory) {
            std::cout << "- " << item->getName() << ": " << item->getDescription() << "\n";
        }
    }
}
void Player::equip(const std::shared_ptr<Weapon>& weapon) {
    equippedWeapon = weapon;
    std::cout << "You equipped the " << weapon->getName() << ".\n";
}

void Player::unequip() {
    if (equippedWeapon) {
        std::cout << "You unequipped the " << equippedWeapon->getName() << ".\n";
        equippedWeapon = nullptr;
    } else {
        std::cout << "You don't have a weapon equipped.\n";
    }
}

std::shared_ptr<Weapon> Player::getEquippedWeapon() const {
    return equippedWeapon;
}

int Player::getDamage() const {
    return equippedWeapon ? equippedWeapon->getDamage() : 1; // Default fist damage
}

void Player::takeDamage(int dmg) {
    health -= dmg;
    std::cout << "You take " << dmg << " damage. (Health: " << health << ")\n";
    if (health <= 0) {
        std::cout << "You have died!\n";
    }
}

int Player::getHealth() const {
    return health;
}

void Player::heal(int amount) {
    health = std::min(health + amount, 100);  // Cap at 100 health
}

bool Player::hasItem(const std::string& name) const {
    for (const auto& item : inventory) {
        std::string itemName = item->getName();
        std::string searchName = name;
        std::transform(itemName.begin(), itemName.end(), itemName.begin(), ::tolower);
        std::transform(searchName.begin(), searchName.end(), searchName.begin(), ::tolower);
        if (itemName == searchName) {
            return true;
        }
    }
    return false;
}

std::shared_ptr<Item> Player::getItem(const std::string& name) {
    for (auto& item : inventory) {
        std::string itemName = item->getName();
        std::string searchName = name;
        std::transform(itemName.begin(), itemName.end(), itemName.begin(), ::tolower);
        std::transform(searchName.begin(), searchName.end(), searchName.begin(), ::tolower);
        if (itemName == searchName) {
            return item;
        }
    }
    return nullptr;
}
