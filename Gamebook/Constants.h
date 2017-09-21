#pragma once

enum class ExplorationStatus {
	Success,
	QuitInstance,
	Failure,
	InProgress
};

enum class WorldStatus {
	Finished,
	Paused,
	Lost,
	InProgress
};
//! \brief Data structure for storing item's stat bonuses
struct SItemStats {
	int HealthBonus; ///< Bonus health the item provides
	int DamageBonus; ///< Bonus damage the item provides
	int SpeedBonus; ///< Bonus speed the item provides
	int AccuracyBonus; ///< Bonus accuracy the item provides
};
//! \brief Data structure for storing player's natural stats
struct SPlayerStats {

	//! \brief Basic constructor for structure's instance
	SPlayerStats(int H, int D, int S, int A) :
		Health (H), Damage (D), Speed (S), Accuracy (A)
	{}

	int Health; ///< Player's basic health
	int Damage; ///< Player's basic damage 
	int Speed; ///< Player's basic speed 
	int Accuracy; ///< Player's basic accuracy
};

enum class MenuOption { NEW, CONTINUE, LOAD, SAVE, EXIT };

enum class SpecialAbility { Frostbolt, Crit, Fireball };

enum class GameState { MENU, INGAME, FINISHED };

typedef int Stat;

//! \brief Data structure for storing player's combat data during fights
struct SPlayerSnapshot {
	Stat MissChance;			///< Player's current miss chance
	Stat Damage;				///< Player's current damage
	Stat Health;				///< Player's current health
	Stat Speed;					///< Player's current speed
	Stat MaxHealth;				///< Player's maximum health upon entering combat
	SpecialAbility Special;		///< Player's learned special ability

	Stat Shield;				///< Player's current shield amount

	bool vulnerable;			///< Indicator of whether player is currently vulnerable to extra damage
	bool SpecialUsed;			///< Indicator of whether player has already used his special this fight
	int  CritCounter;			///< Indicator of how many of player's next attacks are going to be crits
	bool Frozen;				///< Indicator of whether player is currently freezing his opponent
};