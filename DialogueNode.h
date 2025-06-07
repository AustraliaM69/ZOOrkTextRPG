//
// Created by Samuel on 5/06/2025.
//

#ifndef DIALOGUENODE_H
#define DIALOGUENODE_H
#include <memory>
#include <string>
#include <vector>



enum class DialogueAction {
    None,
    OpenShop,
    GiveItem,
    EndDialogue,
    GiveQuestItem,
    WinGame
};
struct DialogueOption {
    std::string text;                        // The choice text shown to the player
    std::shared_ptr<class DialogueNode> next; // What node it links to
    DialogueAction action = DialogueAction::None;

    std::string itemName;
    int itemCost = 0;

    DialogueOption(const std::string& t, std::shared_ptr<DialogueNode> n = nullptr,
                   DialogueAction a = DialogueAction::None,
                   const std::string& item = "", int cost = 0)
        : text(t), next(n), action(a), itemName(item), itemCost(cost) {}
};


class DialogueNode {
public:
    std::string npcLine;                     // What the NPC says
    std::vector<DialogueOption> options;     // What the player can say
    bool isEndNode = false;                  // Whether this node should end the conversation

    DialogueNode(std::string line, bool end = false) : npcLine(std::move(line)), isEndNode(end) {}

    void addOption(const std::string& text, std::shared_ptr<DialogueNode> next) {
        options.push_back({text, next});
    }

    bool isTerminal() const {
        return options.empty() || isEndNode;
    }
};


#endif //DIALOGUENODE_H
