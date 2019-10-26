#include "server.hpp"

void Server::listenServer(uvw::Loop& loop) {
	std::shared_ptr<uvw::TCPHandle> tcp = loop.resource<uvw::TCPHandle>();

	tcp->on<uvw::ListenEvent>([tcp,this](const uvw::ListenEvent&, uvw::TCPHandle& srv) {
		std::shared_ptr<uvw::TCPHandle> client = srv.loop().resource<uvw::TCPHandle>();
		std::cout << "New connection" << std::endl;

		client->on<uvw::CloseEvent>([ptr = srv.shared_from_this()](const uvw::CloseEvent&, uvw::TCPHandle&) { 
			ptr->close();
		});
		client->on<uvw::EndEvent>([this](const uvw::EndEvent&, uvw::TCPHandle& client) { 

			auto cl = std::find(clients.begin(), clients.end(), client.shared_from_this());
			clients.erase(cl);
			client.close(); 
		});

		srv.accept(*client);
		client->read();
		clients.push_back(client);
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

void Server::Run()
{
	OutputStream os;
	std::vector<GameObject*> gameObjects;
	bool isRunning = true;

	while (isRunning)
	{
		std::string command;
		std::cin >> command;
		if (command == "init")
		{
			gameObjects.clear();
			gameObjects.push_back(new Player(-287.542f, 186.301f, 499.998f, "Adrien", -0.457f, 0.532f, 0.425f, -0.572f));
			gameObjects.push_back(new Player(410.2f, 2.321f, -102.54f, "Mehdi", 0.800f, -0.600f, 0.0f, 0.0f));
			gameObjects.push_back(new Player(-245.23f, 147.851f, -500.0f, "Laura", -0.742f, -0.241f, 0.542f, 0.312f));
			gameObjects.push_back(new Enemy(253.542f, 475.12f, -14.2f, "Spider", -0.5f, 0.5f, 0.7f, -0.1f));
			gameObjects.push_back(new Enemy(-53.637f, -356.12f, 145.52f, "Zombie", 0.342f, 0.682f, 0.623f, -0.172f));
			gameObjects.push_back(new Enemy(-212.212f, 198.235f, -497.54f, "Skeleton", 0.578f, -0.452f, 0.542f, -0.409f));
		}
		else if (command == "deleteTest")
		{
			gameObjects.erase(gameObjects.begin()+2);
		}
		else if (command == "send") PrepareAndSend(os, gameObjects);
		else if (command == "exit") isRunning = false;
	}
}

void Server::PrepareAndSend(OutputStream& os, std::vector<GameObject*>& gameObjects)
{
	os.Flush();
	ReplicationManager replicationManager = ReplicationManager::getInstance();
	replicationManager.Replicate(os, gameObjects);

	auto data = os.Data();
	uint8_t* dataToSend = NULL;
	int dataSize = data.size();
	dataToSend = new uint8_t[dataSize];

	for (int i = 0; i < dataSize; i++)
	{
		dataToSend[i] = static_cast<uint8_t>(data[i]);
	}
	Send(dataToSend, dataSize);
	delete[] dataToSend;
	dataToSend = NULL;
}