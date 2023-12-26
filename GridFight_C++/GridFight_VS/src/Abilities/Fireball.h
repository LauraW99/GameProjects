#pragma once

#include "Ability.h"

class Fireball : public Ability
{
public:
	Fireball();

	CombatResult Use(Character* other) override;
};