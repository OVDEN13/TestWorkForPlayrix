#pragma once
class Manager;

class ColliderManager
{
public:
	ColliderManager(Manager* manager);
	void update(float dt);

private:
	void init();
	void checkCollision();
	void makeWalls();
private:
	Manager* _manager;
};

enum class TAG : std::size_t
{
	NONE,
	BULLETS,
	TARGETS,
	BOMB,
	WALLS,
	AIM,
	BUTTONS
};

enum class COLLIDER_TYPE : std::size_t
{
	CIRCLE,
	BOX
};

typedef std::shared_ptr<ColliderManager> ColliderManagerPtr;
 
