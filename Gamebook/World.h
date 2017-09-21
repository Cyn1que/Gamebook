#pragma once
#include <string>
#include <map>
#include <memory>
#include <vector>

#include "Location.h"
#include "Player.h"
#include "DataManager.h"



//! \brief Class describing game World with all its features
class World
{
public:

	//! \brief Constructor for fresh worlds that will be stationed in brand new state
	World(std::ifstream & SelectedWorldFile);

	//! \brief Constructor for worlds that have already been altered by previous play
	World(std::ifstream & SelectedWorldFile, std::ifstream & SelectedSaveFile);
	
	//! \brief Offers information about Player's current location within the world
	std::string GetCurLocation();

	//! \brief Begins exploration of the world and returns its status
	WorldStatus ExploreWorld();

	//! \brief Moves player to a new location
	void MovePlayer(LocationID NewLocation);
	//! \brief Gives brief introduction to the world
	void Introduction() const;
	std::shared_ptr<APlayer> Player; ///< Pointer to player object within the world

private:
	std::string Name; ///< Name of the world
	std::string Description; ///< World's description
	std::map<LocationID, Location> Locations; ///< Map of locations within the world
	
};

