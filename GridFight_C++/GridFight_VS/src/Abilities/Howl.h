#pragma once

#include "Ability.h"

class Howl : public Ability
{
public:
	Howl();

	CombatResult Use(Character* other) override;
};