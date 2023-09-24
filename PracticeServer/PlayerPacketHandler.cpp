#include "Player.h"
#include "SerializationBuffer.h"
#include "../Protocol.h"
#include "AsioSession.h"

void Player::C2S_Message(CSerializationBuffer& packet)
{
	char message[MAX_MESSAGE_SIZE];
	packet.ReadBuffer(message, packet.GetUseSize());

	CSerializationBuffer& sendBuffer = *CSerializationBuffer::Alloc();
	WORD protocolId = S2C_Message;
	sendBuffer << protocolId;
	sendBuffer.WriteBuffer(message, sizeof(MAX_MESSAGE_SIZE));

	owner.Send(sendBuffer);
}