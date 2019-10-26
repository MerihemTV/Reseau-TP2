#pragma once
#include <uvw.hpp>
#include <thread>
#include "class_registry.hpp"
#include "replication_manager.hpp"
#include "game_object.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "streams.hpp"

class Client
{
public:
	Client(std::string addr, int port);
	~Client();
	void connect(uvw::Loop& loop, std::string addr, int port);
	void runner();

private:
	std::unique_ptr<std::thread> loopThread;
	std::shared_ptr<uvw::Loop> loop;
};