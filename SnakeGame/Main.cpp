#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Scenemanager.h"
#include "FileHandling.h"

int	main()
{
	srand((time(0u)));
	
	Scenemanager myScenes;

	while (!myScenes.GetGame()->GetWindow()->isDone())
	{
		myScenes.Update();
	}




	return 0;
}
