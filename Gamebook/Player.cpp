#include "Player.h"

APlayer::APlayer(int IHealth, int IDamage, int ISpeed, int IMissChance, int IPosition, SpecialAbility ISpecialAbility){
	Health = IHealth;
	Damage = IDamage;
	Speed = ISpeed;
	MissChance = IMissChance;

	Alive = true;

	CurrentLocation = IPosition;
	Special = ISpecialAbility;
}

APlayer::APlayer(int IHealth, int IDamage, int ISpeed, int IMissChance, OInventory SInventory, int Position, SpecialAbility ISpecialAbility)
	: APlayer(IHealth, IDamage, ISpeed, IMissChance, Position, ISpecialAbility) {

	Inventory = SInventory;
}

ExplorationStatus APlayer::ExploreLocation(Location & Loc) {

	if (Loc.IsEmpty()) {
		int buffer;

		if (Loc.Deadend())
			return ExplorationStatus::Success;

		Loc.GetDirections();
		while ( (buffer = InputManager::Read()) != 0) {
			if (buffer == -2) {
				Inventory.Open();
				RenderManager::Show("");
				Loc.GetDirections();
			}
			else if (buffer == -3) {
				return ExplorationStatus::QuitInstance;
			}
			else if (buffer == -1) {
				RenderManager::WrongChoice();
				continue;
			}
			else {
				if (buffer < 1 || buffer > (signed)Loc.ConnectedAmount()) {
					RenderManager::WrongChoice();
					continue;
				}
				else {
					Move(Loc.GetConnectionID(buffer - 1));
					break;
				}
			}
		}
		
	}
	else {
		while (!Loc.IsEmpty()) {
			Interact(Loc.Interact());
			Loc.ClearInteraction();
		}
	}

	if (!Alive)
		return ExplorationStatus::Failure;

	return ExplorationStatus::InProgress;
}

void APlayer::Move(LocationID NewLocation) {
	CurrentLocation = NewLocation;
}

LocationID APlayer::Locate() const {
	return CurrentLocation;
}

void APlayer::Interact(std::shared_ptr<OObject> Object){
	Object->InteractWith(*this);
}
void APlayer::InteractWith(ANonPlayerChar & Player) {
	RenderManager::Show("Player interacting with NPC");
}
void APlayer::InteractWith(APlayer & Player) {
	// What happened here?
}

void APlayer::InteractWith(std::shared_ptr<OObject>) {

}

void APlayer::TakeItem(OItem Item) {
	Inventory.TakeItem(Item);
}
int APlayer::InventorySize() const{
	return Inventory.size();
}

SPlayerStats APlayer::GetPlayerStats() const
{
	Stat A = MissChance + Inventory.GetStats().AccuracyBonus;
	Stat D = Damage + Inventory.GetStats().DamageBonus;
	Stat H = Health + Inventory.GetStats().HealthBonus;
	Stat S = Speed + Inventory.GetStats().SpeedBonus;
	return SPlayerStats(H, D, S, A);
}

SpecialAbility APlayer::GetSpecial() const
{
	return Special;
}

std::string APlayer::CreateInvSaveList() const
{
	return Inventory.CreateSaveList();
}

const OInventory & APlayer::GetInventory() {
	return Inventory;
}

void APlayer::InteractWith(OObject & Object) {
	RenderManager::Show("Player interacting with Object");
}

void APlayer::Death() {
	Alive = false;
}
