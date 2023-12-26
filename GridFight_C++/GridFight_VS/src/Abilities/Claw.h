#pragma once

#include "Ability.h"

class Claw : public Ability
{
public:
	Claw();

	CombatResult Use(Character* other) override;
};