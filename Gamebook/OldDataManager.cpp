#include "DataManager.h"

std::shared_ptr<APlayer> DataManager::GetPlayerCreationDetails() {

	SpecialAbility Special;
	int tmp, Health = 25, Damage = 8, Speed = 7, MissChance = 15;

	RenderManager::Show("Create your character\n");
	RenderManager::Show("Select your special ability:");
	RenderManager::Show("1) Frostbolt - damage enemy for 70% of your damage and freeze him for one turn.");
	RenderManager::Show("2) Crit - your next two attacks will deal extra 60% damage.");
	RenderManager::Show("3) Fireball - hit the enemy for 200% of your damage.");

	do {
		switch (tmp = InputManager::Read()) {
		case 1:
			Special = SpecialAbility::Frostbolt;
			break;
		case 2:
			Special = SpecialAbility::Crit;
			break;
		case 3:
			Special = SpecialAbility::Fireball;
			break;
		default:
			RenderManager::WrongChoice();
		}
	} while (tmp < 1 || tmp > 3);

	RenderManager::Show("\nYour basic stats are: \n");
	RenderManager::Show("Health: " + std::to_string(Health) + " | Damage : " + std::to_string(Damage) + " | Speed: " + std::to_string(Speed) + " | MissChance: " + std::to_string(MissChance) + "%");
	RenderManager::Show("\n You can increase your Health at expense of your Speed, same with Damage and Miss Chance.");

	RenderManager::Show("1) Increase Health by 5 and reduce speed by 2.");
	RenderManager::Show("2) Increase Damage by 3 and increase MissChance by 10%.");

	do {
		switch (tmp = InputManager::Read()) {
		case 1:
			Health += 5;
			Speed -= 2;
			break;
		case 2:
			Damage += 5;
			MissChance += 10;
			break;
		default:
			RenderManager::WrongChoice();
		}
	} while (tmp < 1 || tmp > 2);
	return std::make_shared<APlayer>(Health, Damage, Speed, MissChance, 1, Special);
}

std::shared_ptr<APlayer> DataManager::LoadPlayer(std::ifstream & SelectedSaveFile) {

	int Position, Health, Speed, Damage, MissChance;
	int ItemAmount, SpecialDec;
	SpecialAbility Special;
	OInventory Inventory;

	std::string line;
	std::getline(SelectedSaveFile, line);
	std::istringstream iss(line);
	iss >> Position >> SpecialDec;

	if (SpecialDec == 1)
		Special = SpecialAbility::Frostbolt;
	else if (SpecialDec == 1)
		Special = SpecialAbility::Crit;
	else if (SpecialDec == 1)
		Special = SpecialAbility::Fireball;

	std::getline(SelectedSaveFile, line);
	std::istringstream iss2(line);
	iss2 >> Health >> Damage >> Speed >> MissChance >> ItemAmount;

	if (ItemAmount > 0) {

		for (int i = 0; i < ItemAmount; i++) {
			auto Item = ReadItem(SelectedSaveFile);
			std::getline(SelectedSaveFile, line);
			if (line.compare("unequipped") == 0)
				Inventory.TakeItem(Item);
			else
				Inventory.EquipItem(Item);
		}
	}

	return std::make_shared<APlayer>(Health, Damage, Speed, MissChance, Inventory, Position, Special);
}

std::string DataManager::GetWorldName(std::ifstream & SelectedWorldFile)
{
	SelectedWorldFile.seekg(0);

	std::string line;
	std::getline(SelectedWorldFile, line);
	return line;

}

std::string DataManager::GetWorldDescription(std::ifstream & SelectedWorldFile)
{
	SelectedWorldFile.seekg(0);

	int NumberOfLines = 0;

	std::string line, result;
	std::getline(SelectedWorldFile, line);
	std::getline(SelectedWorldFile, line);

	std::istringstream iss(line);
	iss >> NumberOfLines;

	for (int i = 0; i < NumberOfLines; i++) {
		std::getline(SelectedWorldFile, line);
		result += line + "\n";
	}

	return result;
}

std::map<LocationID, Location> DataManager::GetLocations(std::ifstream & SelectedWorldFile)
{
	std::map<LocationID, Location>  LocationList;

	int NumberOfLocations;

	std::string line;
	std::getline(SelectedWorldFile, line);

	std::istringstream iss(line);
	iss >> NumberOfLocations;

	for (int i = 1; i <= NumberOfLocations; i++) {
		LocationList.insert(std::pair<LocationID, Location>((LocationID)i, ReadLocation(SelectedWorldFile)));
	}

	return LocationList;

}

