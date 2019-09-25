#pragma once
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class Connection
	: public std::enable_shared_from_this<Connection>
{
public:
	using handler = std::shared_ptr<Connection>;

	Connection(boost::asio::io_context& ioContext);

	static handler createConnection(boost::asio::io_context& ioContext);
	tcp::socket& getSocket();
	void sendMessage(std::string_view message);
	void startConnection();
	std::string getMessage() const { return message; }

private:
	void handleWrite(const boost::system::error_code&, size_t);
	void handleRead(const boost::system::error_code& error, size_t bytes);
	void startReading();

	tcp::socket socket;
	std::string message;
	boost::asio::streambuf buffer;
};