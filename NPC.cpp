//
// Created by Samuel on 5/06/2025.
//

#include "NPC.h"
#include "Player.h"

#include <sstream>

NPC::NPC(const std::string& name, const std::string& description, const std::shared_ptr<DialogueNode>& root)
    :name(name), description(description), dialogueRoot(root){
}

std::string NPC::getName() const {
    return name;
}

std::string NPC::getDescription() const {
    return description;
}
void NPC::addItemToInventory(const std::shared_ptr<Item>& item) {
    inventory.push_back(item);
}

void NPC::startDialogue(Player* player) {
    if (!dialogueRoot) {
        std::cout << "This character has nothing to say.\n";
        return;
    }

    std::shared_ptr<DialogueNode> current = dialogueRoot;
    while (current && !current->isTerminal()) {
        std::cout << "\n" << name << " says: \"" << current->npcLine << "\"\n";

        if (current->options.empty()) {
            std::cout << "(End of conversation)\n";
            return;
        }

        for (size_t i = 0; i < current->options.size(); ++i) {
            std::cout << i + 1 << ". " << current->options[i].text << "\n";
        }

        int choice = 0;
        std::string input;
        std::cout << "Choose: ";
        std::getline(std::cin, input);
        
        try {
            choice = std::stoi(input);
        } catch (const std::exception&) {
            std::cout << "Invalid choice.\n";
            return;
        }

        if (choice >= 1 && choice <= (int)current->options.size()) {
            const DialogueOption& selected = current->options[choice - 1];

            switch (selected.action) {
                case DialogueAction::OpenShop:
                    std::cout << "\n[Opening shop...]\n";
                    showShop(player);
                    return;
                case DialogueAction::GiveItem:
                    std::cout << name << " gives you something.\n";
                    break;
                case DialogueAction::GiveQuestItem:
                    if (player->hasItem(selected.itemName)) {
                        std::cout << "You give the " << selected.itemName << " to " << name << ".\n";
                        player->removeItem(selected.itemName);
                        if (winRoom) {
                            std::cout << "\nSuddenly, a bright light surrounds you!\n";
                            player->setCurrentRoom(winRoom.get());
                            std::cout << winRoom->getDescription() << "\n";
                            std::cout << "\nCongratulations! You have completed the quest and completed the game!\n";
                        }
                    } else {
                        std::cout << "You don't have the " << selected.itemName << ".\n";
                    }
                    return;
                case DialogueAction::WinGame:
                    if (winRoom) {
                        std::cout << "\nSuddenly, a bright light surrounds you!\n";
                        player->setCurrentRoom(winRoom.get());
                        std::cout << winRoom->getDescription() << "\n";
                        std::cout << "\nCongratulations! You have completed the quest and completed the game!\n";
                    }
                    return;
                case DialogueAction::EndDialogue:
                    std::cout << "(The conversation ends.)\n";
                    return;
                case DialogueAction::None:
                    if (selected.next) {
                        current = selected.next;
                    } else {
                        return;
                    }
                    break;
            }
        } else {
            std::cout << "Invalid choice.\n";
            return;
        }
    }

    if (current) {
        std::cout << "\n" << name << " says: \"" << current->npcLine << "\"\n";
        std::cout << "(End of conversation)\n";
    }
}

void NPC::showShop(Player* player) {
    std::cout << "Here's what I have:\n";

    if (inventory.empty()) {
        std::cout << "Sorry, I have nothing to sell right now.\n";
        return;
    }

    for (size_t i = 0; i < inventory.size(); ++i) {
        std::cout << i + 1 << ". " << inventory[i]->getName() << " - " << inventory[i]->getPrice() << " gold\n";
    }

    std::cout << "Enter item number to buy or 0 to exit: ";
    int choice;
    std::cin >> choice;

    if (choice < 1 || choice > (int)inventory.size()) {
        std::cout << "Leaving the shop.\n";
        return;
    }

    auto item = inventory[choice - 1];

    if (player->spendGold(item->getPrice())) {
        std::cout << "You bought: " << item->getName() << "\n";
        player->addItem(item);
        // Remove item from NPC's inventory
        inventory.erase(inventory.begin() + (choice - 1));
    } else {
        std::cout << "You don't have enough gold.\n";
    }
}

void NPC::handleItemGive(const std::string& itemName) {
    if (hasQuestItem(itemName)) {
        std::cout << "The old man's eyes light up as he takes the " << itemName << ".\n";
        std::cout << "\"Ah, at last! The ancient artifact has returned to its rightful place.\"\n";
        std::cout << "He carefully places the " << itemName << " on a pedestal, and suddenly...\n";
        std::cout << "A bright light engulfs you!\n\n";
        gameEnd = true;  // Set the game end flag
    } else {
        std::cout << "The old man looks at the " << itemName << " with disinterest.\n";
        std::cout << "\"That's not what I'm looking for, my child.\"\n";
    }
}
