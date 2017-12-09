#include "../include/AnimationManager.hpp"

AnimationManager::AnimationManager()
	: currentAnimation(nullptr)
{
}




AnimationManager::~AnimationManager()
{
	for(auto& iterator : animations)
	{
		delete iterator.second;
	}
}




void AnimationManager::update(unsigned row, float deltaTime)
{
	currentAnimation->second->update(row, deltaTime);
}




void AnimationManager::addAnimation(int index, Animation *newAnimation)
{
	animations.insert(std::make_pair(index, newAnimation));
}




void AnimationManager::setAnimation(int index)
{
	auto found = animations.find(index);
	if(found != animations.end())
	{
		currentAnimation = found;
	}
	currentAnimation->second->initialize();
	currentAnimation->second->restart();
}




int AnimationManager::whatAnimation()
{
	return currentAnimation->first;
}




float AnimationManager::getThisAnimationTime()
{
	return currentAnimation->second->getAnimationTime();
}




float AnimationManager::getAnimationTime(int index)
{
	auto found = animations.find(index);
	if(found != animations.end())
	{
		return found->second->getAnimationTime();
	}
	return 0.0f;
}




bool AnimationManager::isAnimationEnded()
{
	return currentAnimation->second->isEnded();
}
