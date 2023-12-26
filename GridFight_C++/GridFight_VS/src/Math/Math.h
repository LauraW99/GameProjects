#pragma once

template<typename T>
T RemapValueRange(T Value, T Low1, T High1, T Low2, T High2)
{
	return static_cast<T>(Low2 + (Value - Low1) * static_cast<float>(High2 - Low2) / static_cast<float>(High1 - Low1));
}