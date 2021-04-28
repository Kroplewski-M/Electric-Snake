#include "Scenemanager.h"



int	WinMain()
{
	//RANDOM SEED
	srand((time(0u)));
	
	//GAME LOOP
	Scenemanager myScenes;

	while (!myScenes.GetGame()->GetWindow()->isDone())
	{
		myScenes.Update();
	}
}
