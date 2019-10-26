#include <uvw.hpp>
#include <memory>
#include <iostream>
#include "server.hpp"
#include "client.hpp"

#include <uvw.hpp>
#include <memory>


int main(int argc, char* argv[]) {
	//args 
	std::string status = argv[1];
	std::string addr = argv[2];
	std::string Iport = argv[3];
	int port = atoi(Iport.c_str());

	if (status == "server") {
		auto srv = Server(addr, port);
		srv.Run();
	}
	else if (status == "client") {
		auto cl = Client(addr, port);
	}
	else {
		std::cout << "Use: 0 for server, 1 for client" << std::endl;
	}
	return 0;
}