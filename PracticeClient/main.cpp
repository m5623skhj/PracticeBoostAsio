#include "AsioClient.h"
#include <iostream>
#include <boost/thread.hpp>
#include "../Protocol.h"
#include "SerializationBuffer.h"
#include "../Protocol.h"

int main()
{
	boost::asio::io_service io;
	boost::asio::ip::tcp::endpoint endPoint(boost::asio::ip::address::from_string("127.0.0.1"), PORT);

	AsioClient client(io);
	client.Connect(endPoint);

	boost::thread t(boost::bind(&boost::asio::io_service::run, &io));

	char message[MAX_MESSAGE_SIZE];
	while (std::cin.getline(message, MAX_MESSAGE_SIZE))
	{
		if (client.IsConnected() == true)
		{
			CSerializationBuffer& sendBuffer = *CSerializationBuffer::Alloc();
			WORD protocolId = ProtocolId::C2S_Message;
			sendBuffer << protocolId;

			sendBuffer.WriteBuffer(message, MAX_MESSAGE_SIZE);
			client.Send(sendBuffer);
		}
	}

	t.join();
	return 0;
}