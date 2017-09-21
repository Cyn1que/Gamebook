#pragma once

#include "Object.h"
#include <string>


//! \brief Purely abstract class representing general concept of Actor within game world (players, NPCs, monsters, traps)
class AActor : public OObject
{
protected:
	std::string Name; ///< Name of the Actor

};

