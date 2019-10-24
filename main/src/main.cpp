#include <uvw.hpp>
#include <memory>
#include <iostream>
#include <server.hpp>
#include "classRegistry.hpp"
#include "player.hpp"
#include "enemy.hpp"

#include <iostream>

#include <uvw.hpp>
#include <memory>

void listen(uvw::Loop& loop) {
	std::shared_ptr<uvw::TCPHandle> tcp = loop.resource<uvw::TCPHandle>();

	tcp->once<uvw::ListenEvent>([](const uvw::ListenEvent&, uvw::TCPHandle& srv) {
		std::shared_ptr<uvw::TCPHandle> client = srv.loop().resource<uvw::TCPHandle>();
		std::cout << "New connection" << std::endl;

		client->on<uvw::CloseEvent>([ptr = srv.shared_from_this()](const uvw::CloseEvent&, uvw::TCPHandle&) { ptr->close(); });
		client->on<uvw::EndEvent>([](const uvw::EndEvent&, uvw::TCPHandle& client) { client.close(); });
		client->on<uvw::DataEvent>([](const uvw::DataEvent&, uvw::TCPHandle&) {std::cout << "Data received" << std::endl; });
		srv.accept(*client);
		client->read();
	});

	tcp->bind("127.0.0.1", 4242);
	tcp->listen();
}

void conn(uvw::Loop& loop) {
	auto tcp = loop.resource<uvw::TCPHandle>();

	tcp->on<uvw::ErrorEvent>([](const uvw::ErrorEvent&, uvw::TCPHandle&) { /* handle errors */ });

	tcp->on<uvw::ConnectEvent>([](const uvw::ConnectEvent&, uvw::TCPHandle& tcp) {
		auto dataWrite = std::unique_ptr<char[]>(new char[2]{ 'b', 'c' });
		tcp.write(std::move(dataWrite), 2);
		tcp.close();
	});

	tcp->on<uvw::DataEvent>([](const uvw::DataEvent& evt, uvw::TCPHandle&) {
		std::cout << evt.data.get() << std::endl;
	});

	tcp->connect(std::string{ "127.0.0.1" }, 4242);
}


int main(int argc, char* argv[]) {

	//args 
	std::string status = argv[1];
	std::string addr = argv[2];
	std::string port = argv[3];

	
	if (status == "server") {
		auto srv = Server("127.0.0.1",4242);
		
		/*
		auto loop = uvw::Loop::getDefault();
		listen(*loop);
		loop->run();
		*/
		
	}
	else if (status == "client") {
		auto loop = uvw::Loop::getDefault();
		conn(*loop);
		loop->run();
	}
	else {
		std::cout << "Use: 0 for server, 1 for client" << std::endl;
	}
	return 0;
}
/*
int main(int argc, char* argv[]) {
	
	std::string status = argv[1];
	std::string addr = argv[2];
	std::string port = argv[3];

	//If programme executed as server
	if (status == "server") {
		//Server srv(addr, atoi(port.c_str()));
		auto loop = uvw::Loop::getDefault();
		listen(*loop);
		loop->run();
	}
	else if (status == "client") {
		auto loop = uvw::Loop::getDefault();
		loop->run();
		conn(*loop);
	}
	else {
		std::cout << "Use: 0 for server, 1 for client" << std::endl;
	}
	return 0;
}*/