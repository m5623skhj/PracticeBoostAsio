#include <boost/asio.hpp>
#include "AsioServer.h"

int main()
{
	boost::asio::io_service io;
	AsioServer server(io);

	io.run();

	return 0;
}