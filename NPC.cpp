//
// Created by Samuel on 5/06/2025.
//

#include "NPC.h"

#include <sstream>

NPC::NPC(const std::string& name, const std::string& description, const std::shared_ptr<DialogueNode>& root)
    : name(name), description(description), dialogueRoot(std::move(root)) {}

std::string NPC::getName() const {
    return name;
}

std::string NPC::getDescription() const {
    return description;
}

void NPC::startDialogue() {
    std::shared_ptr<DialogueNode> current = dialogueRoot;

    while (current) {
        std::cout << "\n" << name << " says: \"" << current->npcLine << "\"\n";

        if (current->isTerminal()) {
            std::cout << "(End of conversation)\n";
            break;
        }

        for (size_t i = 0; i < current->options.size(); ++i) {
            std::cout << i + 1 << ". " << current->options[i].text << "\n";
        }

        int choice = 0;
        while (true) {
            std::cout << "Choose: ";
            std::string input;
            std::getline(std::cin, input);

            std::stringstream ss(input);
            if ((ss >> choice) && (choice >= 1) && (choice <= (int)current->options.size())) {
                break; // valid input
            } else {
                std::cout << "Invalid choice. Please enter a number between 1 and " << current->options.size() << ".\n";
            }
        }

        current = current->options[choice - 1].next;
    }
}