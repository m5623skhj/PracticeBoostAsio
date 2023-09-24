#include "AsioClient.h"

int main()
{
	boost::asio::io_service io;
	boost::asio::ip::tcp::endpoint endPoint(boost::asio::ip::address::from_string("127.0.0.1"), PORT);

	AsioClient client(io);
	client.Connect(endPoint);

	io.run();

	return 0;
}