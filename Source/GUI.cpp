#include <iostream>
#include <fstream>
#include <string>

#include "GUI.h"
#include "Texture.h"
#include "Object.h"
#include "Player.h"
#include "Enemy.h"
#include "Block.h"
#include "engine.h"
#include "HealthBar.h"

using namespace std;

const Vector2D GUI::columnRowDimensions{ 50, 50 };
const Vector2D GUI::numColumnsRows{ 14,8 };
const Vector2D GUI::screenDimensions{ numColumnsRows.x * columnRowDimensions.x, numColumnsRows.y * columnRowDimensions.y };

GUI::GUI(){

	//Start-up the GUI!
	initGUI();

	//Load in all the images and clip (if necessary)
	loadMedia();

	//Exit criteria
	quit=false;

}

GUI::~GUI(){
	cleanUp();
}

int GUI::observeEvent(){
	return(SDL_PollEvent( event ));
}

Object::Command GUI::getCommand() {
	//Base command is "NA" for "Not Applicable"
	command = new Object::Command;
	*command = Object::Command::NA;

	//If a key was pressed
	if (event->type == SDL_KEYDOWN) {

		//Animate
		switch (event->key.keysym.sym)
		{
		case SDLK_SPACE: *command = Object::Command::attack; break;
		case SDLK_UP: *command = Object::Command::up; break;
		case SDLK_DOWN: *command = Object::Command::down; break;
		case SDLK_LEFT: *command = Object::Command::left; break;
		case SDLK_RIGHT: *command = Object::Command::right; break;
		case SDLK_LCTRL: *command = Object::Command::jump; break;
		default: *command = Object::Command::NA; break;
		}
	}

	return(*command);

}


bool GUI::quitGame(){
	return(event->type == SDL_QUIT );
}

void GUI::initGUI(){

	//Initialize all SDL subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {

		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		exit(1);
	}
	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		exit(1);
	}

	//Initialize SDL_ttf
	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		exit(1);
	}

	//Construct and check window construction
	window = SDL_CreateWindow("Contra Clone",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		screenDimensions.x, screenDimensions.y, SDL_WINDOW_SHOWN);

	if (window == nullptr) {

		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		exit(1);
	}

	//Construct and check renderer construction
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr) {

		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		exit(1);

	}
	event = new SDL_Event;
}

