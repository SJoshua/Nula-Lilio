/* Project Nula Lilio
 * Author: SJoshua & Lethur
 * - For the summer 2019.
 */

#include <iostream>
#include <SDL.h>
#include "basic/Audio.h"
#include "basic/Engine.h"
#include "basic/Resource_Manager.h"
#include "basic/Scene_Manager.h"

ResourceManager resources;
SceneManager scenes;
Audio audio;
Engine game;

int main(int argc, char *args[]) {	
	game.init();
	game.run();
	game.close();
	return 0;
}
