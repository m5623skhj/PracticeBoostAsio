#pragma once
#include <boost/asio.hpp>

class AsioSession
{
public:
	AsioSession() = delete;
	AsioSession(boost::asio::io_context& ioContext);
	virtual ~AsioSession();

#pragma region Asio
private:
	boost::asio::ip::tcp::socket socket;
#pragma endregion Asio

public:
	boost::asio::ip::tcp::socket& GetSocket();

private:
	void OnReceive(const boost::system::error_code& errorCode, size_t transferred);
	void OnSend(const boost::system::error_code& errorCode, size_t transferred);
};