#include <uvw.hpp>
#include <memory>
#include <iostream>
#include <server.hpp>
#include "classRegistry.hpp"
#include "player.hpp"
#include "enemy.hpp"

void conn(uvw::Loop& loop) {
	auto tcp = loop.resource<uvw::TCPHandle>();

	tcp->on<uvw::ErrorEvent>([](const uvw::ErrorEvent&, uvw::TCPHandle&) { /* handle errors */ });

	tcp->once<uvw::ConnectEvent>([](const uvw::ConnectEvent&, uvw::TCPHandle& tcp) {
		
	auto dataWrite = std::unique_ptr<char[]>(new char[2]{ 'b', 'c' });
	tcp.write(std::move(dataWrite), 2);
	tcp.close();
	});

	tcp->connect(std::string{ "127.0.0.1" }, 4242);
}

Player ConstructorFake() {
	Player p;
	return p;
}

int main(int argc, char* argv[]) {
	classRegistry *CR = classRegistry::get();
	//CR->saveClassInRegistry<Player>(ConstructorFake);
	/*
	std::string status = argv[1];
	std::string addr = argv[2];
	std::string port = argv[3];

	//If programme executed as server
	if (status == "server") {
		Server srv(addr, atoi(port.c_str()));
	}
	else if (status == "client") {
		auto loop = uvw::Loop::getDefault();
		loop->run();
		conn(*loop);
	}
	else {
		std::cout << "Use: 0 for server, 1 for client" << std::endl;
	}
	*/
	return 0;
}