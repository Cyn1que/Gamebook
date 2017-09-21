#include "GameMenu.h"

MenuSelection GameMenu::GetMenuChoice() const {
	ShowMenu();
	return ReadSelection();
}

void GameMenu::ShowMenu() const {
	RenderManager::Show("1 New game");
	RenderManager::Show("2 Continue");
	RenderManager::Show("3 Save");
	RenderManager::Show("4 Load");
	RenderManager::Show("5 Quit");
}

MenuSelection GameMenu::ReadSelection() const {

	return InputManager::Read();
}