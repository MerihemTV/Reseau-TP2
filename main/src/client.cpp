#include "client.hpp"
#include <iostream>

void Client::connect(uvw::Loop& loop, std::string addr, int port) {
	auto tcp = loop.resource<uvw::TCPHandle>();

	tcp->on<uvw::ErrorEvent>([](const uvw::ErrorEvent&, uvw::TCPHandle&) { /* handle errors */ });

	tcp->on<uvw::ConnectEvent>([](const uvw::ConnectEvent&, uvw::TCPHandle& tcp) {
		auto dataWrite = std::unique_ptr<char[]>(new char[2]{ 'b', 'c' });
		tcp.write(std::move(dataWrite), 2);
		tcp.read();
	});

	tcp->on<uvw::DataEvent>([](const uvw::DataEvent& evt, uvw::TCPHandle&) {
		std::string result( evt.data.get(), evt.length);
		std::cout <<  result << std::endl;
	});

	tcp->connect(addr, port);
}

Client::~Client() {
	if (loopThread->joinable()) {
		loopThread->join();
	}
}

void Client::runner() {
	loop->run();
}

Client::Client(std::string addr, int port) {
	loop = uvw::Loop::getDefault();
	connect(*loop, addr, port);
	loopThread = std::make_unique<std::thread>(&Client::runner, this);
}