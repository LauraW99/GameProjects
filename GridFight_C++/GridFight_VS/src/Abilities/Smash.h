#pragma once

#include "Ability.h"

class Smash : public Ability
{
public:
	Smash();

	CombatResult Use(Character* other) override;
};