void GUI::loadMedia(){

	objectTextures[Object::Type::hpbar] = new Texture();
	objectTextures[Object::Type::hpbar]->load(renderer, "./Assets/Images/HealthSpriteSheet.png");

	hpClips.push_back(new SDL_Rect{ 0, 0, 300, 90 });//First Bar
	hpClips.push_back(new SDL_Rect{ 0, 85, 300, 80 });//Second Bar
	hpClips.push_back(new SDL_Rect{ 0, 168, 300, 90 }); //Third Bar
	hpClips.push_back(new SDL_Rect{ 0, 260, 300, 90 }); //Last Bar

	//Open Enemy Sprite Sheet Forward
	objectTextures[Object::Type::enemy] = new Texture();
	objectTextures[Object::Type::enemy]->load(renderer, "./Assets/Images/opponent_sheet.png");

	//Parse enemy Sprite Sheet Forward
	enemyClips.push_back(new SDL_Rect{ 79, 16, 30, 37 });//Still Left
	enemyClips.push_back(new SDL_Rect{ 140, 16, 30, 37 });//Still Right

	for (int i = 0; i < 5; i++)
	{
		enemyClips.push_back(new SDL_Rect{ 16 + i * 25, 132, 25, 37 });//Run Left
	}


	for (int i = 0; i < 5; i++)
	{
		enemyClips.push_back(new SDL_Rect{ 143 + i * 25, 132, 25, 37 });//Run Right
	}


	for (int i = 0; i < 4; i++)
	{
		enemyClips.push_back(new SDL_Rect{ 11 + i * 22, 170, 22, 22 });//Jump Left
	}


	for (int i = 0; i < 4; i++)
	{
		enemyClips.push_back(new SDL_Rect{ 182 + i * 22, 170, 22, 22 });//Jump Right
	}

	enemyClips.push_back(new SDL_Rect{ 99, 172, 38, 20 });//Crouch Left
	enemyClips.push_back(new SDL_Rect{ 144, 172, 38, 20 });//Crouch Right
	enemyClips.push_back(new SDL_Rect{ 43, 7, 14, 45 });//Up Left
	enemyClips.push_back(new SDL_Rect{ 223, 7, 14, 45 });//Up Right

	//Open Bullet Sheet
	objectTextures[Object::Type::bullet] = new Texture();
	objectTextures[Object::Type::bullet]->load(renderer, "./Assets/Images/cs_w_bullet.png");
	
	//Open player Sprite Sheet Forward
	objectTextures[Object::Type::player] = new Texture();
	objectTextures[Object::Type::player]->load(renderer,"./Assets/Images/player_sheet.png");

	//Parse player Sprite Sheet Forward
	playerClips.push_back(new SDL_Rect{ 79, 16, 30, 37 });//Still Left
	playerClips.push_back(new SDL_Rect{ 140, 16, 30, 37 });//Still Right
	
	for (int i = 0; i<5; i++) 
	{
		playerClips.push_back(new SDL_Rect{ 16 + i * 25, 132, 25, 37 });//Run Left
	}

	
	for (int i = 0; i<5; i++) 
	{
		playerClips.push_back(new SDL_Rect{ 143 + i * 25, 132, 25, 37 });//Run Right
	}

	
	for (int i = 0; i<4; i++) 
	{
		playerClips.push_back(new SDL_Rect{ 11 + i * 22, 170, 22, 22 });//Jump Left
	}

	
	for (int i = 0; i<4; i++) 
	{
		playerClips.push_back(new SDL_Rect{ 182 + i * 22, 170, 22, 22 });//Jump Right
	}

	playerClips.push_back(new SDL_Rect{ 99, 172, 38, 20 });//Crouch Left
	playerClips.push_back(new SDL_Rect{ 144, 172, 38, 20 });//Crouch Right
	playerClips.push_back(new SDL_Rect{ 43, 7, 14, 45 });//Up Left
	playerClips.push_back(new SDL_Rect{ 223, 7, 14, 45 });//Up Right

	//Create bridge textures
	objectTextures[Object::Type::bridge_center] = new Texture();
	objectTextures[Object::Type::bridge_center]->load(renderer,"./Assets/Images/bridge_center.png");
	objectTextures[Object::Type::bridge_end] = new Texture();
	objectTextures[Object::Type::bridge_end]->load(renderer, "./Assets/Images/bridge_end.png");
	objectTextures[Object::Type::bridge_start] = new Texture();
	objectTextures[Object::Type::bridge_start]->load(renderer, "./Assets/Images/bridge_start.png");

	//Create Block Textures
	objectTextures[Object::Type::center_block] = new Texture();
	objectTextures[Object::Type::center_block]->load(renderer, "./Assets/Images/center_block.png");
	objectTextures[Object::Type::top_block] = new Texture();
	objectTextures[Object::Type::top_block]->load(renderer, "./Assets/Images/top_block.png");
	objectTextures[Object::Type::tree_background] = new Texture();
	objectTextures[Object::Type::tree_background]->load(renderer, "./Assets/Images/tree_background.png");

	//create Water Textures
	objectTextures[Object::Type::water] = new Texture();
	objectTextures[Object::Type::water]->load(renderer, "./Assets/Images/water.png");
	objectTextures[Object::Type::water_shore] = new Texture();
	objectTextures[Object::Type::water_shore]->load(renderer, "./Assets/Images/water_shore.png");
	objectTextures[Object::Type::water_top] = new Texture();
	objectTextures[Object::Type::water_top]->load(renderer, "./Assets/Images/water_top.png");
	objectTextures[Object::Type::water_wall] = new Texture();
	objectTextures[Object::Type::water_wall]->load(renderer, "./Assets/Images/water_wall.png");
	objectTextures[Object::Type::water_wall_corner] = new Texture();
	objectTextures[Object::Type::water_wall_corner]->load(renderer, "./Assets/Images/water_wall_corner.png");
	guiFont = TTF_OpenFont("./Assets/fonts/impact.ttf", 40);
	if(!guiFont) printf("TTF_OpenFont: %s\n", TTF_GetError());
}

