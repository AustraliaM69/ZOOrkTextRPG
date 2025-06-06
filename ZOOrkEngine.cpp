//
// Created by Richard Skarbez on 5/7/23.
//

#include "ZOOrkEngine.h"

#include <algorithm>
#include <utility>

#include "Weapon.h"


ZOOrkEngine::ZOOrkEngine(std::shared_ptr<Room> start) {
    player = Player::instance();
    player->setCurrentRoom(start.get());
    player->getCurrentRoom()->enter();
}

void ZOOrkEngine::run() {
    while (!gameOver) {
        std::cout << "> ";

        std::string input;
        std::getline(std::cin, input);

        std::vector<std::string> words = tokenizeString(input);
        std::string command = words[0];
        std::vector<std::string> arguments(words.begin() + 1, words.end());

        if (command == "go") {
            handleGoCommand(arguments);
        } else if ((command == "look") || (command == "inspect")) {
            handleLookCommand(arguments);
        } else if ((command == "take") || (command == "get")) {
            handleTakeCommand(arguments);
        } else if (command == "drop") {
            handleDropCommand(arguments);
        }else if (command == "inventory") {
            player->listInventory();
        }else if (command == "scan") {
            handleScanCommand();
        }else if (command == "help") {
            std::cout << "-----HELP-----\n Below are the following commands.\n\nGo\nLook\nTake\nDrop\nInventory\nScan\nAttack\nEquip\nUnequip\nTalk\nQuit\n\n Please note: Use commands without filler words. For example - Look North, Take Sword, Go West\n Use the LOOK tool to see which direction to go.\n Use the SCAN command to see all available items.\n\n";
        }else if (command == "attack") {
            handleAttackCommand(arguments);
        }else if (command == "equip") {
            handleEquipCommand(arguments);
        }else if (command == "unequip") {
            player->unequip();
            std::cout << "You unequip your weapon.\n";
        }else if (command == "talk") {
            handleTalkCommand(arguments);
        }else if (command == "quit") {
            handleQuitCommand(arguments);
        } else {
            std::cout << "I don't understand that command.\n";
        }
    }
}

void ZOOrkEngine::handleGoCommand(std::vector<std::string> arguments) {
    std::string direction;
    if (arguments[0] == "n" || arguments[0] == "north") {
        direction = "north";
    } else if (arguments[0] == "s" || arguments[0] == "south") {
        direction = "south";
    } else if (arguments[0] == "e" || arguments[0] == "east") {
        direction = "east";
    } else if (arguments[0] == "w" || arguments[0] == "west") {
        direction = "west";
    } else if (arguments[0] == "u" || arguments[0] == "up") {
        direction = "up";
    } else if (arguments[0] == "d" || arguments[0] == "down") {
        direction = "down";
    } else {
        direction = arguments[0];
    }

    Room* currentRoom = player->getCurrentRoom();
    auto passage = currentRoom->getPassage(direction);
    player->setCurrentRoom(passage->getTo());
    passage->enter();

    currentRoom = player->getCurrentRoom();
    auto enemies = currentRoom->getEnemies();
    if (!enemies.empty()) {
        std::cout << "You notice the following enemies:\n";
        for (const auto& enemy : enemies) {
            std::cout << "- " << enemy->getDescription() << "\n";
        }
    }
    auto npcs = currentRoom->getNPCs();
    if (!npcs.empty()) {
        std::cout << "\nYou see the following people:\n";
        for (const auto& npc : npcs) {
            std::cout << "- " << npc->getDescription() << "\n";
        }
    }
}

void ZOOrkEngine::handleLookCommand(std::vector<std::string> arguments) {
    Room* currentRoom = player->getCurrentRoom();

    if (arguments.empty()) {
        std::cout << currentRoom->getDescription() << "\n";
        return;
    }

    std::string direction = arguments[0];
    std::shared_ptr<Passage> passage = currentRoom->getPassage(direction, false);

    // Check: no passage OR loops back to current room
    if (!passage || passage->getTo() == currentRoom) {
        std::cout << "You don't see anything notable that way.\n";
        return;
    }

    // Valid passage to a different room
    std::cout << "You look " << direction << " and see:\n";
    std::cout << passage->getTo()->getShortDescription() << "\n";
}


void ZOOrkEngine::handleTakeCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "Take what?\n";
        return;
    }

    std::string itemName = arguments[0];
    Room* currentRoom = player->getCurrentRoom();
    std::shared_ptr<Item> item = currentRoom->retrieveItem(itemName);

    if (item) {
        player->addItem(item);
        currentRoom->removeItem(itemName);
        std::cout << "You take the " << itemName << ".\n";
    } else {
        std::cout << "There is no " << itemName << " here.\n";
    }
}

