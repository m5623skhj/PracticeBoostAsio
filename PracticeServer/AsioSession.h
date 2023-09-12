#pragma once
#include <boost/asio.hpp>

class AsioSession
{
public:
	AsioSession() = delete;
	AsioSession(const boost::asio::any_io_executor& ioContext);
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