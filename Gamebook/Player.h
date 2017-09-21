#pragma once
#include "Character.h"
#include <memory>

#include "Location.h"
#include "Object.h"
#include "Inventory.h"

class ANonPlayerChar;

//! \brief Class describing inner working of Player character within the game world
class APlayer : public ACharacter
{
public:

	//! \brief Constructor that creates player with empty inventory
	APlayer(int IHealth, int IDamage, int ISpeed, int IMissChance, int IPosition, SpecialAbility ISpecialAbility);
	//! \brief Constructor that creates player some items already present in the inventory
	APlayer(int IHealth, int IDamage, int ISpeed, int IMissChance, OInventory SInventory, int IPosition, SpecialAbility ISpecialAbility);
	
	//! \brief Sends player to given Location and lets him interact with any present objects
	ExplorationStatus ExploreLocation(Location & Loc);

	//! \brief Moves player to a new location
	void Move(LocationID);

	//! \brief Returns player's current position
	LocationID Locate() const;


	//! \brief Makes player interact with given Object's interface
	void Interact(std::shared_ptr<OObject> Object);

	//! \brief Basic interaction with any given object
	void InteractWith(OObject & Object);

	//! \brief Basic interaction with NPC 
	void InteractWith(ANonPlayerChar & Player);

	//! \brief Basic interaction with another player
	void InteractWith(APlayer & Player);

	//! \brief Visitor pattern helping method
	virtual void InteractWith(std::shared_ptr<OObject>);

	//! \brief Put item into player's inventory
	void TakeItem(OItem Item);

	//! \brief Checks player's current inventory size
	int InventorySize() const;

	//! \brief Checks what are the player's stats
	SPlayerStats GetPlayerStats() const;

	//! \brief Checks what special ability player has learned
	SpecialAbility GetSpecial() const;

	//! \brief Creates Save string containing player inventory's data
	std::string CreateInvSaveList () const;
	const OInventory & GetInventory();

	//! \brief RIP
	void Death();

private:
	bool Alive; ///< Indicator of whether player is still alive
	SpecialAbility Special;  ///< Indicator of player's taught special ability
	LocationID CurrentLocation;  ///< Player's current position within the world
	OInventory Inventory;  ///< Player's inventory
};

