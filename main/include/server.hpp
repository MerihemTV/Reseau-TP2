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
	void Send(uint8_t* data, int data_size);
private:
	std::string m_addr;
	int m_port;
	void listen(uvw::Loop& loop);
	std::vector< std::shared_ptr<uvw::TCPHandle>> clients;
};