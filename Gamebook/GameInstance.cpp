#include "GameInstance.h"

GameInstance::GameInstance(std::ifstream & SelectedWorldFile, std::ifstream & SelectedSaveFile)
	: valid (true) {
	MainWorld = std::make_unique<World>(SelectedWorldFile, SelectedSaveFile);
}

GameInstance::GameInstance(std::ifstream & SelectedWorldFile)
	: valid(true) {
	
	MainWorld = std::make_unique<World>(SelectedWorldFile);
}

void GameInstance::Begin() {
	MainWorld->Introduction();
	GameLoop();
}

bool GameInstance::IsValid() 
{
	return valid;
}

void GameInstance::GameLoop() {

	while (true) {
		RenderManager::Show(MainWorld->GetCurLocation());
		auto ExplorationEval = MainWorld->ExploreWorld();
		if (ExplorationEval == WorldStatus::Finished) {
			valid = false;
			RenderManager::Show("Congratulations on finishing your journey! Where to next?");
			RenderManager::Show("");
			break;
		}
			
		if (ExplorationEval == WorldStatus::Lost) {
			valid = false;
			RenderManager::Show("Game over. Better luck next time! Where to next?");
			RenderManager::Show("");
			break;
		}
			
		else if (ExplorationEval == WorldStatus::Paused)
			break;
	}
}


std::shared_ptr<APlayer> GameInstance::GetSaveData() const{
	return MainWorld->Player;
}
