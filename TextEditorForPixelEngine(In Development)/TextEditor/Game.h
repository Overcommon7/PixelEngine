#pragma once
#include "Clicker.h"

class Game
{
private:
	
	Game() = delete;
	Game(const Game& g) = delete;
	Game& operator= (const Game& g) = delete;

	inline static Color color = GREEN;

public:
	
	static void Initialize();
	static void DeInitialize();


	static void TitleScreenLogic(GameScreen& cs);
	static void TitleScreenDraw();
	static void GameplayLogic(GameScreen& cs);
	static void GameplayDraw();
	static void GameOverLogic(GameScreen& cs);
	static void GameOverDraw();
	static void ShutDown();
	
};

