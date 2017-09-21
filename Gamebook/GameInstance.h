#pragma once
#include <memory>
#include <iostream>
#include <fstream>

#include "RenderManager.h"
#include "InputManager.h"
#include "World.h"

//! \brief Class describing instance of Gamebook's game
class GameInstance
{
public:
	//! \brief Creates World already in progress (loading game)
	//! \param SelectedWorldFile File stream with World File from which the World will be created.
	//! \param SelectedSaveFile File stream with Save File from which the state of World will be determined.
	GameInstance(std::ifstream & SelectedWorldFile, std::ifstream & SelectedSaveFile);

	//! \brief Creates fresh instance of World (new game)
	//! \param SelectedWorldFile File stream with World File from which the World will be created.
	GameInstance(std::ifstream & SelectedWorldFile);

	//! \brief Starts the World from last known state
	void Begin();
	//! \brief Checks validity of GameInstance
	//! \return Boolean value indicating whether GameInstance is valid or not
	bool IsValid();

	//! \brief Provides data required to save current GameInstance to Save file
	//! \return Pointer to datablock with information about player character
	std::shared_ptr<APlayer> GetSaveData() const;

private:
	std::shared_ptr<World> MainWorld; ///< Pointer to instance of World in which Game occurs
	bool valid;		///< Boolean signaling whether GameInstance is still valid/playable

	//! \brief Main game loop responsible for tracing game's end
	void GameLoop();

	GameInstance();  // Forbid creation of object without initialization
};

