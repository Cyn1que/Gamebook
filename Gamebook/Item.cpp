#include "Item.h"

OItem::OItem() {
	Name = "Empty";

	ItemStats.HealthBonus = 0;
	ItemStats.DamageBonus = 0;
	ItemStats.SpeedBonus = 0;
	ItemStats.AccuracyBonus = 0;

}

OItem::OItem(std::string SName, SItemStats IItemStats, int ICategoryNumber) :
	ItemStats(IItemStats), Name(SName), CategoryNumber(ICategoryNumber)
{}


const std::string OItem::ItemDetails() const {
	return std::string ("Damage: +" + std::to_string(ItemStats.DamageBonus) + " | Health: +" + std::to_string(ItemStats.HealthBonus) +
		" | Speed: +" + std::to_string(ItemStats.SpeedBonus) + " | Accuracy: +" + std::to_string(ItemStats.AccuracyBonus));
	
}


const std::string OItem::ItemSaveDetails() const {
	return std::string(Name + "\n" + std::to_string(ItemStats.DamageBonus) + " " + std::to_string(ItemStats.HealthBonus) + " " + std::to_string(ItemStats.SpeedBonus) + " " + std::to_string(ItemStats.AccuracyBonus) + " " + std::to_string(CategoryNumber) + "\n");
}

const std::string & OItem::GetName() const
{
	return Name;
}

const int OItem::GetCat() const
{
	return CategoryNumber;
}

const SItemStats & OItem::GetItemStats() const
{
	return ItemStats;
}

json OItem::toJSON(bool isEquipped) const {
	json Item;
	Item["category"] = CategoryNumber;
	Item["equipped"] = isEquipped;
	Item["name"] = Name;
	Item["stats"]["accuracy"] = ItemStats.AccuracyBonus;
	Item["stats"]["damage"] = ItemStats.DamageBonus;
	Item["stats"]["health"] = ItemStats.HealthBonus;
	Item["stats"]["speed"] = ItemStats.SpeedBonus;

	return Item;
}