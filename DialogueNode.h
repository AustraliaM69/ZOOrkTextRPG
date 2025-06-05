//
// Created by Samuel on 5/06/2025.
//

#ifndef DIALOGUENODE_H
#define DIALOGUENODE_H
#include <memory>
#include <string>
#include <vector>


struct DialogueOption {
    std::string text;                        // The choice text shown to the player
    std::shared_ptr<class DialogueNode> next; // What node it links to
};

class DialogueNode {
public:
    std::string npcLine;                     // What the NPC says
    std::vector<DialogueOption> options;     // What the player can say

    DialogueNode(std::string line) : npcLine(std::move(line)) {}

    void addOption(const std::string& text, std::shared_ptr<DialogueNode> next) {
        options.push_back({text, next});
    }

    bool isTerminal() const {
        return options.empty();
    }
};


#endif //DIALOGUENODE_H
