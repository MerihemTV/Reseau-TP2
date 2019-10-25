#include "server.hpp"

void Server::listenServer(uvw::Loop& loop) {
	std::shared_ptr<uvw::TCPHandle> tcp = loop.resource<uvw::TCPHandle>();

	tcp->on<uvw::ListenEvent>([tcp,this](const uvw::ListenEvent&, uvw::TCPHandle& srv) {
		std::shared_ptr<uvw::TCPHandle> client = srv.loop().resource<uvw::TCPHandle>();
		std::cout << "New connection" << std::endl;

		client->on<uvw::CloseEvent>([ptr = srv.shared_from_this()](const uvw::CloseEvent&, uvw::TCPHandle&) { 
			ptr->close();
		});
		client->on<uvw::EndEvent>([tcp](const uvw::EndEvent&, uvw::TCPHandle& client) { 
			client.close(); 
		});
		client->on<uvw::DataEvent>([](const uvw::DataEvent&, uvw::TCPHandle&) {
			std::cout << "Data received" << std::endl; 
		});

		srv.accept(*client);
		client->read();
		clients.push_back(client);

		/*
		uint8_t data[] = { 4 };
		Send(data, sizeof(data));
		*/
	});

	tcp->bind(m_addr, m_port);
	tcp->listen();
}

void Server::runner() {
	loop->run();
}

Server::Server(std::string addr, int port) {
	m_addr = addr;
	m_port = port;
	loop = uvw::Loop::getDefault();
	listenServer(*loop);
	loopThread = std::make_unique<std::thread>(&Server::runner, this);
}

Server::~Server() {
	if (loopThread->joinable()) {
		loopThread->join();
	}
}

void Server::Send(uint8_t* data, int data_size){
	std::cout << "Sending data" << std::endl;
	std::for_each(clients.begin(), clients.end(), [data, data_size](auto cl) {
		cl->write(reinterpret_cast<char*>(data), data_size); });
}