void ZOOrkEngine::handleDropCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "Drop what?\n";
        return;
    }

    std::string itemName = arguments[0];
    std::shared_ptr<Item> item = player->getItem(itemName);

    if (item) {
        player->removeItem(itemName);
        player->getCurrentRoom()->addItem(item);
        std::cout << "You drop the " << itemName << ".\n";
    } else {
        std::cout << "You don’t have a " << itemName << ".\n";
    }
}

void ZOOrkEngine::handleQuitCommand(std::vector<std::string> arguments) {
    std::string input;
    std::cout << "Are you sure you want to QUIT?\n> ";
    std::cin >> input;
    std::string quitStr = makeLowercase(input);

    if (quitStr == "y" || quitStr == "yes") {
        gameOver = true;
    }
}
void ZOOrkEngine::handleScanCommand() {
    Room* currentRoom = player->getCurrentRoom();
    const std::vector<std::shared_ptr<Item>>& items = currentRoom->getItems();

    if (items.empty()) {
        std::cout << "You don't see anything noteworthy lying around.\n";
        return;
    }

    std::cout << "You scan the area and see:\n";
    for (const auto& itemPtr: items) {
        std::cout << "- " << itemPtr->getName() << ": " << itemPtr->getDescription() << "\n";
    }
}
void ZOOrkEngine::handleAttackCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "Attack what?\n";
        return;
    }

    std::string target = arguments[0];
    Room* currentRoom = player->getCurrentRoom();
    std::shared_ptr<Enemy> enemy = currentRoom->getEnemy(target);

    if (!enemy) {
        std::cout << "There is no " << target << " here.\n";
        return;
    }

    //Player damage from equipped weapon
    std::shared_ptr<Weapon> weapon = player->getEquippedWeapon();
    int playerDamage = weapon ? weapon->getDamage() : 1; //Unequipped is 1 Damage
    std::cout << "You strike the " << target << " for " << playerDamage << " damage!\n";
    enemy->takeDamage(playerDamage);

    if (enemy->getHP() <= 0) {
        int enemyReward = enemy->getReward();
        std::cout << "You have defeated the " << target << "!\n You have earned " << enemyReward<< " gold!\n";
        currentRoom->removeEnemy(target);
        player->addGold(enemyReward);
        return;
    }

    //Enemy attack
    int enemyDamage = enemy->getAttackPower();
    std::cout << "The " << target << " fights back for " << enemyDamage << " damage!\n";
    player->takeDamage(enemyDamage);

    if (player->getHealth() <= 0) {
        std::cout << "You have been slain by the " << target << "...\n";
        gameOver = true;
    }
}

std::vector<std::string> ZOOrkEngine::tokenizeString(const std::string &input) {
    std::vector<std::string> tokens;
    std::stringstream ss(input);
    std::string token;

    while (std::getline(ss, token, ' ')) {
        tokens.push_back(makeLowercase(token));
    }

    return tokens;
}

std::string ZOOrkEngine::makeLowercase(std::string input) {
    std::string output = std::move(input);
    std::transform(output.begin(), output.end(), output.begin(), ::tolower);

    return output;
}
void ZOOrkEngine::handleEquipCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "Equip what?\n";
        return;
    }

    std::string weaponName = arguments[0];
    auto playerInventory = player->getInventory();

    // Find weapon in inventory by name
    std::shared_ptr<Weapon> weaponToEquip = nullptr;
    for (auto &item : playerInventory) {
        if (item->getName() == weaponName) {
            weaponToEquip = std::dynamic_pointer_cast<Weapon>(item);
            if (!weaponToEquip) {
                std::cout << "You can't equip that!\n";
                return;
            }
            break;
        }
    }

    if (!weaponToEquip) {
        std::cout << "You don't have that weapon.\n";
        return;
    }

    player->equip(weaponToEquip);
}
void ZOOrkEngine::handleTalkCommand(const std::vector<std::string>& arguments) {
    if (arguments.empty()) {
        std::cout << "Talk to who?\n";
        return;
    }

    std::string npcName = arguments[0];
    Room* currentRoom = player->getCurrentRoom();
    auto npcs = currentRoom->getNPCs();

    for (const auto& npc : npcs) {
        if (npc->getName() == npcName) {
            npc->startDialogue();
            return;
        }
    }

    std::cout << "There's no one named " << npcName << " here.\n";
}
