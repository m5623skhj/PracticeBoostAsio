#pragma once
#include <memory>
#include <map>
#include <boost/asio.hpp>
#include <queue>
#include <vector>

#define PORT 10001
#define MAX_SESSION_SIZE 500

class AsioSession;
class std::thread;

class AsioServer
{
public:
	AsioServer() = delete;
	AsioServer(boost::asio::io_service& inIO);
	virtual ~AsioServer();

#pragma region session
private:
	std::map<UINT64, std::shared_ptr<AsioSession>> connectedSessionList;
	std::queue<std::shared_ptr<AsioSession>> sessionQueue;

	bool isAccepting = true;
#pragma endregion session

#pragma region Asio
private:
	boost::asio::ip::tcp::acceptor acceptor;
	boost::asio::ip::tcp::endpoint endPoint;
#pragma endregion Asio

public:
	void OnCloseSession(UINT64 sessionId);

private:
	void Accept();
	void OnAccept(std::shared_ptr<AsioSession> session);

#pragma region thread
private:
	int GetCoreCount();
	void StartWorkerThreads(boost::asio::io_service& io);

private:
	std::vector<std::shared_ptr<std::thread>> workerThreadList;
	bool stopThread = false;
#pragma endregion thread

private:
	UINT64 sessionIndex = 0;
};