#ifndef GUI_H
#define GUI_H

#include <string>
#include <vector>
#include <map>
//GUI definitions
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

//User-defined tools
#include "Texture.h"
#include "Object.h"
//Comment for push

class Engine;
class GUI
{

public:
	const static Vector2D columnRowDimensions;
	const static Vector2D numColumnsRows;
	const static Vector2D screenDimensions;
	
	GUI();
	~GUI();
	int observeEvent();
	bool quitGame();
	Object::Command getCommand();
	void displayGameState(Engine* engine);

	Vector2D getDimensions(const Object* object) const;	

private:

	//
	// PRIVATE METHODS
	//
	void initGUI();
	void loadMedia();
	void cleanUp();

	
	//
	//PRIVATE MEMBERS
	//
	Object::Command* command{ nullptr };
	bool quit;

	//Window(s) to display graphics
	SDL_Window* window{ nullptr };

	//Hardware accelerated renderer
	SDL_Renderer* renderer{ nullptr };

	//The texture and clipping that will be used for the objects
	std::map<Object::Type, Texture*> objectTextures;
	std::vector<SDL_Rect*> playerClips;
	std::vector<SDL_Rect*> enemyClips;
	
	//The font used on the screen.
	TTF_Font* guiFont{ nullptr };

	//The event structure that will be used
	SDL_Event* event{ nullptr };

};

#endif
