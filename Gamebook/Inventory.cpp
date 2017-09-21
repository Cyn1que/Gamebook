#include "Inventory.h"

void OInventory::TakeItem(OItem Item) {
	ItemList.push_back(Item);
}

void OInventory::Open() {

	ListItems();
	PickChoice();

}

void OInventory::ListEquipped() {
	for (int i = 0; i < 4; i++) {

		if (Equipped[i] == false) {
			RenderManager::Show("Slot " + (std::to_string(i + 1)) + " is empty.");
		}
		else {
			RenderManager::Show(std::to_string(i + 1) + ") " + EquippedList[i].GetName());
			RenderManager::Show(EquippedList[i].ItemDetails());
		}
	}
	RenderManager::Show("");
}

void OInventory::ListItems() {
	
	RenderManager::Show("Equipped items:");
	ListEquipped();

	if (ItemList.empty()){
		RenderManager::Show("Your inventory is empty.");
	}

	RenderManager::Show("Your inventory:");

	int number = 1;

	for (auto & it : ItemList) {
		RenderManager::Show(std::to_string(number) + ") " + it.GetName());
		number++;
	}
	
}


void OInventory::PickChoice() {

	if (ItemList.empty()) 
		return;
	
	int ItemNumber;

	while ( (ItemNumber = InputManager::Read()) != 0) {
		if (ItemNumber < 1 || ItemNumber > (signed)ItemList.size()) {
			RenderManager::WrongChoice();
			continue;
		}
		else
			break;
	}

	RenderManager::Show("You've selected: " + ItemList[ItemNumber - 1].GetName());
	RenderManager::Show(ItemList[ItemNumber - 1].ItemDetails());
	RenderManager::Show("What would you like to do with said item?");
	RenderManager::Show("1) Equip   2) Destroy   3) Leave it be");

	while (int buffer = InputManager::Read()) {
		if (buffer == 1) {
			RenderManager::Show("Item equipped.");
			EquipItem(ItemList[ItemNumber - 1]);
			auto it = ItemList.begin();
			for (int i = 1; i != ItemNumber; i++) {
				it++;
			}
			ItemList.erase(it);
			break;
		}
		else if (buffer == 2) {
			auto it = ItemList.begin();
			for (int i = 1; i != ItemNumber; i++) {
				it++;
			}
			ItemList.erase(it);
			RenderManager::Show("Item destroyed.");
			break;
		}
		else if (buffer == 3) {
			break;
		}
		else {
			RenderManager::WrongChoice();
			continue;
		}
	}
}

std::string OInventory::CreateSaveList() const {
	std::string tmp;
	for (auto & it : ItemList) {
		tmp += it.ItemSaveDetails() + "Unequipped\n";
	}
	for (int i = 0; i < 4; i++) {
		if(Equipped[i])
			tmp += EquippedList[i].ItemSaveDetails() + "Equipped\n";
	}

	return tmp;

}

json OInventory::toJSON() const {
	json Items;
	for (auto & it : ItemList) {
		Items.push_back(it.toJSON(false));
	}
	for (int i = 0; i < 4; i++) {
		if (Equipped[i])
			Items.push_back(EquippedList[i].toJSON(true));
	}
	return Items;
}

void OInventory::EquipItem(OItem Item){
	if (Equipped[Item.GetCat()] == false) {
		EquippedList[Item.GetCat()] = Item;
		Equipped[Item.GetCat()] = true;
	}
	else {
		TakeItem(EquippedList[Item.GetCat()]);
		EquippedList[Item.GetCat()] = Item;
	}

}

int OInventory::size() const {
	int tmp = 0;
	for (int i = 0; i < 4; i++) {
		if (Equipped[i])
			tmp++;
	}
	return ItemList.size() + tmp;
}

SItemStats OInventory::GetStats() const {
	SItemStats returnTable;
	returnTable.AccuracyBonus = EquippedList[0].GetItemStats().AccuracyBonus + EquippedList[1].GetItemStats().AccuracyBonus +
								EquippedList[2].GetItemStats().AccuracyBonus + EquippedList[3].GetItemStats().AccuracyBonus;
	returnTable.DamageBonus = EquippedList[0].GetItemStats().DamageBonus + EquippedList[1].GetItemStats().DamageBonus +
						      EquippedList[2].GetItemStats().DamageBonus + EquippedList[3].GetItemStats().DamageBonus;
	returnTable.HealthBonus = EquippedList[0].GetItemStats().HealthBonus + EquippedList[1].GetItemStats().HealthBonus +
							  EquippedList[2].GetItemStats().HealthBonus + EquippedList[3].GetItemStats().HealthBonus;
	returnTable.SpeedBonus = EquippedList[0].GetItemStats().SpeedBonus + EquippedList[1].GetItemStats().SpeedBonus +
						     EquippedList[2].GetItemStats().SpeedBonus + EquippedList[3].GetItemStats().SpeedBonus;

	return returnTable;
}


