#pragma once

#include <string>
#include <vector>
#include <memory>

#include "Object.h"
#include "Managers.h"


typedef int LocationID;

//! \brief Class representing location within the World
class Location 
{
public:
	//! \brief Constructor that creates a fully specified location
	Location(std::string SText, std::vector<std::pair<LocationID, std::string >> MConnectedLocations, std::vector<std::shared_ptr<OObject>> VInteractibles);

	//! \brief Checks whether Location has any interactable objects within it
	//! \return Truth value of said statement
	bool IsEmpty() const;
	//! \brief Checks whether Location has any paths leading from it
	//! \return Truth value of said statement
	bool Deadend() const;
	//! \brief Shows possible paths leading from the location
	void GetDirections() const;


	//! \brief Offers address to new location based on user input
	//! \param input User input indicating which direction he wants to go in
	//! \return ID of selected Location
	LocationID SetDirections(int input);

	//! \brief Offers interaction interface with one of the interactables located in the location
	//! \return Interface for interaction
	std::shared_ptr<OObject> Interact();


	//! \brief Finds ID of given connection
	//! \param Target Targetted connection
	//! \return Location ID
	LocationID GetConnectionID(int Target) const;
	//! \brief Returns the list of connections from this location
	//! \return Amount of connections
	int ConnectedAmount() const;
	//! \brief Offers access to Location's description text
	//! \return String containing location text
	const std::string & GetText() const;

	//! \brief Deletes active interaction
	void ClearInteraction();

private:
	std::string Text; ///< Text describing the location
	std::vector<std::pair<LocationID, std::string>> ConnectedLocations; ///< Vector of locations that have path leading to it
	std::vector<std::shared_ptr<OObject>> Interactibles; ///< Interactable objects located withing the location


};

