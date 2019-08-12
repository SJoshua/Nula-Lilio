/* Project Nula Lilio
 * Au: SJoshua
 */

#include <iostream>
#include <SDL.h>
#include "Engine.h"
#include "Resource_Manager.h"
#include "Scene_Manager.h"

ResourceManager resources;
SceneManager scenes;
Engine game;

int main(int argc, char *args[]) {	
	game.init();
	game.run();
	game.close();
	return 0;
}
