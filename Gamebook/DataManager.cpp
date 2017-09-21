#include "DataManager.h"

using json = nlohmann::json;

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
	RenderManager::Show("Health: " + std::to_string(Health) + " | Damage : " + std::to_string(Damage) + " | Speed: " + std::to_string(Speed) + " | MissChance: " + std::to_string(MissChance) + "%" );
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
	SpecialAbility Special;
	OInventory Inventory;

	json SaveData;
	SelectedSaveFile >> SaveData;
	
	if (SaveData.find("specialAbility").value() == "Frostbolt")
		Special = SpecialAbility::Frostbolt;
	else if (SaveData.find("specialAbility").value() == "Crit")
		Special = SpecialAbility::Crit;
	else if (SaveData.find("specialAbility").value() == "Fireball")
		Special = SpecialAbility::Fireball;

	Position = SaveData.find("locationID").value();

	Health = SaveData["stats"].find("health").value();
	Damage = SaveData["stats"].find("damage").value();
	Speed = SaveData["stats"].find("speed").value();
	MissChance = SaveData["stats"].find("missChance").value();
		
	if ( ! SaveData["items"].empty() ) {
		for (json::iterator it = SaveData["items"].begin(); it != SaveData["items"].end(); ++it) {
			auto Item = ReadItem((*it));
			if ((*it).find("equipped").value() == false)
				Inventory.TakeItem(Item); 
			else
				Inventory.EquipItem(Item);
		}
	}

	return std::make_shared<APlayer>(Health, Damage, Speed, MissChance, Inventory, Position, Special);
}

std::string DataManager::GetWorldName(json & WorldData)
{
	return WorldData["worldName"].get<std::string>();
}

std::string DataManager::GetWorldDescription(json & WorldData)
{
	return WorldData["worldDescription"].get<std::string>();
}

std::map<LocationID, Location> DataManager::GetLocations(json & WorldData)
{
	std::map<LocationID, Location>  LocationList;

	for (json::iterator it = WorldData["locations"].begin(); it != WorldData["locations"].end(); ++it) {
		int location = (*it).find("ID").value();
		LocationList.insert(std::pair<LocationID, Location>((LocationID)location, ReadLocation(*it)) );
	}
	
	return LocationList;
}

OItem DataManager::ReadItem(json & ItemData) {
	std::string ItemName;
	SItemStats ItemStats;
	int Category;
	
	ItemStats.HealthBonus = ItemData["stats"]["health"];
	ItemStats.DamageBonus = ItemData["stats"]["damage"];
	ItemStats.SpeedBonus = ItemData["stats"]["speed"];
	ItemStats.AccuracyBonus = ItemData["stats"]["accuracy"];
	Category = ItemData["category"];
	ItemName = ItemData["name"].get<std::string>();
	
	return OItem (ItemName, ItemStats, Category);
}


Location DataManager::ReadLocation(json & LocationData) {

	std::string LocationText;
	std::vector<std::pair<LocationID, std::string >> ConnectedLocations;
	std::vector<std::shared_ptr<OObject>> Interactions;
	
	LocationText = LocationData["description"].get<std::string>();

	for (json::iterator it = LocationData["connections"].begin(); it != LocationData["connections"].end(); ++it) {
		int ConnectionAddress = (*it).find("destinationID").value();
		std::string ConnectionText = (*it)["description"].get<std::string>();
		ConnectedLocations.push_back(std::pair<LocationID, std::string>(ConnectionAddress, ConnectionText));
	}

	for (json::iterator it = LocationData["interactions"].begin(); it != LocationData["interactions"].end(); ++it) {

		if ((*it)["type"] == "enemy") 
			Interactions.push_back(LoadEnemy(*it));
	}



	Location tmp(LocationText, ConnectedLocations, Interactions);
	return tmp;
}

std::shared_ptr<OObject> DataManager::LoadEnemy(json & EnemyData) {

	std::string Name = EnemyData["name"];
	
	int Health = EnemyData["stats"]["health"];
	int Speed = EnemyData["stats"]["speed"];
	int Damage = EnemyData["stats"]["damage"];
	int MissChance = EnemyData["stats"]["missChance"];


	if ( ! EnemyData["items"].empty()) {
		// TODO: Fix temporary
		OLootbag TmpLootbag;

		for (json::iterator it = EnemyData["items"].begin(); it != EnemyData["items"].end(); ++it) {
			TmpLootbag.Insert(ReadItem(*it));
		}
		auto SharedLootbag = std::make_shared<OLootbag>(TmpLootbag);
		return std::make_shared<AEnemy>(Name, Health, Speed, Damage, MissChance, SharedLootbag);
	}
	else 
		return std::make_shared<AEnemy>(Name, Health, Speed, Damage, MissChance);
}

void DataManager::SavePlayer(std::shared_ptr<APlayer> Player, std::ofstream & SelectedSaveFile){

	json PlayerSave;

	if (Player->GetSpecial() == SpecialAbility::Frostbolt)
		PlayerSave["specialAbility"] = "Frostbolt";
	else if (Player->GetSpecial() == SpecialAbility::Crit)
		PlayerSave["specialAbility"] = "Crit";
	else if (Player->GetSpecial() == SpecialAbility::Fireball)
		PlayerSave["specialAbility"] = "Fireball";

	PlayerSave["locationID"] = Player->Locate();
	PlayerSave["stats"]["damage"] = Player->GetStats().Damage;
	PlayerSave["stats"]["health"] = Player->GetStats().Health;
	PlayerSave["stats"]["missChance"] = Player->GetStats().Accuracy;
	PlayerSave["stats"]["speed"] = Player->GetStats().Speed;

	PlayerSave["items"] = Player->GetInventory().toJSON();

	SelectedSaveFile << PlayerSave;
}
