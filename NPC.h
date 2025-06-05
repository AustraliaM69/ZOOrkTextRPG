//
// Created by Samuel on 5/06/2025.
//

#ifndef NPC_H
#define NPC_H
#include <iostream>
#include <memory>
#include <string>

#include "DialogueNode.h"


class NPC {
private:
    std::string name;
    std::string description;
    std::shared_ptr<DialogueNode> dialogueRoot;

public:
    NPC(const std::string& name, const std::string& description,const std::shared_ptr<DialogueNode>& root);

    std::string getName() const;
    std::string getDescription() const;

    void startDialogue();
};


#endif //NPC_H
