#include "HealthPotion.h"
#include "RoomDefaultEnterCommand.h"
#include "Passage.h"
#include "Player.h"
#include "Room.h"
#include "Weapon.h"
#include "ZOOrkEngine.h"
#include "Item.h"
#include "Enemy.h"
#include "NPC.h"
#include "QuestItem.h"



int main() {

    //INIT ---- I know this is messy but it works

    //ROOMS -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
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
    auto victoryRoom = std::make_shared<Room>("Victory Chamber", "You stand in a magnificent chamber filled with golden light. The walls are adorned with ancient runes that tell the story of your triumph. The old man smiles at you, his true form revealed as a guardian of the realm.");

    //PASSAGES -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    Passage::createBasicPassage(stable.get(), forestPath.get(), "east", true);
    Passage::createBasicPassage(forestPath.get(), glade.get(), "east", true);
    Passage::createBasicPassage(stable.get(), rockyPath.get(), "west", true);
    Passage::createBasicPassage(rockyPath.get(), caveEntrance.get(), "west", true);
    Passage::createBasicPassage(caveEntrance.get(), forkedTunnel.get(), "west", true);
    Passage::createBasicPassage(forkedTunnel.get(), mossyCavern.get(), "north", true);
    Passage::createBasicPassage(forkedTunnel.get(), crystalChamber.get(), "south", true);
    Passage::createBasicPassage(crystalChamber.get(), hiddenShrine.get(), "west", true);
    Passage::createBasicPassage(hiddenShrine.get(), caveDepths.get(), "west", true);

    //ITEMS -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //Starter Sword
    auto sword = new Weapon("Starter Sword", "A gleaming silver sword with runes.",5);
    stable->addItem(std::shared_ptr<Item>(sword));
    //Potion
    auto healthPotion = std::make_shared<HealthPotion>("Health Potion", "Heals 25 Health", 25,20);
    stable->addItem(std::shared_ptr<Item>(healthPotion));
    mossyCavern->addItem(std::shared_ptr<Item>(healthPotion));
    glade->addItem(std::shared_ptr<Item>(healthPotion));
    //Ancient Amulet
    auto ancientAmulet = std::make_shared<QuestItem>("Ancient Amulet", "An ancient amulet pulsing with mysterious energy. The old man might be interested in this...");
    caveDepths->addItem(ancientAmulet);
    //Steel Sword
    auto steelSword = new Weapon("Steel Sword","A sword made of fine steel",15);
    glade->addItem(std::shared_ptr<Item>(steelSword));
    //Greater Health Potion
    auto greatHealthPotion = std::make_shared<HealthPotion>("Greater Health Potion","Heals 75 health",75,50);
    //Katana
    auto katana = new Weapon("Katana","A very sharp blade",25);
    mossyCavern->addItem(std::shared_ptr<Item>(katana));

    // NPCS -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    //Oldman
    auto root = std::make_shared<DialogueNode>("Hello, traveler. What brings you here?");
    auto askWho = std::make_shared<DialogueNode>("I'm just a tired old man.", true);
    auto askPlace = std::make_shared<DialogueNode>("To the west is a great cave, I believe I lost something there...", true);
    auto questDialogue = std::make_shared<DialogueNode>("Ah, you have the ancient amulet! This is what I've been searching for...");
    auto goodbye = std::make_shared<DialogueNode>("Safe travels, then.", true);
    root->addOption("Who are you?", askWho);
    root->addOption("What is this place?", askPlace);
    root->addOption("I have something for you...", questDialogue);
    root->addOption("Goodbye.", goodbye);
    questDialogue->options.push_back(DialogueOption("Give the Ancient Amulet", nullptr, DialogueAction::GiveQuestItem, "Ancient Amulet"));
    std::shared_ptr<NPC> oldMan = std::make_shared<NPC>("oldman","OldMan: A weary traveler leaning on a stick.",root);
    oldMan->setQuestItem("Ancient Amulet");
    oldMan->setWinRoom(victoryRoom);
    stable->addNPC(oldMan);

    //ShopKeeper
    auto shopRoot = std::make_shared<DialogueNode>("Welcome to my shop!");
    auto shopMenu = std::make_shared<DialogueNode>("Here's what I have for sale:", true);
    shopRoot->options.push_back(DialogueOption("What do you sell?", shopMenu, DialogueAction::OpenShop));
    shopRoot->options.push_back(DialogueOption("Bye", nullptr, DialogueAction::EndDialogue));
    std::shared_ptr<NPC> shopkeeper = std::make_shared<NPC>("Shopkeeper", "Shopkeeper: A shady merchant", shopRoot);
    shopkeeper->addItemToInventory(healthPotion);
    shopkeeper->addItemToInventory(healthPotion);
    shopkeeper->addItemToInventory(greatHealthPotion);
    stable->addNPC(shopkeeper);

    //ENEMIES -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //Goblin
    auto goblin = std::make_shared<Enemy>("goblin", "Goblin: A sneaky goblin lurks here.", 10, 10,15);
    forestPath->addEnemy(goblin);
    auto fatGoblin = std::make_shared<Enemy>("Fat Goblin","Fat Goblin: A fat goblin stands tall", 15,10,20);
    forestPath->addEnemy(fatGoblin);
    //Skeleton
    auto skeleton = std::make_shared<Enemy>("Skeleton", "Skeleton: A man of bones", 25, 12,25);
    glade->addEnemy(skeleton);
    rockyPath->addEnemy(skeleton);
    //Sorcerer
    auto sorcerer = std::make_shared<Enemy>("Sorcerer","Sorcerer: A dangerous looking mage",100,24,100);
    hiddenShrine->addEnemy(sorcerer);
    //Crystal Beast
    auto crystalBeast = std::make_shared<Enemy>("Crystal Beast","Crystal Beast: A huge creature with sharp gems all over it.",75,18,85);
    crystalChamber->addEnemy(crystalBeast);

    //MENU ART
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
