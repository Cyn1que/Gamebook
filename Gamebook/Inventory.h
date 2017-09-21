#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include <map>

#include "Managers.h"
#include "Item.h"
#include "json.hpp"

using json = nlohmann::json;

//! \brief Class simulating inventory containing various items in bag and equipped items
class OInventory 
{
public:	
	//! \brief Allows inventory to accept item into bag
	//! \param Item Accepted item
	void TakeItem(OItem Item);
	//! \brief Allows inventory to equip item
	//! \param Item Equipped item
	void EquipItem(OItem Item);

	//! \brief Opens inventory UI
	void Open();
	//! \brief Lists all equipped items
	void ListEquipped();
	//! \brief Lists all items in bag
	void ListItems();
	//! \brief Takes action upon selected item
	void PickChoice();
	
	//! \brief Checks size of the inventory
	//! \return Integer equal to amount of items in inventory
	int size() const;

	//! \brief Aggregates all stat bonuses of equipped items
	//! \return Strcture cointaining stat bonuses
	SItemStats GetStats() const;

	//! \brief Creates save string containing information about all items in the inventory
	//! \return Save string
	std::string CreateSaveList() const;

	json toJSON() const;

private:
	std::vector<OItem> ItemList; ///< Vector containing items in bag
	OItem EquippedList[4]; ///< Array containing equipped items
	bool Equipped[4] = { false };	///< Control structure showing which equipment slots are taken

};

