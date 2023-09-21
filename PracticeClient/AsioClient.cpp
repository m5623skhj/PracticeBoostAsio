#include "AsioClient.h"
#include "SerializationBuffer.h"
#include <boost/bind.hpp>
#include <iostream>

AsioClient::AsioClient(boost::asio::io_service& inIO)
	: io(inIO)
	, socket(inIO)
{

}

AsioClient::~AsioClient()
{

}

void AsioClient::Connect(boost::asio::ip::tcp::endpoint& endPoint)
{
	socket.async_connect(endPoint,
		boost::bind(&AsioClient::OnConnect, this, boost::asio::placeholders::error));
}

void AsioClient::OnConnect(const boost::system::error_code& errorCode)
{
	if (errorCode)
	{
		if (errorCode != boost::asio::error::eof)
		{
			std::cout << "Error in OnReceive() : " << errorCode.message() << std::endl;
		}

		return;
	}

	isConnected = true;
}

void AsioClient::Receive()
{
	socket.async_read_some(boost::asio::buffer(receiveBuffer.GetBufferPtr(), receiveBuffer.GetNotBrokenPutSize())
		, boost::bind(&AsioClient::OnReceive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void AsioClient::Send(CSerializationBuffer& packet)
{
	auto packetFront = packet.GetBufferPtr();
	WORD packetSize = packet.GetUseSize();
	memset(packetFront, packetSize, HEADER_SIZE);

	socket.async_write_some(boost::asio::buffer(packetFront, packetSize + HEADER_SIZE)
		, boost::bind(&AsioClient::OnSend, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, packet));
}

void AsioClient::OnReceive(const boost::system::error_code& errorCode, size_t transferred)
{
	if (errorCode)
	{
		if (errorCode != boost::asio::error::eof)
		{
			std::cout << "Error in OnReceive() : " << errorCode.message() << std::endl;
		}

		return;
	}

	while (true)
	{
		WORD packetSize;
		receiveBuffer.Peek((char*)(&packetSize), sizeof(packetSize));
		if (packetSize < receiveBuffer.GetUseSize())
		{
			break;
		}

		CSerializationBuffer& packet = *CSerializationBuffer::Alloc();
		receiveBuffer.Dequeue(packet.GetBufferPtr(), packetSize);

		PacketHandle(packet);
	}

	Receive();
}

void AsioClient::OnSend(const boost::system::error_code& errorCode, size_t transferred, CSerializationBuffer& packet)
{
	if (errorCode)
	{
		if (errorCode != boost::asio::error::eof)
		{
			std::cout << "Error in OnReceive() : " << errorCode.message() << std::endl;

		}

		return;
	}

	CSerializationBuffer::Free(&packet);
}