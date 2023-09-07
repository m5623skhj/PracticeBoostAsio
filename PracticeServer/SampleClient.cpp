#include <boost/asio.hpp>
#include <iostream>

using namespace boost::asio;
using namespace std;

void OnConnected(const boost::system::error_code& errorCode)
{
	if (errorCode.failed() == true)
	{
		cout << "Connect failed " << errorCode.message() << endl;
		return;
	}

	cout << "Connect success" << endl;
}

int main()
{
	io_service io;
	ip::tcp::endpoint endPoint(ip::address::from_string("127.0.0.1"), 10001);
	ip::tcp::socket socket(io);

	/* ����
	socket.connect(endPoint);
	//*/

	//* �񵿱�
	socket.async_connect(endPoint, OnConnected);
	io.run();
	//*/

	while (1);

	return 0;
}