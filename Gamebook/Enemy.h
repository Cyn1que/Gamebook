#pragma once
#include "NonPlayerChar.h"
#include "Managers.h"


//! \brief Class representing Enemy that's able to interact (fight) with the player
class AEnemy :
	public ANonPlayerChar
{
public:

	//! \brief Constructor that creates enemy with empty Lootbag
	AEnemy(std::string SName, int IHealth, int IDamage, int ISpeed, int IMissChance);

	//! \brief Constructor that creates enemy including items in his Lootbag
	AEnemy(std::string SName, int IHealth, int IDamage, int ISpeed, int IMissChance, std::shared_ptr<OLootbag> LootBag);

	//! \brief Virtual function that enables any objects inhereting from this class to interact with any other classes inhereting from OObject using Double Dispatch pattern
	virtual void InteractWith(OObject & );

	//! \brief Virtual function that enables any objects inhereting from this class to interact with APlayer using Double Dispatch pattern
	virtual void InteractWith(APlayer & );

private:
	SPlayerSnapshot PlayerSnapshot; ///< Snapshot of Player's stats at beginning of the fight

	//! \brief Function that initiates the fight, alternating between turns
	//! \param Player Player data
	void Fight(SPlayerSnapshot & Player);
	//! \brief Plays out Enemy turn
	//! \param Player Player data
	void EnemyTurn(SPlayerSnapshot & Player);
	//! \brief Plays out Monster turn
	//! \param Player Player data
	void PlayerTurn(SPlayerSnapshot & Player);
};

