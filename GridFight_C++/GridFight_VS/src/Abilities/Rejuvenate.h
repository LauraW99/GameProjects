#pragma once

#include "Ability.h"

class Rejuvenate : public Ability
{
public:
	Rejuvenate();

	virtual CombatResult Use(Character* other) override;
};