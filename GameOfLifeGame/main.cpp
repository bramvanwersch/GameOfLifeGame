#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <BWengine/IMainGame.h>

#include "App.h"
#include "Constants.h"

int main(int argc, char* argv[])
{
	App app;
	app.run(DESIRED_FPS);
	return 0;
}