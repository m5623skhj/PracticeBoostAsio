#pragma once
#include <memory>
#include <map>
#include <boost/asio.hpp>

#define PORT 10001

class AsioSession;

class AsioServer
{
public:
	AsioServer() = delete;
	AsioServer(boost::asio::io_service& inIO);
	virtual ~AsioServer();

private:
	std::map<unsigned long long, std::shared_ptr<AsioSession>> sessionList;

#pragma region Asio
private:
	boost::asio::ip::tcp::acceptor acceptor;
	boost::asio::ip::tcp::endpoint endPoint;
#pragma endregion Asio

#pragma region Accept
private:
	void Accept();
	void OnAccept(std::shared_ptr<AsioSession> session);
#pragma endregion Accept

private:
	UINT64 sessionIndex = 0;
};