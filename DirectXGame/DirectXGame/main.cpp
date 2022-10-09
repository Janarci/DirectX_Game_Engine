#include "AppWindow.h"



int main()
{
	AppWindow app;
	AppWindow app2;
	if (app.init())
	{
		while (app.isRun())
		{
			app.broadcast();
		}
	}



	return 0;
}
