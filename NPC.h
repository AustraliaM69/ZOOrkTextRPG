//
// Created by Samuel on 5/06/2025.
//

#ifndef NPC_H
#define NPC_H
#include <iostream>
#include <memory>
#include <string>

#include "DialogueNode.h"
#include "Item.h"

class Player;
class Room;  // Add forward declaration

class NPC{
private:
    std::string name;
    std::string description;
    std::shared_ptr<DialogueNode> dialogueRoot;
    std::vector<std::shared_ptr<Item>> inventory;
    std::string questItemName;
    std::shared_ptr<Room> winRoom;
    bool gameEnd = false;

public:
    NPC(const std::string& name, const std::string& description,const std::shared_ptr<DialogueNode>& root);

    std::string getName() const;
    std::string getDescription() const;

    void addItemToInventory(const std::shared_ptr<Item>& item);
    const std::vector<Item>& getInventory() const;

    void startDialogue(Player* player);
    void showShop(Player* player);

    void handleItemGive(const std::string &itemName);

    void setQuestItem(const std::string& itemName) { questItemName = itemName; }
    void setWinRoom(std::shared_ptr<Room> room) { winRoom = room; }
    bool hasQuestItem(const std::string& itemName) const { return itemName == questItemName; }
    std::shared_ptr<Room> getWinRoom() const { return winRoom; }
    bool shouldEndGame() const { return gameEnd; }
};


#endif //NPC_H
