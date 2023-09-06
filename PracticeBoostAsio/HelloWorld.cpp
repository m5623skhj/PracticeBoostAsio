// from https://www.boost.org/doc/libs/1_83_0/doc/html/boost_asio/tutorial.html

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>

using namespace std;

void Print(const boost::system::error_code& error)
{
	UNREFERENCED_PARAMETER(error);

	cout << "Hello world" << endl;
}

void Print(const boost::system::error_code& error, boost::asio::steady_timer* timer, int& count)
{
	if (count < 5)
	{
		cout << count << endl;
		++count;

		timer->expires_at(timer->expiry() + boost::asio::chrono::seconds(1));
		timer->async_wait(boost::bind(Print, boost::asio::placeholders::error, timer, count));
	}
}

class Printer
{
public:
	Printer(boost::asio::io_context& io)
		: timer(io, boost::asio::chrono::seconds(1)),
		count(0)
	{
		timer.async_wait(boost::bind(&Printer::Print, this));
	}

	~Printer()
	{
		cout << "count is " << count << endl;
	}

	void Print()
	{
		if (count < 5)
		{
			std::cout << count << std::endl;
			++count;

			timer.expires_at(timer.expiry() + boost::asio::chrono::seconds(1));
			timer.async_wait(boost::bind(&Printer::Print, this));
		}
	}

private:
	boost::asio::steady_timer timer;
	int count;
};

int main()
{
	boost::asio::io_context io;

	boost::asio::steady_timer timer(io, boost::asio::chrono::seconds(5));
	/*
	timer.wait();

	cout << "Hello world" << endl;
	*/

	/*
	timer.async_wait(&Print);
	cout << "asdf" << endl;

	io.run();
	*/

	/*
	int count = 0;
	timer.async_wait(boost::bind(Print, boost::asio::placeholders::error, &timer, count));
	
	io.run();

	cout << "count is " << count << endl;
	*/

	/*
	Printer printer(io);
	io.run();
	*/

	return 0;
}

