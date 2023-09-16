#include "AsioSession.h"
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <iostream>

AsioSession::AsioSession(const boost::asio::any_io_executor& ioContext)
	: socket(ioContext)
{
	receiveBuffer.InitPointer();
}

AsioSession::AsioSession(boost::asio::io_service& io)
	: socket(io)
{
	receiveBuffer.InitPointer();
}

AsioSession::~AsioSession()
{
}

boost::asio::ip::tcp::socket& AsioSession::GetSocket()
{
	return socket;
}

void AsioSession::StartReceive()
{
	socket.async_read_some(boost::asio::buffer(receiveBuffer.GetBufferPtr(), receiveBuffer.GetNotBrokenPutSize())
		, boost::bind(&AsioSession::OnReceive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void AsioSession::StartSend()
{
}

void AsioSession::OnReceive(const boost::system::error_code& errorCode, size_t transferred)
{
	if (errorCode)
	{
		if (errorCode != boost::asio::error::eof)
		{
			std::cout << "OnReceive() : " << errorCode.message() << std::endl;

		}

		return;
	}

	// Callback OnMessage();

	StartReceive();
}

void AsioSession::OnSend(const boost::system::error_code& errorCode, size_t transferred)
{
	UNREFERENCED_PARAMETER(errorCode);
	UNREFERENCED_PARAMETER(transferred);
}