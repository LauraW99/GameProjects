#include <iostream>
#include "src/Math/Int2.h"
#include "src/Math/Grid.h"
#include "src/Game.h"
#include "GameParameters.h"

int main()
{
	//EXAMPLE FOR EXERCISE 7

	GameParameters params;
	
	params.playerStart = int2(2, 2);
	params.gridWidth = 25;
	params.gridHeight = 25;
	params.enemyCount = 15;
	
	Game game = Game(params);
	game.Run();

	return 0;
}
