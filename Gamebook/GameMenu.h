#pragma once
#include "Constants.h"
#include "RenderManager.h"
#include "InputManager.h"
#include <memory>

typedef int MenuSelection;

//! \brief Class offering basic user menu to navigate through game
class GameMenu
{
public:	
	//! \brief Opens menu and gets user input from selecting one of the options
	//! \return Menu option selected
	MenuSelection GetMenuChoice() const;

private:

	//! \brief Shows menu on screen
	void ShowMenu() const;

	//! \brief Takes user input
	//! \return Menu option selected
	MenuSelection ReadSelection() const;

};

