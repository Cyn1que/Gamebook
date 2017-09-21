//Author: Ondrej Slejtr
//slejtond@fit.cvut.cz

#pragma once

#include <string>

#include "Managers.h"
#include "json.hpp"

using json = nlohmann::json;


//! \brief Class describing item objects that can be picked up, thrown away and equipped for stat bonuses.
class OItem 
{
public:
	//! \brief Constructor that creates placeholder item
	OItem();
	//! \brief Constructor for fully defined item
	//! \param SName String with item's name
	//! \param ItemStats Structure with item's stats
	//! \param CategoryNumber ID of equipment category
	OItem(std::string SName, SItemStats ItemStats, int CategoryNumber);

	//! \brief Provides data necessary to present item data to user
	//! \return String with item's details
	const std::string ItemDetails() const;
	//! \brief Provides data necessary to save item's details into Save file
	//! \return String with item's save details
	const std::string ItemSaveDetails() const;

	//! \brief Provides item's name
	//! \return String with item's name
	const std::string & GetName() const;
	//! \brief Provides item's equipment category
	//! \return String with item's equipment category
	const int GetCat() const;
	//! \brief Provides item's stats
	//! \return String with item's stats
	const SItemStats & GetItemStats() const;

	json toJSON(bool isEquipped) const;

private:
	SItemStats ItemStats; ///< Structure with item's stats
	std::string Name; ///< Item's name
	int CategoryNumber; ///< ID of equipment category
};

