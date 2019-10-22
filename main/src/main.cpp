#include <uvw.hpp>
#include <memory>
#include <iostream>
#include <server.hpp>

std::vector< std::shared_ptr<uvw::TCPHandle>> clients;

void listen(uvw::Loop& loop) {
	std::shared_ptr<uvw::TCPHandle> tcp = loop.resource<uvw::TCPHandle>();

	tcp->on<uvw::ListenEvent>([tcp](const uvw::ListenEvent&, uvw::TCPHandle& srv) {
		std::cout << "New Connection" << std::endl;
		std::shared_ptr<uvw::TCPHandle> client = srv.loop().resource<uvw::TCPHandle>();

		client->on<uvw::CloseEvent>([ptr = srv.shared_from_this()](const uvw::CloseEvent&, uvw::TCPHandle&) { ptr->close(); });
		client->on<uvw::EndEvent>([](const uvw::EndEvent&, uvw::TCPHandle& client) { client.close(); });

		srv.accept(*client);
	});
	tcp->bind("127.0.0.1", 4242);
	tcp->listen();
}

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

int main(int argc, char* argv[]) {
	//If this is a server
	std::string status = argv[1];
	if (status == "server") {
		Server srv("127.0.0.1", 4242);
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
}