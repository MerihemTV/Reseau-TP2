#include "server.hpp"


void Server::listen(uvw::Loop& loop) {
	std::shared_ptr<uvw::TCPHandle> tcp = loop.resource<uvw::TCPHandle>();

	tcp->on<uvw::ListenEvent>([this,tcp](const uvw::ListenEvent&, uvw::TCPHandle& srv) {
		std::cout << "New Connection" << std::endl;
		std::shared_ptr<uvw::TCPHandle> client = srv.loop().resource<uvw::TCPHandle>();
		clients.push_back(client);
		client->on<uvw::CloseEvent>([ptr = srv.shared_from_this()](const uvw::CloseEvent&, uvw::TCPHandle& client) { ptr->close();  });
		client->on<uvw::EndEvent>([this](const uvw::EndEvent&, uvw::TCPHandle& client) {
			auto cl = std::find(clients.begin(), clients.end(), client.shared_from_this());
			clients.erase(cl); 
			client.close(); });
		srv.accept(*client);
	});
	tcp->bind(m_addr, m_port);
	tcp->listen();
}

Server::Server(std::string add , int port) {
	m_addr = add;
	m_port = port;
	auto loop = uvw::Loop::getDefault();
	listen(*loop);
	loop->run();
}

void Server::Send(uint8_t* data, int data_size) {
	std::for_each(clients.begin(), clients.end(), [data, data_size](auto cl) { 
		cl->write(reinterpret_cast<char*> (data), data_size); });
}