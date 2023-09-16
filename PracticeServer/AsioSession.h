#pragma once
#include <boost/asio.hpp>
#include "Ringbuffer.h"

class CSerializationBuffer;

class AsioSession
{
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

public:
	void Receive();
	void Send(std::shared_ptr<CSerializationBuffer> packet);

private:
	void OnReceive(const boost::system::error_code& errorCode, size_t transferred);
	void OnSend(const boost::system::error_code& errorCode, size_t transferred, std::shared_ptr<CSerializationBuffer> packet);

private:
	CRingbuffer receiveBuffer;
};