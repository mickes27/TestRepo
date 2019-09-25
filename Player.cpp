#include "Player.h"


Player::Player(Connection::handler connection) :
	connection(connection),
	connectionState(ConnectionState::Login)
{
	connection->startConnection();
}

void Player::processPlayer()
{
	//TODO: Finish processing - state, player input and commands
	processState();
}

void Player::processState()
{
	if (connectionState == ConnectionState::Login) {
		connection->sendMessage("Musisz sie zalogowac!");
	}
}
