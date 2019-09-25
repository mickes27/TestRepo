#pragma once
#include "Connection.h"

class Player
{
public:
	using handler = std::shared_ptr<Connection>;

	enum class ConnectionState
	{
		Login,
		InGame
	};

	Player(Connection::handler connection);
	void processPlayer();

private:
	void processState();

	Connection::handler connection;
	ConnectionState connectionState;
};

