#include "Connection.h"
#include "Messages.h"
#include <iostream>
#include <boost/bind.hpp>


Connection::Connection(boost::asio::io_context& ioContext) : 
	socket(ioContext)
{
}

Connection::handler Connection::createConnection(boost::asio::io_context& ioContext)
{
	return std::make_shared<Connection>(ioContext);
}

tcp::socket& Connection::getSocket()
{
	return socket;
}

void Connection::sendMessage(std::string_view message)
{
	boost::asio::async_write(socket, boost::asio::buffer(message),
	                  boost::bind(&Connection::handleWrite, shared_from_this(),
	                         boost::asio::placeholders::error,
	                         boost::asio::placeholders::bytes_transferred));
}

void Connection::startReading()
{
	boost::asio::async_read_until(socket, buffer, "\r\n",
		                   boost::bind(&Connection::handleRead, shared_from_this(),
			                      boost::asio::placeholders::error,
			                      boost::asio::placeholders::bytes_transferred));
}

void Connection::startConnection()
{
	sendMessage(Messages::welcomeMessage);
	startReading();
}

void Connection::handleWrite(const boost::system::error_code&, size_t)
{
}

void Connection::handleRead(const boost::system::error_code& error, size_t bytes)
{
	if (!error)
	{
		std::istream is(&buffer);
		std::string line;
		std::getline(is, line);
		message = line;
	}

	startReading();
}
