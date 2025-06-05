//
// Created by Richard Skarbez on 5/7/23.
//

#ifndef ZOORK_ROOM_H
#define ZOORK_ROOM_H

#include "Character.h"
#include "RoomDefaultEnterCommand.h"
#include "Item.h"
#include "Location.h"
#include <map>
#include "Enemy.h"
#include "NPC.h"

class Passage;

class Room : public Location {
    std::vector<std::shared_ptr<Item>> items;

public:
    Room(const std::string &, const std::string &);

    Room(const std::string &, const std::string &, std::shared_ptr<Command>);

    void addItem(std::shared_ptr<Item> item);
    bool removeItem(const std::string&);
    std::shared_ptr<Item> retrieveItem(const std::string&);

    //NPC
    void addNPC(std::shared_ptr<NPC> npc);
    std::vector<std::shared_ptr<NPC>> getNPCs() const;

    void addPassage(const std::string &, std::shared_ptr<Passage>);

    void removePassage(const std::string &);

    std::shared_ptr<Passage> getPassage(const std::string &, bool warnIfMissing = true);

    std::vector<std::shared_ptr<Item>> getItems() const {
        return items;
    }
    void addEnemy(std::shared_ptr<Enemy> enemy);
    std::shared_ptr<Enemy> getEnemy(const std::string& name);
    void removeEnemy(const std::string& name);
    std::vector<std::shared_ptr<Enemy>>& getEnemies();


protected:
//    std::vector<Item*> items;
//    std::vector<Character*> characters;
    std::map<std::string, std::shared_ptr<Passage>> passageMap;
    std::vector<std::shared_ptr<Enemy>> enemies;
    std::vector<std::shared_ptr<NPC>> npcs;
};


#endif //ZOORK_ROOM_H
