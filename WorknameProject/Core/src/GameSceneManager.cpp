#include "../include/GameSceneManager.hpp"
#include <iostream>

GameSceneManager::GameSceneManager(sf::RenderWindow& _window, BasicScene *initScene)
	: window(_window)
{
	pushScene(initScene);
}




GameSceneManager::~GameSceneManager()
{
	while(!scenes.empty())
	{
		delete scenes.top();
		scenes.pop();
	}
}




void GameSceneManager::update(float deltaTime)
{
	if(scenes.empty())
	{
		return window.close();
	}

	BasicScene *current = scenes.top();
	BasicScene *updated = current->update(window, deltaTime);

	if(!current->isActive())
	{
		std::cout << "Last scene deleted\n";
		delete current;
		scenes.pop();
	}
	if(updated != current)
	{
		std::cout << "NewSceneAdded\n";
		pushScene(updated);
	}
	scenes.top()->render(window);
}




void GameSceneManager::pushScene(BasicScene *newScene)
{
	if(newScene == nullptr)
	{
		return window.close();
	}
	scenes.push(newScene);
	scenes.top()->initialize(window);
}
