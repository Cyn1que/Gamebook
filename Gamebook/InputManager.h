#pragma once
#include <iostream>
#include <string>

//! \brief Utility class for taking input from the user
class InputManager
{
public:
	//! \brief Reads integer or one of key phrases from standard input
	static int Read();
	//! \brief Reads one line of string from standard input
	static std::string ReadString();

};

