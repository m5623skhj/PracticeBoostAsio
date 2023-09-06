// from https://www.boost.org/doc/libs/1_83_0/doc/html/boost_asio/tutorial.html

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/thread/thread.hpp>

using namespace std;

class Printer
{
public:
	Printer(boost::asio::io_context& io)
		: strand(boost::asio::make_strand(io))
		, timer1(io, boost::asio::chrono::seconds(1))
		, timer2(io, boost::asio::chrono::seconds(1))
		, count(0)
	{
		timer1.async_wait(boost::asio::bind_executor(strand, boost::bind(&Printer::Print_1, this)));
		timer2.async_wait(boost::asio::bind_executor(strand, boost::bind(&Printer::Print_2, this)));
	}

	~Printer()
	{
		cout << "cout is " << count << endl;
	}

	void Print_1()
	{
		if (count < 10)
		{
			cout << "Timer 1 : " << count << endl;
			++count;

			timer1.expires_at(timer1.expiry() + boost::asio::chrono::seconds(1));
			timer1.async_wait(boost::asio::bind_executor(strand, boost::bind(&Printer::Print_1, this)));
		}
	}

	void Print_2()
	{
		if (count < 10)
		{
			cout << "Timer 2 : " << count << endl;
			++count;

			timer2.expires_at(timer2.expiry() + boost::asio::chrono::seconds(1));
			timer2.async_wait(boost::asio::bind_executor(strand, boost::bind(&Printer::Print_2, this)));
		}
	}

private:
	boost::asio::strand<boost::asio::io_context::executor_type> strand;
	boost::asio::steady_timer timer1;
	boost::asio::steady_timer timer2;

	int count;
};

int main()
{
	boost::asio::io_context io;
	Printer printer(io);
	boost::thread thread(boost::bind(&boost::asio::io_context::run, &io));
	io.run();

	thread.join();

	return 0;
}