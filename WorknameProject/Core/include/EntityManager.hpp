#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP

#include <array>
#include <unordered_map>
#include <queue>

#include <Box2D/Dynamics/b2World.h>

#include "Entity.hpp"

class EntityManager
{
public:
	EntityManager();
	~EntityManager();

	void addEntity(const std::string&, Entity*);
	Entity* getEntity(Entity::EntityGroup, const std::string&);
	void update(float, b2World&);
	void render(sf::RenderWindow&);
private:
	void updateGroup(std::unordered_map<std::string, Entity*>&, float, b2World&);
	void checkCollision(Entity::EntityGroup, Entity::EntityGroup);
	void executeRequest(Entity*);

	std::array<std::unordered_map<std::string, Entity*>, 6> all;

	Entity::EntityManagerRequest* lastRequest;
};




struct axisYcomparator
{
	bool operator()(Entity *left, Entity *right) const
	{
		return left->getSprite().getPosition().y < right->getSprite().getPosition().y;
	}
};

typedef std::priority_queue<Entity*, std::vector<Entity*>, axisYcomparator> draw_queue;

#endif //ENTITY_MANAGER_HPP
