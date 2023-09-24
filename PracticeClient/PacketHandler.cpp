#include "AsioClient.h"
#include "SerializationBuffer.h"
#include <iostream>
#include "../Protocol.h"

void AsioClient::PacketHandle(CSerializationBuffer& packet)
{
	if (packet.GetUseSize() > sizeof(WORD))
	{
		std::cout << "Packet size is smaller than packet type size" << std::endl;
		return;
	}

	WORD packetId;
	packet >> packetId;

	switch (packetId)
	{
	case ProtocolId::S2C_Message:
		C2S_Message(packet);
		break;

	default:
		std::cout << "Invalid packet id : " << packetId << std:: endl;
		break;
	}
}

void AsioClient::C2S_Message(CSerializationBuffer& packet)
{
	char message[MAX_MESSAGE_SIZE];
	packet.ReadBuffer(message, packet.GetUseSize());

	std::cout << message << std::endl;
}