#include "RenderManager.h"


void RenderManager::WrongChoice() {
	Show("This isn't a valid location option, pick again please.");
}

void RenderManager::Show(const std::string & Text) {
	std::cout << Text << std::endl;
}