/*
* Author:	Sean Orme (based on the work of Dr. Keith Bush)
*			UALR
*
* Date:		September 23, 2019
*
* File:		level.3.quest.cpp
*/

#include <cstdlib> 
#include <ctime> 
#include <string>
#include <iostream>
#include <vector>
#include <tuple>
#include <memory>
#include "GUI.h"
#include "Timer.h"

#include "engine.h"
#include "Object.h"
#include "Player.h"
#include "Block.h"
#include "Enemy.h"

using namespace std;

int main(int argc, char* argv[]) {
	//Construct GUI
	std::unique_ptr<GUI> gui{ std::make_unique<GUI>() };

	std::unique_ptr<Engine> engine{ std::make_unique<Engine>(
		gui,
		"./Assets/data/background.txt",
		"./Assets/data/animation.txt",
		"./Assets/data/EnemyAnimations.txt") };

	//test code for rule of 5.
	/*
	std::unique_ptr<Engine> engine_copy{std::make_unique<Engine>(*engine)};
	std::unique_ptr<Engine> engine_move{ std::make_unique<Engine>(std::move(*engine_copy)) };

	Engine engine_op_copy = *engine_move;
	Engine engine_op_move = std::move(*engine_move);
	*/

	//Construct Timer
	Timer fps;

	//Initialize Termination Criteria
	bool quit = false;
	Object::Command command{ Object::Command::NA };

	//While the user hasn't quit
	while (quit == false)
	{
		//Start the frame timer
		fps.start();

		//GUI waits for mouse events
		if (gui->observeEvent())
		{
			//Receive Command From GUI
			command = gui->getCommand();

			//GUI transmits quit event
			if (gui->quitGame())
			{
				quit = true;
			}
		}

		//Task 3: Update Game state
		engine->changeGameState(command);

		//Render Game Data
		gui->displayGameState(engine.get());

		//Adjust Frame Rate
		if (fps.get_ticks() < fps.frameDelay)
		{
			SDL_Delay((Uint32)fps.frameDelay - (Uint32)fps.get_ticks());
		}
	}
	//Return
	return 0;

}