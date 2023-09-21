#pragma once
#include <boost/asio.hpp>
#include "Ringbuffer.h"
#include "Player.h"

class CSerializationBuffer;
class AsioServer;

class AsioSession
{
	friend AsioServer;

public:
	AsioSession() = delete;
	AsioSession(const boost::asio::any_io_executor& ioContext);
	AsioSession(boost::asio::io_service& io);
	virtual ~AsioSession();

#pragma region Asio
private:
	boost::asio::ip::tcp::socket socket;
#pragma endregion Asio

public:
	boost::asio::ip::tcp::socket& GetSocket();

private:
	void Receive();
	void Send(CSerializationBuffer& packet);
	void OnReceive(const boost::system::error_code& errorCode, size_t transferred);
	void OnSend(const boost::system::error_code& errorCode, size_t transferred, CSerializationBuffer& packet);

private:
	CRingbuffer receiveBuffer;

#pragma region PlayerObject
private:
	Player playerobject;
#pragma endregion PlayerObject
};