#pragma once

#include "Ability.h"

class Backstab : public Ability
{
public:
	Backstab();

	CombatResult Use(Character* other) override;
};