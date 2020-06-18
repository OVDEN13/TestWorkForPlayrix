#include "stdafx.h"
#include "AssetsManager.h"

AssetsManager::AssetsManager()
{
	init();
}

AssetsManager::~AssetsManager()
{
	_textures.clear();
}

void AssetsManager::init()
{
	initStaticGameConfig();
}

void AssetsManager::addTexture(std::string id)
{
	addTexture(id, Core::resourceManager.Get<Render::Texture>(id));
}

void AssetsManager::addTexture(std::string id, Render::Texture* texture)
{
	_textures.emplace(id, texture);
}

Render::Texture* AssetsManager::getTexture(std::string id)
{
	return _textures[id];
}

void AssetsManager::initStaticGameConfig()
{
	boost::system::error_code err;
	const auto stream = Core::fileSystem.OpenRead("input.txt", err);

	if (err != 0)
	{
		Log::Error("Failed to open file with initial data");
		assert(false);
	}

	IO::TextReader reader(stream.get());

	GameStaticConfig config;
	config.countTarget = ReadLineAndGetValue<int>(&reader, "CountTarget");
	config.countBomb = ReadLineAndGetValue<int>(&reader, "CountBomb");

	config.targetSpeed = ReadLineAndGetValue<int>(&reader, "TargetSpeed");
	config.bombSpeed = ReadLineAndGetValue<int>(&reader, "BombSpeed");
	config.bulletSpeed = ReadLineAndGetValue<float>(&reader, "BulletSpeed");
	
	config.time = ReadLineAndGetValue<float>(&reader, "Time");
	config.iterations = ReadLineAndGetValue<float>(&reader, "Iterations");
	
	_gameConfig = config;
}

const GameStaticConfig& AssetsManager::getStaticGameConfig()
{
	return _gameConfig;
}