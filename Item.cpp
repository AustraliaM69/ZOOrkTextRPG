//
// Created by Richard Skarbez on 5/7/23.
//

#include "Item.h"

#include <utility>

Item::Item(const std::string &n, const std::string &d,int p): GameObject(n, d),price(p),
                                                         useCommand(std::make_shared<NullCommand>()) {}

Item::Item(const std::string &n, const std::string &d, std::shared_ptr<Command> c) : GameObject(n, d),
                                                                                     useCommand(std::move(c)) {}
Item::Item(const std::string &n, const std::string &d): GameObject(n, d) {

}


void Item::use() {
    useCommand->execute();
}

void Item::setUseCommand(std::shared_ptr<Command> c) {
    useCommand = c;
}
