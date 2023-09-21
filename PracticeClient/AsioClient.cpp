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

}

void AsioClient::Send()
{

}

void AsioClient::OnReceive()
{

}

void AsioClient::OnSend()
{

}