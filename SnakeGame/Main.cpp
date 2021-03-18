#include "Scenemanager.h"




int	main()
{
	srand((time(0u)));
	
	Scenemanager myScenes;

	while (!myScenes.GetGame()->GetWindow()->isDone())
	{
		myScenes.Update();
	}
}
