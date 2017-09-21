#include "NonPlayerChar.h"


ANonPlayerChar::ANonPlayerChar()
{
}

ANonPlayerChar::ANonPlayerChar(std::string SName, std::string SNPCText) {
	Name = SName;
	NPCText = SNPCText;
}

void ANonPlayerChar::InteractWith(APlayer & herp)
{
	RenderManager::Show(NPCText);
	Dialogue();
}

void ANonPlayerChar::Dialogue() {
	
}

void ANonPlayerChar::InteractWith(OObject & herp)
{
	RenderManager::Show("NPC interacting with OObject");
	herp.InteractWith(*this);
}
