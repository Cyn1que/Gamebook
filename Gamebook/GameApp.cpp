#include "GameApp.h"

GameApp::GameApp() : CurrentGameState (GameState::MENU)
{
	CurrentGameState = GameState::MENU;
	MainMenu = std::make_unique<GameMenu>();
}

void GameApp::Play() {

	while (CurrentGameState != GameState::FINISHED) {
		if (CurrentGameState == GameState::MENU) {
			ProcessMenuChoice(MainMenu->GetMenuChoice());
		}
		else if (CurrentGameState == GameState::INGAME) {
			if (MainGameInstance == nullptr || !MainGameInstance->IsValid()) {
				RenderManager::Show("Cannot continue playing, no valid game in progress.\n");
			}
			else 
				MainGameInstance->Begin();
		}

		SwapGameState();
	}
}

void GameApp::ExitApp() {
	CurrentGameState = GameState::FINISHED;
}

void GameApp::SwapGameState()
{
	if (CurrentGameState == GameState::MENU) {
		CurrentGameState = GameState::INGAME;
	}
	else if (CurrentGameState == GameState::INGAME) {
		CurrentGameState = GameState::MENU;
	}
}

void GameApp::ProcessMenuChoice(MenuSelection MenuOpt) {

	try {
		switch (MenuOpt) {
		case 1:
			NewGame();
			break;
		case 2:
			ContinueGame();
			break;
		case 3:
			SaveGame();
			break;
		case 4:
			LoadGame();
			break;
		case 5:
			ExitApp();
			break;

		}
	}
	catch (const std::invalid_argument& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
		ExitApp();
	}
}

void GameApp::NewGame() {
	
	RenderManager::Show("Name of the World file? ");
	std::string WorldFile = InputManager::ReadString();
	std::ifstream SelectedWorldFile;
	
	SelectedWorldFile.open(WorldFile, std::fstream::in);

	if (!SelectedWorldFile.good()) {
		throw std::invalid_argument("Error reading file.");
	}

	MainGameInstance = std::make_unique<GameInstance>(SelectedWorldFile);
}

void GameApp::ContinueGame() {

}

void GameApp::SaveGame() {

	RenderManager::Show("What do you wanna call you save file? ");
	std::string SaveFile = InputManager::ReadString();

	if (std::ifstream(SaveFile).good())
	{
		RenderManager::Show("File already exists, sure you wanna overwrite it?");
		RenderManager::Show("1) Yes   2) No");

		if (InputManager::Read() != 1)
			return;
	}

	std::ofstream SelectedSaveFile;
	SelectedSaveFile.open(SaveFile, std::ofstream::out |std::fstream::trunc);

	if (!SelectedSaveFile.good()) {
		throw std::invalid_argument("Error saving game.");
	}
	
	DataManager::SavePlayer(MainGameInstance->GetSaveData(), SelectedSaveFile);
	SelectedSaveFile.close();

	RenderManager::Show("Game saved to " + SaveFile);

}

void GameApp::LoadGame() {
	RenderManager::Show("Name of the World file?");
	std::string WorldFile = InputManager::ReadString();

	RenderManager::Show("Name of the Save file?");
	std::string SaveFile = InputManager::ReadString();


	std::ifstream SelectedWorldFile;
	std::ifstream SelectedLoadFile;
	SelectedWorldFile.open(WorldFile, std::fstream::in);
	SelectedLoadFile.open(SaveFile, std::fstream::in);

	if (!SelectedWorldFile.good() || !SelectedLoadFile.good()) {
		throw std::invalid_argument("Error reading file.");
	}

	RenderManager::Show("Game loaded. Have fun!\n");

	MainGameInstance = std::make_unique<GameInstance>(SelectedWorldFile, SelectedLoadFile);
}