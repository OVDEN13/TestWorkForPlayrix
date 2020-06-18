#pragma once
class Manager;

class BulletManager
{
public:
	BulletManager(Manager* manager);
	void changedState();
	
	void createBullet(bool isPunchy = false);
	void draw();
private:
	FPoint calculateSpawnPosition();
private:
	float _bulletSpeed;
	Manager* _manager;
};

typedef std::shared_ptr<BulletManager> BulletManagerPtr;