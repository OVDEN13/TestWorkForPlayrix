#include "stdafx.h"
#include "ECS.h"

Entity::Entity(Manager& manager): _manager(manager){}

void Entity::update(float dt)
{
	for (auto& c : _components)
	{
		c->update(dt);
	}
}

void Entity::draw()
{
	for (auto& c : _components)
	{
		c->draw();
	}
}

bool Entity::isActive() const
{
	return _active;
}

void Entity::destroy()
{
	_active = false;
}

bool Entity::hasGroup(Group mGroup)
{
	return _groupBitset[mGroup];
}

void Entity::addGroup(Group group)
{
	_groupBitset[group] = true;
	_manager.addToGroup(this, group);
}

void Entity::delGroup(Group group)
{
	_groupBitset[group] = false;
}


void Manager::update(float dt)
{
	for (auto& entities : _entities)
	{
		entities->update(dt);
	}
}

void Manager::draw()
{
	for (auto& entities : _entities)
	{
		entities->draw();
	}
}

void Manager::refresh()
{
	for (auto i(0u); i < maxGroups; i++)
	{
		auto& groupedEntities(_groupedEntities[i]);

		auto cb = [i](Entity* entity)
		{
			return !entity->isActive() || !entity->hasGroup(i);
		};

		groupedEntities.erase(std::remove_if(groupedEntities.begin(), groupedEntities.end(), cb), groupedEntities.end());
	}

	auto eraseCb = [](const std::unique_ptr<Entity>& åntity)
	{
		return !åntity->isActive();
	};

	_entities.erase(std::remove_if(_entities.begin(), _entities.end(), eraseCb), _entities.end());
}

void Manager::addToGroup(Entity* entity, Group group)
{
	_groupedEntities[group].emplace_back(entity);
}

const std::vector<Entity*>& Manager::getGroup(Group group)
{
	return _groupedEntities[group];
}

Entity& Manager::addEntity()
{
	Entity* e = new Entity(*this);
	std::unique_ptr<Entity> uPtr{ e };
	_entities.emplace_back(std::move(uPtr));
	return *e;
}
