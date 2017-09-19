#include "Demo.hpp"
#include <dingus/app/DingusSystem.hpp>

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR lpCmdLine, INT)
{
	CDemo* demo = new CDemo();
	CDingusSystem* system = new CDingusSystem(*demo);
	if (SUCCEEDED(system->create(hInstance)))
	{
		system->run();
	}
	delete demo;
	delete system;
}