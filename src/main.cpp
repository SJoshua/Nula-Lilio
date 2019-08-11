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

int main(int argc, char *args[]) {
	Engine game;
	game.init();
	game.run();
	game.close();
	return 0;
}
