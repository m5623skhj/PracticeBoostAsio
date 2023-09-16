#include "AsioServer.h"
#include "AsioSession.h"
#include <boost/bind.hpp>
#include <iostream>

AsioServer::AsioServer(boost::asio::io_service& inIO)
	: endPoint(boost::asio::ip::tcp::v4(), PORT)
	, acceptor(inIO, endPoint)
{

}

AsioServer::~AsioServer()
{

}

void AsioServer::Accept()
{
    std::shared_ptr<AsioSession> newSession = std::make_shared<AsioSession>(acceptor.get_executor());
    acceptor.async_accept(newSession->GetSocket(), [this, newSession](const boost::system::error_code& error)
    {
        if (!error)
        {
            OnAccept(newSession);
        }
        else
        {
            std::cout << error.message() << std::endl;
        }
    });
}

void AsioServer::OnAccept(std::shared_ptr<AsioSession> session)
{
    session->StartReceive();
}
