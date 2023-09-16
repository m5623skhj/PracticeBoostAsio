#include "AsioSession.h"
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include "SerializationBuffer.h"

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

void AsioSession::Receive()
{
	socket.async_read_some(boost::asio::buffer(receiveBuffer.GetBufferPtr(), receiveBuffer.GetNotBrokenPutSize())
		, boost::bind(&AsioSession::OnReceive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void AsioSession::Send(std::shared_ptr<CSerializationBuffer> packet)
{
	if (packet == nullptr)
	{
		return;
	}

	auto packetFront = packet->GetBufferPtr();
	WORD packetSize = packet->GetUseSize();
	memset(packetFront, packetSize, HEADER_SIZE);

	socket.async_write_some(boost::asio::buffer(packetFront, packetSize + HEADER_SIZE)
		, boost::bind(&AsioSession::OnSend, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, packet));
}

void AsioSession::OnReceive(const boost::system::error_code& errorCode, size_t transferred)
{
	if (errorCode)
	{
		if (errorCode != boost::asio::error::eof)
		{
			std::cout << "Error in OnReceive() : " << errorCode.message() << std::endl;

		}

		return;
	}

	// Callback OnReceiveMessage();

	Receive();
}

void AsioSession::OnSend(const boost::system::error_code& errorCode, size_t transferred, std::shared_ptr<CSerializationBuffer> packet)
{
	if (errorCode)
	{
		if (errorCode != boost::asio::error::eof)
		{
			std::cout << "Error in OnReceive() : " << errorCode.message() << std::endl;

		}

		return;
	}
	
	// Callback OnSendMessage();
}