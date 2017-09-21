#include "Lootbag.h"

void OLootbag::Insert(OItem Item) {
	ItemList.emplace_back(Item);
}


void OLootbag::InteractWith(OObject & ah){
}

void OLootbag::InteractWith(APlayer & Player) {


	RenderManager::Show("");

	for (auto & it : ItemList) {

		RenderManager::Show("You've found an interesting object: " + it.GetName());
		RenderManager::Show(it.ItemDetails());
		RenderManager::Show("What would like to do with it?");
		RenderManager::Show("1 - Pick it up. | 2 - Leave it be.");

		int choice;

		while (true) {
			choice = InputManager::Read();

			RenderManager::Show(std::to_string(choice));

			if (choice == 1) {
				Player.TakeItem(OItem(it));
				RenderManager::Show("Item picked up.");
				break;
			}
			else if (choice == 2) {
				RenderManager::Show("Item left behind.");
				break;
			}
			else {
				RenderManager::WrongChoice();
				RenderManager::Show(std::to_string(choice));
			}
				
		}
	
	}
}
