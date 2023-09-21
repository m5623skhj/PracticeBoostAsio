#pragma once
#include <boost/asio.hpp>
#include "Ringbuffer.h"

#define PORT 10001

class AsioClient
{
public:
	AsioClient() = delete;
	AsioClient(boost::asio::io_service& inIO);
	virtual ~AsioClient();

#pragma region Connect
public:
	void Connect(boost::asio::ip::tcp::endpoint& endPoint);

private:
	void OnConnect(const boost::system::error_code& errorCode);

private:
	bool isConnected = false;
#pragma endregion Connect

private:
	void Receive();
	void Send();
	void OnReceive();
	void OnSend();

private:
	boost::asio::io_service& io;
	boost::asio::ip::tcp::socket socket;

private:
	CRingbuffer receiveBuffer;
};