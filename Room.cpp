//
// Created by Richard Skarbez on 5/7/23.
//

#include "NullPassage.h"
#include "Room.h"

#include <algorithm>
#include <utility>


Room::Room(const std::string &n, const std::string &d) : Location(n, d) {
    enterCommand = std::make_shared<RoomDefaultEnterCommand>(this);
}

Room::Room(const std::string &n, const std::string &d, std::shared_ptr<Command> c) : Location(n, d, std::move(c)) {}

void Room::addPassage(const std::string &direction, std::shared_ptr<Passage> p) {
    passageMap[direction] = std::move(p);
}

void Room::removePassage(const std::string &direction) {
    if (passageMap.contains(direction)) {
        passageMap.erase(direction);
    }
}

std::shared_ptr<Passage> Room::getPassage(const std::string &direction,bool warnIfMissing) {
    if (passageMap.contains(direction)) {
        return passageMap[direction];
    } else {
        if (warnIfMissing) {
            std::cout << "It is impossible to go " << direction << "!\n";
        }
        return std::make_shared<NullPassage>(this);
    }
}
void Room::addItem(std::shared_ptr<Item> item) {
    items.push_back(std::move(item));
}

std::shared_ptr<Item> Room::retrieveItem(const std::string& name) {
    auto it = std::find_if(items.begin(), items.end(),
                          [&name](const std::shared_ptr<Item>& item) {
                              std::string itemName = item->getName();
                              std::string searchName = name;
                              std::transform(itemName.begin(), itemName.end(), itemName.begin(), ::tolower);
                              std::transform(searchName.begin(), searchName.end(), searchName.begin(), ::tolower);
                              return itemName == searchName;
                          });
    if (it != items.end()) {
        std::shared_ptr<Item> item = *it;
        items.erase(it);
        return item;
    }
    return nullptr;
}

void Room::removeItem(const std::string& name) {
    auto it = std::find_if(items.begin(), items.end(),
                          [&name](const std::shared_ptr<Item>& item) {
                              std::string itemName = item->getName();
                              std::string searchName = name;
                              std::transform(itemName.begin(), itemName.end(), itemName.begin(), ::tolower);
                              std::transform(searchName.begin(), searchName.end(), searchName.begin(), ::tolower);
                              return itemName == searchName;
                          });
    if (it != items.end()) {
        items.erase(it);
    }
}
void Room::addEnemy(std::shared_ptr<Enemy> enemy) {
    enemies.push_back(enemy);
}

std::shared_ptr<Enemy> Room::getEnemy(const std::string& name) {
    auto it = std::find_if(enemies.begin(), enemies.end(),
                          [&name](const std::shared_ptr<Enemy>& enemy) {
                              std::string enemyName = enemy->getName();
                              std::string searchName = name;
                              std::transform(enemyName.begin(), enemyName.end(), enemyName.begin(), ::tolower);
                              std::transform(searchName.begin(), searchName.end(), searchName.begin(), ::tolower);
                              return enemyName == searchName;
                          });
    if (it != enemies.end()) {
        return *it;
    }
    return nullptr;
}

void Room::removeEnemy(const std::string& name) {
    enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
        [&](const std::shared_ptr<Enemy>& enemy) {
            return enemy->getName() == name;
        }),
        enemies.end());
}

std::vector<std::shared_ptr<Enemy>>& Room::getEnemies() {
    return enemies;
}

void Room::addNPC(std::shared_ptr<NPC> npc) {
    npcs.push_back(npc);
}

std::vector<std::shared_ptr<NPC>> Room::getNPCs() const {
    return npcs;
}