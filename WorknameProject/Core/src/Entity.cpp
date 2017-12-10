#include "../include/Entity.hpp"
#include <iostream>

Entity::EntityManagerRequest::EntityManagerRequest(Entity::EntityManagerRequest::RequestType _type, Entity::EntityGroup _group, const std::string& _name, Entity *_additive)
	: reqType(_type)
	, targetGroup(_group)
	, targetName(_name)
	, additive(_additive)
{
}




Entity::AbstractBody::AbstractBody(const sf::Vector2f& _size)
	: size(_size)
{
}




const sf::FloatRect Entity::AbstractBody::bodyRect()
{
	return sf::FloatRect(getPosition() - getOrigin(), size);
}




Entity::Entity(const sf::Vector2f& initPos, const sf::Vector2f& size, Entity::EntityGroup _group)
	: sprite()
	, abstractBody(size)
	, group(_group)
	, active(true)
	, response(nullptr)
	, live(true)
{
	sprite.setOrigin(sprite.getLocalBounds().width / 2.0f, sprite.getLocalBounds().height - 20.0f);
	sprite.setPosition(initPos);
	abstractBody.setOrigin(size.x / 2.0f, size.y / 2.f);
	abstractBody.setPosition(initPos);
}




Entity::~Entity()
{
}


const sf::Sprite& Entity::getSprite()
{
	return sprite;
}




bool Entity::isColliding(Entity *other)
{
	return abstractBody.bodyRect().intersects(other->abstractBody.bodyRect());
}




bool Entity::isActive()
{
	return active;
}


bool Entity::isLive() {
	return live;
}

void Entity::setGroup(Entity::EntityGroup _group)
{
	group = _group;
}




Entity::EntityGroup Entity::whatGroup()
{
	return group;
}




void Entity::setResponse(Entity *_response)
{
	response = _response;
}
