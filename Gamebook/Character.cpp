#include "Character.h"

SPlayerStats ACharacter::GetStats() const {
	return SPlayerStats(Health, Damage, Speed, MissChance);
}
