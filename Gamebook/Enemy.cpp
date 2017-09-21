#include "Enemy.h"


AEnemy::AEnemy(std::string SName, int IHealth, int IDamage, int ISpeed, int IMissChance) {
	Name = SName;

	Health = IHealth;
	Damage = IDamage;
	Speed = ISpeed;
	MissChance = IMissChance;

	PlayerSnapshot.vulnerable = false;
	PlayerSnapshot.SpecialUsed = false;
	PlayerSnapshot.Shield = 0;
	PlayerSnapshot.Frozen = false;
	PlayerSnapshot.CritCounter = 0;

	Inv = nullptr;
}

AEnemy::AEnemy(std::string SName, int IHealth, int IDamage, int ISpeed, int IMissChance, std::shared_ptr<OLootbag> LootBag)
	: AEnemy (SName, IHealth, IDamage, ISpeed, IMissChance) {
		
	Inv = LootBag;
}

void AEnemy::InteractWith(OObject & herp) {

}

void AEnemy::InteractWith(APlayer & Player) {
	RenderManager::Show("You've encountered an enemy: " + Name + ", total HP: " + std::to_string(Health) );
	RenderManager::Show("");

	// Get player data
	PlayerSnapshot.MissChance = Player.GetPlayerStats().Accuracy;
	PlayerSnapshot.Damage = Player.GetPlayerStats().Damage;
	PlayerSnapshot.Health = Player.GetPlayerStats().Health;
	PlayerSnapshot.Speed = Player.GetPlayerStats().Speed;
	PlayerSnapshot.MaxHealth = PlayerSnapshot.Health;
	PlayerSnapshot.Special = Player.GetSpecial();

	// Fight until one of the two combatants is defeated
	while (PlayerSnapshot.Health > 0 && this->Health > 0) {
		Fight(PlayerSnapshot);
	}

	if (PlayerSnapshot.Health > 0) {
		RenderManager::Show("You are victorious!");
		RenderManager::Show("");

		if (Inv != nullptr)
			Player.Interact(Inv); // Loot enemy
	}
	else {
		RenderManager::Show("You've died. :(");
		RenderManager::Show("");
		Player.Death();
	}

}

void AEnemy::EnemyTurn(SPlayerSnapshot & Player) {

	// Check if you're not frozen and can attack
	if (Player.Frozen) {
		RenderManager::Show("Enemy is frozen this turn.");
		Player.Frozen = false;
		return;
	}

	// Calculate damage Player takes
	int PlayerDamageTaken = (int)(this->Damage * (1 + (0.3 * PlayerSnapshot.vulnerable)));
	int DamageBlocked = 0;
	
	if (Player.Shield <= PlayerDamageTaken) {
		DamageBlocked = Player.Shield;
		PlayerDamageTaken -= Player.Shield;
		Player.Shield = 0;
	}
	else {
		DamageBlocked = PlayerDamageTaken;
		Player.Shield -= PlayerDamageTaken;
		PlayerDamageTaken = 0;
	}

	Player.Health -= PlayerDamageTaken;

	// Inform player about your turn
	RenderManager::Show(Name + " attacks you for " + std::to_string(Damage) + ", your remaining HP: " + std::to_string(Player.Health) + ", remaining shield: " + std::to_string(Player.Shield));
	if (Player.vulnerable)
		RenderManager::Show("   (Vulnerable bonus)");
	if (DamageBlocked > 0)
		RenderManager::Show("   (Blocked: " + std::to_string(DamageBlocked) + ")");

	RenderManager::Show("");
}

void AEnemy::PlayerTurn(SPlayerSnapshot & Player) {

	Player.vulnerable = false;

	// Ask player about how to proceed
	RenderManager::Show("What do you wish to do?");
	RenderManager::Show("1) Quick attack   2) Strong attack   3) Special   4) Defend");

	int buffer;
	while ( (buffer = InputManager::Read()) != 0) {
		if (buffer < 1 || buffer > 4) {
			RenderManager::WrongChoice();
			continue;
		}
		if (buffer == 1) { // Quick attack
			if (Player.CritCounter > 0) {
				Health -= (int)(Player.Damage * 1.6);
				Player.CritCounter--;
				RenderManager::Show("You critically strike " + Name + " for " + std::to_string((int)(Player.Damage * 1.6)) + " damage. (" + std::to_string(Health) + " HP left)");
			}
			else {
				Health -= Player.Damage;
				RenderManager::Show("You hit " + Name + " for " + std::to_string(Player.Damage) + " damage. (" + std::to_string(Health) + " HP left)");
			}
		}
		else if (buffer == 2) { // Strong attack
			Player.vulnerable = true;
			Health -= (int)(Player.Damage * 1.4);
			RenderManager::Show("You hit " + Name + " for " + std::to_string((int)(Player.Damage * 1.4)) + " damage. (" + std::to_string(Health) + " HP left). You will be vulnerable for next enemy attack.");
			
		}
		else if (buffer == 3) { // Special ability
			if (Player.SpecialUsed) {
				RenderManager::Show("Special ability depleted and cannot be used again in this fight.");
				continue;
			}
			if (Player.Special == SpecialAbility::Frostbolt) {
				Health -= (int)(Player.Damage * 0.7);
				RenderManager::Show("Magical frostbolt crushes " + Name + " and hits it for " + std::to_string((int)(Player.Damage * 0.7)) + " damage. (" + std::to_string(Health) + " HP left).");
				Player.Frozen = true;
			}
			else if (Player.Special == SpecialAbility::Crit) {
				RenderManager::Show("You focus inward, causing your next two quick attacks to critically strike for 60% extra damage.");
				Player.CritCounter = 2;
			}
			else if (Player.Special == SpecialAbility::Fireball) {
				Health -= (int)(Player.Damage * 2);
				RenderManager::Show("You conjure a massive fireball and hit " + Name + " with it for " + std::to_string((int)(Player.Damage * 2)) + " damage. (" + std::to_string(Health) + " HP left).");
			}
			Player.SpecialUsed = true;
		}

		else if (buffer == 4) { // Defense
			Player.Shield = (int)(Player.MaxHealth * 0.3);
			RenderManager::Show("You will block next " + std::to_string(Player.Shield) + " damage.");
		}

		break;

	}
}


void AEnemy::Fight(SPlayerSnapshot & Player) {
	if (this->Speed > Player.Speed) {
		EnemyTurn(Player);
		if (Player.Health <= 0)
			return;
		PlayerTurn(Player);
	}
	else {
		PlayerTurn(Player);
		if (this->Health <= 0)
			return;
		EnemyTurn(Player);
	}
}