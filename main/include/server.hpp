#pragma once
#include <uvw.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <thread>
#include <algorithm>
#include "class_registry.hpp"
#include "replication_manager.hpp"
#include "game_object.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "streams.hpp"

class Server
{
public:
	Server(std::string addr, int port);
	~Server();
	void listenServer(uvw::Loop& loop);
	void Send(uint8_t* data, int data_size);
	void runner();
	void Run();
	void PrepareAndSend(OutputStream& os, std::vector<GameObject*>& gameObjects);
private:
	std::string m_addr;
	int m_port;
	std::shared_ptr<uvw::Loop> loop; 
	std::unique_ptr<std::thread> loopThread;
	std::vector<std::shared_ptr<uvw::TCPHandle>> clients;
};