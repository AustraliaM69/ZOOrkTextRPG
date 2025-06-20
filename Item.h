//
// Created by Richard Skarbez on 5/7/23.
//

#ifndef ZOORK_ITEM_H
#define ZOORK_ITEM_H

#include <memory>

#include "Command.h"
#include "GameObject.h"
#include "NullCommand.h"

class Item : public GameObject {
public:
    Item(const std::string &, const std::string &);

    Item(const std::string &n, const std::string &d, int p);

    Item(const std::string &, const std::string &, std::shared_ptr<Command>);

    int getPrice()const{return price;}
    std::string getName()const{return name;}


    virtual void use();

    void setUseCommand(std::shared_ptr<Command>);

protected:
    std::shared_ptr<Command> useCommand;
    int price;
};

#endif //ZOORK_ITEM_H
