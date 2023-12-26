#pragma once

#include "Ability.h"

class Rumble : public Ability
{
public:
	Rumble();

	CombatResult Use(Character* other) override;
};