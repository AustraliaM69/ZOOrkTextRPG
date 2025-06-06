
#include "RoomDefaultEnterCommand.h"
#include "Passage.h"
#include "Player.h"
#include "Room.h"
#include "Weapon.h"
#include "ZOOrkEngine.h"


int main() {
    auto stable = std::make_shared<Room>("Stable", "You are at a quiet stable on the edge of a misty valley. A hooded man stands by a covered carriage. The horses snort but do not move.");
    stable->setShortDescription("A quiet stable on the edge of a misty valley with a hooded man and horses.");

    auto forestPath = std::make_shared<Room>("Forest Path", "A dirt path winds through whispering trees. Strange lights flicker between the trunks.");
    forestPath->setShortDescription("A narrow dirt path lined with ancient oaks.");

    auto glade = std::make_shared<Room>("Glade", "You stand in a glowing glade where the moonlight seems frozen. A stone circle hums faintly.");
    glade->setShortDescription("An open glade where sunlight pierces the canopy.");

    auto rockyPath = std::make_shared<Room>("Rocky Path", "A rocky trail snakes up the hill toward a dark cave mouth. Crows watch you silently from a gnarled tree.");
    rockyPath->setShortDescription("A rocky trail snaking up a hill towards a cave.");

    auto caveEntrance = std::make_shared<Room>("Cave Entrance", "A cold draft flows from the cave. Symbols are etched in the stone above.");
    caveEntrance->setShortDescription("A yawning cave mouth, damp air seeping out.");

    auto forkedTunnel = std::make_shared<Room>("Forked Tunnel", "The tunnel splits here. The NORTH path smells damp and earthy, the SOUTH sharp and metallic.");
    forkedTunnel->setShortDescription("A split in the tunnel, with two paths.");

    auto mossyCavern = std::make_shared<Room>("Mossy Cavern", "Thick moss carpets the floor. Water drips rhythmically. A quiet peace fills the air.");
    mossyCavern->setShortDescription("A cavern covered in moss.");

    auto crystalChamber = std::make_shared<Room>("Crystal Chamber", "Jagged crystals line the walls, pulsing with dim light. A narrow passage leads deeper.");
    crystalChamber->setShortDescription("A cavern covered in jagged crystals.");

    auto hiddenShrine = std::make_shared<Room>("Hidden Shrine", "An old altar rests beneath glowing runes. You feel watched.");
    hiddenShrine->setShortDescription("An old altar.");

    auto caveDepths = std::make_shared<Room>("Cave Depths", "You reach the end of the cave. A chasm blocks the path forward. Something stirs in the darkness.");
    caveDepths->setShortDescription("Darkness.");


    Passage::createBasicPassage(stable.get(), forestPath.get(), "east", true);
    Passage::createBasicPassage(forestPath.get(), glade.get(), "east", true);


    Passage::createBasicPassage(stable.get(), rockyPath.get(), "west", true);
    Passage::createBasicPassage(rockyPath.get(), caveEntrance.get(), "west", true);
    Passage::createBasicPassage(caveEntrance.get(), forkedTunnel.get(), "west", true);
    Passage::createBasicPassage(forkedTunnel.get(), mossyCavern.get(), "north", true);
    Passage::createBasicPassage(forkedTunnel.get(), crystalChamber.get(), "south", true);
    Passage::createBasicPassage(crystalChamber.get(), hiddenShrine.get(), "west", true);
    Passage::createBasicPassage(hiddenShrine.get(), caveDepths.get(), "west", true);


    auto root = std::make_shared<DialogueNode>("Hello, traveler. What brings you here?");
    auto askWho = std::make_shared<DialogueNode>("I'm just a tired old man.");
    auto askPlace = std::make_shared<DialogueNode>("This forest hides many secrets.");
    auto goodbye = std::make_shared<DialogueNode>("Safe travels, then.");
    root->addOption("Who are you?", askWho);
    root->addOption("What is this place?", askPlace);
    root->addOption("Goodbye.", goodbye);
    std::shared_ptr<NPC> oldMan = std::make_shared<NPC>("oldman","OldMan: A weary traveler leaning on a stick.",root);

    stable->addNPC(oldMan);
    auto sword = new Weapon("sword", "A gleaming silver sword with runes.",5);
    auto apple = new Item("apple", "A crisp red apple.");
    auto goblin = std::make_shared<Enemy>("goblin", "A sneaky goblin lurks here.", 10, 2,10);
    forestPath->addEnemy(goblin);

    stable->addItem(std::shared_ptr<Item>(sword));
    caveEntrance->addItem(std::shared_ptr<Item>(apple));



    std::cout << R"(
 _____           _                __       _ _    ___                  _
| ____|_ __ ___ | |__   ___ _ __ / _| __ _| | |  / _ \ _   _  ___  ___| |_
|  _| | '_ ` _ \| '_ \ / _ \ '__| |_ / _` | | | | | | | | | |/ _ \/ __| __|
| |___| | | | | | |_) |  __/ |  |  _| (_| | | | | |_| | |_| |  __/\__ \ |_
|_____|_| |_| |_|_.__/ \___|_|  |_|  \__,_|_|_|  \__\_\\__,_|\___||___/\__|

)" << "\n";


    ZOOrkEngine zoork(stable);

    zoork.run();

    return 0;
}
