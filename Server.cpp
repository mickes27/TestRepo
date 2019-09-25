#include "Server.h"
#include <boost/bind.hpp>
#include <utility>
#include "Config.h"
#include <iostream>

Server::Server(boost::asio::io_context& ioContext) : 
	ioContext(ioContext),
	acceptor(ioContext, tcp::endpoint(tcp::v4(), Config::serverPort)),
	isRunning(false)
{
	startAccepting();

	mainLoopThread = std::thread(&Server::mainLoop, this);
}

Server::~Server()
{
	mainLoopThread.join();
}

void Server::mainLoop()
{
	std::cout << "Starting loop" << std::endl;
	isRunning = true;
	while (isRunning) {
		std::for_each(playersSet.begin(), playersSet.end(), [](Player player)
		{
			player.processPlayer();
		});

		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}

void Server::startAccepting()
{
	std::cout << "Check" << std::endl;
	Connection::handler newConnection = Connection::createConnection(ioContext);

	acceptor.async_accept(newConnection->getSocket(),
	               boost::bind(&Server::handleNewConnection, this, newConnection,
	                      boost::asio::placeholders::error));
}

void Server::handleNewConnection(Connection::handler newConnection, const boost::system::error_code& error)
{
	if (!error) {
		const Player newPlayer(std::move(newConnection));
		playersSet.push_back(newPlayer);
	}

	startAccepting();
}
