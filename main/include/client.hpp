#pragma once
#include <uvw.hpp>

class Client
{
public:
	Client();
	void connect(uvw::Loop& loop, std::string addr, int port);
private:
};