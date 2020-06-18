#include "stdafx.h"
#include "ColliderManager.h"
#include "Collider.h"
#include "Transform.h"
#include "ECS.h"

ColliderManager::ColliderManager(Manager* manager) : _manager(manager)
{
	init();
}

void ColliderManager::update(float dt)
{
	checkCollision();
}

void ColliderManager::init()
{
	makeWalls();
}

void ColliderManager::makeWalls()
{
	auto& leftWall = _manager->addEntity();
	auto& leftTransform = leftWall.addComponent<Transform>();
 
	auto& leftCollider = leftWall.addComponent<Collider>();
	leftCollider.setTag(TAG::WALLS);
	leftCollider.setType(COLLIDER_TYPE::BOX);
	leftCollider.setCollider(FRect(-5, 5, 0, Render::device.Height() * 1.5));
	leftWall.addGroup(GROUP_NAME::WALLS);

	auto& wall = _manager->addEntity();
	auto& transform = wall.addComponent<Transform>();
	auto& collider = wall.addComponent<Collider>();
	collider.setTag(TAG::WALLS);
	collider.setType(COLLIDER_TYPE::BOX);
	collider.setCollider(FRect(Render::device.Width() - 5, Render::device.Width()+5, 0, Render::device.Height() * 1.5));
	wall.addGroup(GROUP_NAME::WALLS);
}

void ColliderManager::checkCollision()
{
	const std::vector<Entity*>& walls = _manager->getGroup(GROUP_NAME::WALLS);
	auto leftWalls = walls.at(0);
	auto rightWalls = walls.at(1);

	auto leftCollider = leftWalls->getComponent<Collider>();
	auto rightCollider = rightWalls->getComponent<Collider>();
	
	const std::vector<Entity*>& group = _manager->getGroup(COLLIDERS);
	const auto count = group.size();
	for(auto f = 0; f < count; f++)
	{
		auto firstObject = group.at(f);
		auto firstCollider = firstObject->getComponent<Collider>();
		auto firstTransfrom = firstObject->getComponent<Transform>();
		
		auto& firstPos = firstTransfrom.getPosition();
		auto firstRadius = firstCollider.getRadius();

		//Сначала проверяю не натолкнулся ли на стену
		if(leftCollider.getCollider().Contains(firstPos))
		{
			firstCollider.onCollision(leftWalls);
		}
		else if(rightCollider.getCollider().Contains(firstPos))
		{
			firstCollider.onCollision(rightWalls);
		}

		//Потом на другие обьекты
		for(auto s = (f+1); s < count; s++)
		{
			const auto secondObject = group.at(s);
			auto secondCollider = secondObject->getComponent<Collider>();
			auto secondTransform = secondObject->getComponent<Transform>();
			
			const auto secondPos = secondTransform.getPosition();
			const auto secondRadius = secondCollider.getRadius();;

			const auto radiusSum = firstRadius + secondRadius;
			const auto minDist = radiusSum * radiusSum;
			
			const float distance = math::Vector3(firstPos.x, firstPos.y, 0).DistanceSq(math::Vector3(secondPos.x, secondPos.y, 0)); 
			
			if(distance < minDist)
			{
				secondCollider.onCollision(firstObject);
				firstCollider.onCollision(secondObject);
			}
	 
		}
	}
}
 