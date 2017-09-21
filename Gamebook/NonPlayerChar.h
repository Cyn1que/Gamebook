#pragma once

#include <iostream>
#include <map>
#include <memory>
#include <string>

#include "Lootbag.h"
#include "Character.h"
#include "Player.h"
#include "Managers.h"

//! \brief NPC class that serves as basis point for actors such as enemy monsters, vendors or just regular dialogue interactors
class ANonPlayerChar : public ACharacter
{
public:
	//! \brief Constructs basic NPC object
	ANonPlayerChar();

	//! \brief Constructs NPC object
	//! \param SName String with NPC's name
	//! \param SNPCText String with NPC's descriptory text
	ANonPlayerChar(std::string SName, std::string SNPCText);

	//! \brief Interact with Object or any object that inherits from it
	//! \param Object Reference to object being intracted with 
	virtual void InteractWith(OObject & Object);
	//! \brief Interact with Player (lead a conversation with him)
	//! \param Player Reference to player being intracted with 
	virtual void InteractWith(APlayer & Player);

protected:
	std::shared_ptr<OLootbag> Inv; ///< Pointer to NPC's Lootbag object

private:	
	std::string NPCText; ///< String with NPC's description
	//! \brief Begins dialogue with the NPC
	void Dialogue();
	//std::map <int, std::string> Dialogues;
};

