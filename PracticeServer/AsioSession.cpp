#include "AsioSession.h"
#include <boost/bind.hpp>

AsioSession::AsioSession(boost::asio::io_context& ioContext)
	: socket(ioContext)
{
}

AsioSession::~AsioSession()
{
}

boost::asio::ip::tcp::socket& AsioSession::GetSocket()
{
	return socket;
}

void AsioSession::OnReceive(const boost::system::error_code& errorCode, size_t transferred)
{
	UNREFERENCED_PARAMETER(errorCode);
	UNREFERENCED_PARAMETER(transferred);
}

void AsioSession::OnSend(const boost::system::error_code& errorCode, size_t transferred)
{
	UNREFERENCED_PARAMETER(errorCode);
	UNREFERENCED_PARAMETER(transferred);
}