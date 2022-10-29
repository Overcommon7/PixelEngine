#include "pch.h"
#include "Game.h"
#include "Defines.h"
#include "TextManager.h"

#pragma region System

void Game::Initialize()
{
	fonts.insert({ K_FONT_CANDARA, LoadFont("CandaraBold.ttf")});
	TextManager::Initialize();
}

void Game::ShutDown()
{
	TextManager::ShutDown();
	for (auto& t : textures)
		UnloadTexture(t.second);
	for (auto& f : fonts)
		UnloadFont(f.second);
}
#pragma endregion

#pragma region TitleScreen
void Game::TitleScreenLogic(GameScreen& cs)
{

}

void Game::TitleScreenDraw()
{

}
#pragma endregion

#pragma region GamePlay
void Game::GameplayLogic(GameScreen& cs)
{
	TextManager::Update();
}

void Game::GameplayDraw()
{
	TextManager::Draw();
}
#pragma endregion

#pragma region GameOver
void Game::GameOverLogic(GameScreen& cs)
{

}

void Game::GameOverDraw()
{
	
}

#pragma endregion



