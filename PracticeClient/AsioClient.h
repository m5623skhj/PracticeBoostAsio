#pragma once
#include <boost/asio.hpp>
#include "Ringbuffer.h"

#define PORT 10001

class CSerializationBuffer;

class AsioClient
{
public:
	AsioClient() = delete;
	AsioClient(boost::asio::io_service& inIO);
	virtual ~AsioClient();

#pragma region Connect
public:
	void Connect(boost::asio::ip::tcp::endpoint& endPoint);
	bool IsConnected() { return isConnected; }

private:
	void OnConnect(const boost::system::error_code& errorCode);

private:
	bool isConnected = false;
#pragma endregion Connect

public:
	void PacketHandle(CSerializationBuffer& packet);

public:
	void Send(CSerializationBuffer& packet);

private:
	void Receive();
	void OnReceive(const boost::system::error_code& errorCode, size_t transferred);
	void OnSend(const boost::system::error_code& errorCode, size_t transferred, CSerializationBuffer& packet);

private:
	boost::asio::io_service& io;
	boost::asio::ip::tcp::socket socket;

private:
	CRingbuffer receiveBuffer;

#pragma region PacketHandle
private:
	void C2S_Message(CSerializationBuffer& packet);
#pragma endregion PacketHandle
};