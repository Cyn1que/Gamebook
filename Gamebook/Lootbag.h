#pragma once
#include <vector>

#include "Object.h"
#include "Managers.h"
#include "Player.h"
#include "Item.h"

//! \brief  Class simulating lootbag that can be found on monsters or on the ground
class OLootbag : public OObject
{
public:
	//! \brief Allows to insert item into lootbag
	//! \param Item Inserted item
	void Insert(OItem Item);
	
	virtual void InteractWith(OObject & ah);
	virtual void InteractWith(APlayer & ah);

private:
	std::vector<OItem> ItemList; ///< Vector containing items located within lootbag
};

