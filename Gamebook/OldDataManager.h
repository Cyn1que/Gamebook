#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

#include "Player.h"
#include "Location.h"
#include "Enemy.h"
#include "Item.h"
#include "Lootbag.h"

//! \brief Utility class for managing reading and writing into files and hence saving and loading game data
class DataManager
{
public:
	//! \brief Creates player from basic template
	static std::shared_ptr<APlayer> GetPlayerCreationDetails();
	//! \brief Loads player data from given file stream
	static std::shared_ptr<APlayer> LoadPlayer(std::ifstream & SelectedSaveFile);
	//! \brief Saves player data from given Player instance into given file stream
	static void SavePlayer(std::shared_ptr<APlayer>, std::ofstream &);

	//! \brief Reads World's name from given file stream
	static std::string GetWorldName(std::ifstream & SelectedWorldFile);
	//! \brief Reads World's description from given file stream
	static std::string GetWorldDescription(std::ifstream & SelectedWorldFile);
	//! \brief Creates map of Locations located within the World from reading given file stream
	static std::map<LocationID, Location> GetLocations(std::ifstream & SelectedWorldFile);
	//! \brief Reads information about single location from given file stream
	static Location ReadLocation(std::ifstream & SelectedWorldFile);

	//! \brief Reads information about single item from given file stream
	static OItem ReadItem(std::ifstream & SelectedWorldFile);

	//! \brief eads information about single enemy from given file stream
	static std::shared_ptr<OObject> LoadEnemy(std::ifstream & SelectedWorldFile);

};

#pragma once
