#pragma once

#include <vector>
#include "Cell.h"
#include "Int2.h"

struct MoveResult
{
	bool success;
	int2 newPosition;
	bool moved;
	Character* encounteredChar;
	std::string message;

	static MoveResult Error(const std::string& _message)
	{
		return { false, int2(-1,-1), false, nullptr, _message };
	}
};

class Grid
{
public:
	static Grid* Instance;

	Grid(unsigned int width, unsigned int height);

	void InitializeCells();
	bool GetValueAtIndex(unsigned int index) const;
	bool GetValueAtLocation(int2 location) const;
	void SetValueAtIndex(unsigned int index, bool value);
	void SetValueAtLocation(int2 location, bool value);
	Cell& GetCellAtIndex(unsigned int index);
	Cell& GetCellAtLocation(int2 location);
	unsigned int GetIndexFromLocation(int2 location) const;
	int2 GetLocationFromIndex(unsigned int index);
	unsigned int GetWidth() const;
	unsigned int GetHeight() const;
	bool IndexInBounds(unsigned int index) const;
	bool LocationInBounds(int2 location) const;
	void Print();

private:
	unsigned int m_Width;
	unsigned int m_Height;

	std::vector<Cell> m_Values;
};