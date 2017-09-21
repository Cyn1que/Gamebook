#include "InputManager.h"

#include <cctype>

int InputManager::Read()
{
	std::string buffer;
	std::cout << ">> ";
	std::getline(std::cin, buffer);
	
	if (buffer.length() == 1)
		return buffer[0] - '0';
	else if (buffer.compare("inv") == 0 || buffer.compare("Inv") == 0)
		return -2;
	else if (buffer.compare("menu") == 0 || buffer.compare("Menu") == 0)
		return -3;
	else
		return -1;	
}

std::string InputManager::ReadString()
{
	std::string line;
	std::getline(std::cin, line);
	return line;
}
