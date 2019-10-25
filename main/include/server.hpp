#pragma once
#include <uvw.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <thread>
#include <algorithm>

class Server
{
public:
	Server(std::string addr, int port);
	~Server();
	void listenServer(uvw::Loop& loop);
	void Send(uint8_t* data, int data_size);
	void runner();
private:
	std::string m_addr;
	int m_port;
	std::shared_ptr<uvw::Loop> loop; 
	std::unique_ptr<std::thread> loopThread;
	std::vector< std::shared_ptr<uvw::TCPHandle>> clients;
};