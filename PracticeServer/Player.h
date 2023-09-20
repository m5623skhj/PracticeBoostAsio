#pragma once

class AsioSession;
class CSerializationBuffer;

class Player
{
	friend AsioSession;

public:
	Player();
	virtual ~Player();

private:
	void OnReceivePacket(CSerializationBuffer& receivedPacket);
	void OnSendPacket();
};