#ifndef ECS_H
#define ECS_H
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>


class Component;
class Entity;
class Manager;

using ComponentID = std::size_t;
using Group = std::size_t;

inline ComponentID getNewComponentTypeID()
{
	static ComponentID lastID = 0u;
	return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept
{
	static_assert (std::is_base_of<Component, T>::value, "");
	static ComponentID typeID = getNewComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitset = std::bitset<maxGroups>;

using ComponentArray = std::array<Component*, maxComponents>;

class Component
{
public:
	Entity* entity;

	virtual void init() {}
	virtual void update(float dt) {}
	virtual void draw() {}
	virtual ~Component() {}
};

class Entity
{
private:
	Manager& _manager;
	bool _active = true;
	std::vector<std::unique_ptr<Component>> _components;

	ComponentArray _componentArray;
	ComponentBitSet _componentBitset;
	GroupBitset _groupBitset;

public:
	Entity(Manager& manager);

	void update(float dt);

	void draw();

	bool isActive() const;
	void destroy();

	bool hasGroup(Group group);

	void addGroup(Group group);
	void delGroup(Group group);


	template <typename T> bool hasComponent() const
	{
		return _componentBitset[getComponentTypeID<T>()];
	}

	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs)
	{
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component>uPtr{ c };
		_components.emplace_back(std::move(uPtr));

		_componentArray[getComponentTypeID<T>()] = c;
		_componentBitset[getComponentTypeID<T>()] = true;

		c->init();
		return *c;
	}

	template<typename T> T& getComponent() const
	{
		auto ptr(_componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}
};

class Manager
{
public:
	void update(float dt);
	void draw();
	void refresh();

	void addToGroup(Entity* entity, Group group);
	const std::vector<Entity*>& getGroup(Group group);

	Entity& addEntity();

private:
	std::vector<std::unique_ptr<Entity>> _entities;
	std::array<std::vector<Entity*>, maxGroups> _groupedEntities;
};

enum GROUP_NAME : std::size_t
{
	BACKGROUND,
	DECORS,
	PLAYER,
	BULLETS,
	TARGETS,
	COLLIDERS,
	WALLS,
	
	GAME_TIMER,
	GAME_SCORE,
	UI,
	BUTTONS,
	EFFECTS
};

#endif