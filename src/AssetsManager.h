#pragma once
#include <map>
#include "ECS.h"

struct GameStaticConfig
{
	int countTarget = 5;
	int countBomb = 3;
	int targetSpeed = 20;
	int bombSpeed = 30;
	float bulletSpeed = 5.0;
	double time = 10.0;
	int iterations = 10.0;
};

class AssetsManager
{
public:
	AssetsManager();
	~AssetsManager();

	void addTexture(std::string id);
	void addTexture(std::string id, Render::Texture* texture);
	Render::Texture* getTexture(std::string id);
	
	const GameStaticConfig& getStaticGameConfig();
private:
	void init();
	void initStaticGameConfig();
	
	template<typename T>
	T ReadLineAndGetValue(IO::TextReader* reader, const std::string& valueName)
	{
		std::string out, name, value;
		T result = 0;

		out = reader->ReadAsciiLine();
		if (utils::ReadNvp(out, name, value) && name == valueName)
		{
			result = utils::lexical_cast<T>(value);
		}
		else
		{
			Log::Error("Failed to read data from file");
			assert(false);
		}

		return result;
	}
	
private:
	GameStaticConfig _gameConfig;
	std::map<std::string, Render::Texture*> _textures;
 

};

typedef std::shared_ptr<AssetsManager> AssetsManagerPtr;