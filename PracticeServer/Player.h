#pragma once

class AsioSession;
class CSerializationBuffer;

class Player
{
	friend AsioSession;

public:
	Player() = delete;
	Player(AsioSession& owner);
	virtual ~Player();

private:
	void OnReceivePacket(CSerializationBuffer& receivedPacket);
	void OnSendPacket();

private:
	AsioSession& owner;

#pragma region Protocol
private:
	void C2S_Message(CSerializationBuffer& packet);
#pragma endregion Protocol
};