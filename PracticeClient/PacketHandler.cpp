#include "AsioClient.h"
#include "SerializationBuffer.h"
#include <iostream>

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
	default:
		std::cout << "Invalid packet id : " << packetId << std:: endl;
		break;
	}
}
