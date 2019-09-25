#pragma once
#include "Player.h"
#include <thread>

class Server
{
public:
	Server(boost::asio::io_context& ioContext);
	~Server();
	void mainLoop();
private:
	void startAccepting();
	void handleNewConnection(Connection::handler newConnection, const boost::system::error_code& error);

	boost::asio::io_context& ioContext;
	tcp::acceptor acceptor;
	std::vector<Player> playersSet;
	bool isRunning;
	std::thread mainLoopThread;
};
