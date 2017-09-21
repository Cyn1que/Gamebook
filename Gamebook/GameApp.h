
//Author: Ondrej Slejtr
//slejtond@fit.cvut.cz

#pragma once
#include "GameInstance.h"
#include "GameMenu.h"
#include "Constants.h"
#include "RenderManager.h"
#include "InputManager.h"

#include <stdexcept>
#include <memory>
#include <iostream>
#include <fstream>


//! \brief Class representing game application, handles transition between menu and gameplay and their communication.
class GameApp
{
public:

	//! \brief Constructor that initializes new game application and sets its state to show menu at first.
	GameApp();

	//! \brief Initializes game application activity.
	void Play();

private:
	std::unique_ptr<GameMenu> MainMenu;	
	std::unique_ptr<GameInstance> MainGameInstance;

	GameState CurrentGameState;

	//! \brief Stops application run and closes it down.
	void ExitApp();

	//! \brief Swaps application state between displaying Menu and Game itself
	void SwapGameState();
	
	//! \brief Takes user input from Menu to proceed accordingly (exit application or manipulate Game).
	//! \param User input given in menu
	void ProcessMenuChoice(MenuSelection MenuOpt);

	//! \brief Creates a new game from World file
	void NewGame();
	//! \brief Lets player proceed with already running game
	void ContinueGame();
	//! \brief Saves currently running game
	void SaveGame();
	//! \brief Loads game in-progress from World and Save file
	void LoadGame();

};

