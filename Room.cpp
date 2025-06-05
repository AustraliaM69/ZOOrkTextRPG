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
    for (const std::shared_ptr<Item>& itemPtr : items) {
        if (itemPtr->getName() == name) return itemPtr;
    }
    return nullptr;
}

bool Room::removeItem(const std::string &name) {
    auto it = std::find_if(items.begin(), items.end(),
                           [&](const std::shared_ptr<Item>& i) { return i->getName() == name; });
    if (it != items.end()) {
        items.erase(it);
        return true;
    }
    return false;
}
void Room::addEnemy(std::shared_ptr<Enemy> enemy) {
    enemies.push_back(enemy);
}

std::shared_ptr<Enemy> Room::getEnemy(const std::string& name) {
    for (auto& enemy : enemies) {
        if (enemy->getName() == name) {
            return enemy;
        }
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