#pragma once
#include <uvw.hpp>

class Client
{
public:
	Client(std::string addr, int port);
	void connect(uvw::Loop& loop, std::string addr, int port);
private:
};