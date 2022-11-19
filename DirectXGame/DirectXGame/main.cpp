#include "AppWindow.h"



int main()
{
	AppWindow::initialize();
	AppWindow* runningApp = (AppWindow*)AppWindow::getInstance();
	runningApp->initializeEngine();
	runningApp->Start();

	while (runningApp->isRun())
	{
		runningApp->broadcast();
	}

	return 0;
}