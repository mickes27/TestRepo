#include "Server.h"
#include <iostream>


int main()
{
	std::cout << "Gwiezdny Pyl MUD Server" << std::endl;
	try
	{
		boost::asio::io_context io_context;
		Server server(io_context);
		io_context.run();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}