OItem DataManager::ReadItem(std::ifstream & SelectedWorldFile) {
	std::string ItemName, line;
	SItemStats ItemStats;
	int Category;

	std::getline(SelectedWorldFile, ItemName);
	std::getline(SelectedWorldFile, line);
	std::istringstream iss(line);
	iss >> ItemStats.HealthBonus >> ItemStats.DamageBonus >> ItemStats.SpeedBonus >> ItemStats.AccuracyBonus >> Category;

	return OItem(ItemName, ItemStats, Category);
}

Location DataManager::ReadLocation(std::ifstream & SelectedWorldFile) {

	int NumberOfConnections = 0, NumberOfInteractions = 0, NumberOfLines = 0;
	std::string LocationText, line;


	std::getline(SelectedWorldFile, line);
	std::istringstream iss(line);
	iss >> NumberOfLines;

	for (int i = 0; i < NumberOfLines; i++) {
		std::getline(SelectedWorldFile, line);
		LocationText += line + "\n";
	}

	std::getline(SelectedWorldFile, line);
	std::istringstream iss2(line);
	iss2 >> NumberOfConnections >> NumberOfInteractions;

	std::vector<std::pair<LocationID, std::string >> ConnectedLocations;
	std::vector<std::shared_ptr<OObject>> Interactions;

	for (int i = 0; i < NumberOfConnections; i++) {
		int ConnectionAddress;
		std::string ConnectionText, line;

		std::getline(SelectedWorldFile, line);
		std::istringstream helpstream(line);
		helpstream >> ConnectionAddress;

		std::getline(SelectedWorldFile, ConnectionText);

		ConnectedLocations.push_back(std::pair<LocationID, std::string>(ConnectionAddress, ConnectionText));
	}

	for (int i = 0; i < NumberOfInteractions; i++) {
		std::string line;
		std::getline(SelectedWorldFile, line);
		if (line.compare("Enemy") == 0)
			Interactions.push_back(LoadEnemy(SelectedWorldFile));
	}



	Location tmp(LocationText, ConnectedLocations, Interactions);
	return tmp;
}

std::shared_ptr<OObject> DataManager::LoadEnemy(std::ifstream & SelectedWorldFile) {

	std::string Name, line;

	int Health;
	int Speed;
	int Damage;
	int MissChance;
	int ItemAmount;

	std::getline(SelectedWorldFile, Name);
	std::getline(SelectedWorldFile, line);
	std::istringstream helpstream(line);
	helpstream >> Health >> Speed >> Damage >> MissChance;

	std::getline(SelectedWorldFile, line);
	std::istringstream helpstream2(line);
	helpstream2 >> ItemAmount;

	if (ItemAmount > 0) {
		OLootbag TmpLootbag;

		for (int i = 0; i < ItemAmount; i++) {
			TmpLootbag.Insert(ReadItem(SelectedWorldFile));
		}
		auto SharedLootbag = std::make_shared<OLootbag>(TmpLootbag);
		return std::make_shared<AEnemy>(Name, Health, Speed, Damage, MissChance, SharedLootbag);
	}
	else
		return std::make_shared<AEnemy>(Name, Health, Speed, Damage, MissChance);
}

void DataManager::SavePlayer(std::shared_ptr<APlayer> Player, std::ofstream & SelectedSaveFile) {

	int SpecialDec;

	if (Player->GetSpecial() == SpecialAbility::Frostbolt)
		SpecialDec = 1;
	else if (Player->GetSpecial() == SpecialAbility::Crit)
		SpecialDec = 2;
	else if (Player->GetSpecial() == SpecialAbility::Fireball)
		SpecialDec = 3;

	std::string tmp(std::to_string(Player->Locate()) + " " + std::to_string(SpecialDec) + "\n" + std::to_string(Player->GetStats().Health) + " "
		+ std::to_string(Player->GetStats().Damage) + " " + std::to_string(Player->GetStats().Speed) + " " + std::to_string(Player->GetStats().Accuracy) + " " + std::to_string(Player->InventorySize())
		+ "\n" + Player->CreateInvSaveList());
	SelectedSaveFile << tmp;
}
