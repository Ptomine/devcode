#ifndef DEMO_LEVEL_HPP
#define DEMO_LEVEL_HPP

#include <Box2D/Box2D.h>
#include "../../Core/include/GameSceneManager.hpp"
#include "../../Core/include/EntityManager.hpp"
#include "../../Core/include/Level.hpp"

class DemoLevel : public BasicScene
{
public:
	DemoLevel();
	~DemoLevel();

	void initialize(sf::RenderWindow&);
	void createBarriers(const std::vector<Object>& barriers);
	BasicScene* update(sf::RenderWindow&, float);
	void render(sf::RenderWindow&);
	void cease();

	void enemyFromFile(std::string path);
private:
	Level level;
	sf::View view;
	EntityManager *manager;

	b2World world;
};

#endif //DEMO_LEVEL_HPP