void GUI::cleanUp(){

	//Free the window
	SDL_DestroyWindow(window);
    window = nullptr;

    //Free the renderer
   	SDL_DestroyRenderer(renderer);
    renderer = nullptr;

    //Free loaded images
	for (auto& pair : objectTextures)
	{
		pair.second->free();
	}	

	TTF_CloseFont(guiFont);
    //Quit SDL Subsystems
	TTF_Quit();
   	IMG_Quit();
    SDL_Quit();

}

void GUI::displayGameState(Engine* engine){
	auto& objects = engine->getObjects();
	//Clear screen
	SDL_SetRenderDrawColor(renderer, 0, 0, 0,255);
	SDL_RenderClear(renderer);
	//render blocks
	for (auto& object: objects)
	{
		switch (object->getName())
		{
		case Object::Type::enemy:
			objectTextures[Object::Type::enemy]->render(renderer, object->getPosition(), enemyClips[((Enemy*)object.get())->getCurrentSprite()]);
			break;
		case Object::Type::player:
			objectTextures[Object::Type::player]->render(renderer, object->getPosition(), playerClips[((Player*)object.get())->getCurrentSprite()]);
			break;
		case Object::Type::hpbar:
			objectTextures[Object::Type::hpbar]->render(renderer, object->getPosition(), hpClips[((HealthBar*)object.get())->getCurrentSprite()]);
			break;
		case Object::Type::bullet:
			objectTextures[Object::Type::bullet]->render(renderer, object->getPosition(), new SDL_Rect{ 96, 8, 8, 8 });
			break;
		default:
			objectTextures[object->getName()]->render(renderer, object->getPosition(), nullptr);
			break;
		}
		
	}

	string text;

	if (engine->getGameOver() && engine->getGameWon())
	{
		text = "LEVEL COMPLETE";
	}
	else if (engine->getGameOver())
		text = "YOU LOSE!";
	else
	{
		switch (*command) {
		case Object::Command::up: text = "Up"; break;
		case Object::Command::down: text = "Crouch"; break;
		case Object::Command::right: text = "Right"; break;
		case Object::Command::left: text = "Left"; break;
		case Object::Command::NA: text = "NA"; break;
		case Object::Command::jump: text = "Jump"; break;
		}
	}

	//Render Command to Text
	SDL_Color textColor = { 255, 255, 153 };
	SDL_Texture* textSheetTexture = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Solid(guiFont, text.c_str(), textColor));

	//Set rendering space and render to screen
	int width = 0, height = 0;
	SDL_QueryTexture(textSheetTexture, nullptr, nullptr, &width, &height);
	SDL_Rect renderQuad = { screenDimensions.x - width - 5, 10, width, height };

	//Render to screen
	SDL_RenderCopy(renderer, textSheetTexture, nullptr, &renderQuad);
	//-------------------------------------------------------------
	//-------------------------------------------------------------

	//Update the visible screen
	SDL_RenderPresent(renderer);


	////Update the visible screen
	//SDL_RenderPresent(renderer);
	
}

Vector2D GUI::getDimensions(const Object * object) const
{

	switch (object->getName())
	{
	case Object::Type::player:
		if (((Player*)object)->getCurrentSprite() < (int)playerClips.size())
		{
			return { playerClips[((Player*)object)->getCurrentSprite()]->w, playerClips[((Player*)object)->getCurrentSprite()]->h };
		}
	case Object::Type::enemy:
		return { enemyClips[0]->w, enemyClips[0]->h };
		break;
	case Object::Type::bridge_center:
	case Object::Type::bridge_end:
	case Object::Type::bridge_start:
	case Object::Type::center_block:
	case Object::Type::top_block:
	case Object::Type::tree_background:
	case Object::Type::water:
	case Object::Type::water_shore:
	case Object::Type::water_top:
	case Object::Type::water_wall:
	case Object::Type::water_wall_corner:
		return { 50,50 };
		break;
	case Object::Type::bullet:
		return { 8,8 };
		break;
	default:
		return { 0,0 };
		break;
	}
	
	return { 0,0 };
}


