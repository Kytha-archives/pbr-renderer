#pragma once
#include "Input.h"

extern Application* CreateApplication();

// ENTRY POINT
int main(int argc, char** argv)
{
	// Get client defined application object and start app loop
	auto app = CreateApplication();
	app->Run();
	delete app;
}

