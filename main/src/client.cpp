#include "client.hpp"
#include <iostream>

void Client::connect(uvw::Loop& loop, std::string addr, int port) {
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

	tcp->connect(addr, port);
}

Client::Client() {
	auto loop = uvw::Loop::getDefault();
	connect(*loop, "127.0.0.1", 4242);
	loop->run();
}