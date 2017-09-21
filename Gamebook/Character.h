#pragma once

#include <memory>
#include <string>

#include "Actor.h"
#include "Constants.h"

typedef int Stat;

//! \brief Class representing general concept of Character within game world - Actor that has stats, such as player or enemy
class ACharacter : public AActor {
public:
	//! \brief Returns stats of the character
	//! \return Structure made of stats
	SPlayerStats GetStats() const;

protected:
	int Health;			///< Character's health
	int Damage;			///< Character's damage
	int Speed;			///< Character's speed
	int MissChance;		///< Character's misschance

};

