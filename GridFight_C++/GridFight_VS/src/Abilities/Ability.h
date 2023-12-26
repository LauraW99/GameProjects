#pragma once
#include <string>

#include "../Character.h"

enum class EAbilityType
{
	Smash,
	Howl,
	Claw,
	Rumble,
	Backstab,
	Fireball,
	MeteorStrike,
	Rejuvenate
};

struct CombatResult;
class Character;
class Ability
{
protected:
	Character* m_Owner;

	int m_Cooldown;
	int m_CurrentCooldown;

public:
	Ability(std::string name, int cooldown);
	
	std::string m_Name;

	virtual CombatResult Use(Character* other);
	bool CanCast();

	void SetOwner(Character* owner);

	int GetCooldown() const;
	int GetCurrentCooldown() const;
	void ReduceCooldown();
	void ResetCooldown();
};