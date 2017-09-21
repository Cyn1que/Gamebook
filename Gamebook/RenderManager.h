#pragma once

#include <string>
#include <iostream>
#include <iomanip>

//! \brief Utility class for showing ouput to the user
class RenderManager
{
public:
	//! \brief Writes warning for choosing invalid option into standard output
	static void WrongChoice();
	//! \brief Displays string into standard output
	static void Show(const std::string & Text);
};


