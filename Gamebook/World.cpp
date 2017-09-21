#include "World.h"
#include "json.hpp"

World::World(std::ifstream & SelectedWorldFile) {
	Player = DataManager::GetPlayerCreationDetails();

	json WorldData;
	SelectedWorldFile >> WorldData;

	Name = DataManager::GetWorldName(WorldData);
	Description = DataManager::GetWorldDescription(WorldData);
	Locations = DataManager::GetLocations(WorldData);
}

World::World(std::ifstream & SelectedWorldFile, std::ifstream & SelectedSaveFile) {
	Player = DataManager::LoadPlayer(SelectedSaveFile);

	json WorldData;
	SelectedWorldFile >> WorldData;

	Name = DataManager::GetWorldName(WorldData);
	Description = DataManager::GetWorldDescription(WorldData);
	Locations = DataManager::GetLocations(WorldData);
}

std::string World::GetCurLocation() {
	auto it = Locations.find(Player->Locate());
	if (it != Locations.end()) {
		return it->second.GetText();
	}
	else {
		return "Application error";
	}
}

WorldStatus World::ExploreWorld() {
	auto ExplorationEval = (Player->ExploreLocation(Locations.at(Player->Locate())));

	if (ExplorationEval == ExplorationStatus::QuitInstance) {
		return WorldStatus::Paused;
	}
	else if (ExplorationEval == ExplorationStatus::Failure) {
		return WorldStatus::Lost;
	}
	else if (ExplorationEval == ExplorationStatus::Success) {
		return WorldStatus::Finished;
	}
	else
		return WorldStatus::InProgress;
}

void World::MovePlayer(LocationID NewLocation) {
	Player->Move(NewLocation);
}

void World::Introduction() const {
	RenderManager::Show("\n\nWelcome to " + Name);
	RenderManager::Show(Description + "\n- - - - - - - - - - - - - - - - - - ");
}
