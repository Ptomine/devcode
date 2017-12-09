#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>
#include <Box2D/Dynamics/b2World.h>

class Entity
{
public:
	enum EntityGroup
	{
		GROUP_NEUTRAL,
		GROUP_PLAYER,
		GROUP_ENEMY,
		GROUP_DANGERZONE,
		GROUP_PICKUP,
		GROUP_SOLID,
	};

	struct EntityManagerRequest
	{
		enum RequestType
		{
			TYPE_ADD,
			TYPE_FIND,
		};

		EntityManagerRequest(RequestType, EntityGroup, const std::string&, Entity* = nullptr);
		const RequestType reqType;
		EntityGroup targetGroup;
		const std::string targetName;
		Entity *additive;
	};

	Entity(const sf::Vector2f&, const sf::Vector2f&, EntityGroup);
	virtual ~Entity();

	virtual EntityManagerRequest* update(float, b2World&) = 0;
	virtual void collisionEvent(Entity*) = 0;

	const sf::Sprite& getSprite();

	bool isColliding(Entity*);
	bool isActive();

	void setGroup(EntityGroup);
	EntityGroup whatGroup();

	void setResponse(Entity*);
protected:
	sf::Sprite sprite;

	class AbstractBody : public sf::Transformable
	{
	public:
		AbstractBody(const sf::Vector2f&);
		const sf::FloatRect bodyRect();
	private:
		sf::Vector2f size;
	} abstractBody;

	EntityGroup group;
	bool active;

	Entity* response;
};

#endif //ENTITY_HPP
