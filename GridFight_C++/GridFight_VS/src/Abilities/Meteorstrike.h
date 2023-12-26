#pragma once

#include "Ability.h"

class Meteorstrike : public Ability
{
public:
	Meteorstrike();

	CombatResult Use(Character* other) override;
};