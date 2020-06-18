#pragma once
class Manager;

enum class TARGET_TYPE : std::size_t
{
	CLASSIC,
	BOMB
};

struct TargetData
{
	TARGET_TYPE type = TARGET_TYPE::CLASSIC;
	int delayBeforeSpawn = 0;
	FPoint spawnPos = FPoint();
};


class TargetManager
{
public:
	TargetManager(Manager* manager);
	void changedState();
	void draw();
	void createTargets();
private:
	void init();
	void makeTarget(TargetData data);
	void makeBaseTarget(TargetData data);
	void makeBomb(TargetData data);
	
	const FPoint& getSpawnPosition(int index);
private:
	GameStaticConfig _gameConfig;

	std::vector<TargetData> _targetData;
	
	bool _isPlay;
	
	double _timer;
	Manager* _manager;
};

typedef std::shared_ptr<TargetManager> TargetManagerPtr;