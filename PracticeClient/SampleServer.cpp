#include <boost/asio.hpp>
#include <iostream>
#include <memory>

using namespace boost::asio;
using namespace std;

class Server {
public:
    Server(io_context& io, const ip::tcp::endpoint& inEndPoint)
        : acceptor(io, inEndPoint)
    {
        StartAccept();
    }

private:
    void StartAccept() 
    {
        shared_ptr<ip::tcp::socket> socket(new ip::tcp::socket(acceptor.get_executor()));
        acceptor.async_accept(*socket, 
            [this, socket](const boost::system::error_code& errorCode) 
        {
            if (errorCode.failed() == false)
            {
                cout << "Accepted a connection" << endl;
                StartRead(socket);
            }

            StartAccept();
        });
    }

    void StartRead(shared_ptr<ip::tcp::socket> socket) 
    {
        async_read(*socket, buffer(data, sizeof(data)), 
            [this, socket](const boost::system::error_code& errorCode, size_t transffered)
        {
            if (errorCode.failed() == false)
            {
                StartWrite(socket, transffered);
            }
        });
    }

    void StartWrite(shared_ptr<ip::tcp::socket> socket, size_t length) 
    {
        async_write(*socket, buffer(data, length), 
            [this, socket](const boost::system::error_code& errorCode, size_t transffered)
        {
            UNREFERENCED_PARAMETER(transffered);
            if (errorCode.failed() == false)
            {
                StartRead(socket);
            }
        });
    }

private:
    ip::tcp::acceptor acceptor;
    char data[1024];
};

int main() 
{
    io_context io;
    Server server(io, ip::tcp::endpoint(ip::tcp::v4(), 10001));

    io.run();

    return 0;
}
