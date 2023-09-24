#include "Player.h"
#include "../Protocol.h"
#include <iostream>
#include "SerializationBuffer.h"

Player::Player(AsioSession& inOwner)
	: owner(inOwner)
{

}

Player::~Player()
{

}

void Player::OnReceivePacket(CSerializationBuffer& receivedPacket)
{
	if (receivedPacket.GetUseSize() > sizeof(WORD))
	{
		std::cout << "Packet size is smaller than packet type size" << std::endl;
		return;
	}

	WORD packetId;
	receivedPacket >> packetId;

	switch (packetId)
	{
	case ProtocolId::C2S_Message:
		C2S_Message(receivedPacket);
		break;

	default:
		std::cout << "Invalid packet id : " << packetId << std::endl;
		break;
	}
}

void Player::OnSendPacket()
{

}