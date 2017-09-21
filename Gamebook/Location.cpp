#include "Location.h"



Location::Location(std::string SText, std::vector<std::pair<LocationID, std::string >> MConnectedLocations, std::vector<std::shared_ptr<OObject>> VInteractibles)
	: Text(SText),
	  ConnectedLocations (MConnectedLocations),
	  Interactibles (VInteractibles) {
}

bool Location::IsEmpty() const{
	return Interactibles.empty();
}

bool Location::Deadend() const
{
	if (ConnectedLocations.empty())
		return true;
	else
		return false;

}

void Location::GetDirections() const {
	int i = 1;
	for (auto const &Loc : ConnectedLocations) {
		RenderManager::Show(std::to_string(i) + " - " + Loc.second);
		i++;
	}
}
LocationID Location::SetDirections(int input) {
	if (input < 1 || input > (signed)ConnectedLocations.size()) {
		RenderManager::WrongChoice();
		return -1;
	}
	else
		return ConnectedLocations[input - 1].first;

}

int Location::GetConnectionID(int Target) const
{
	return ConnectedLocations[Target].first;
}

std::shared_ptr<OObject> Location::Interact()
{
	return *(Interactibles.begin());
}

int Location::ConnectedAmount() const
{
	return ConnectedLocations.size();
}

const std::string & Location::GetText() const
{
	return Text;
}

void Location::ClearInteraction()
{
	Interactibles.erase(Interactibles.begin());
}