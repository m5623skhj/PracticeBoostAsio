#include "AsioServer.h"
#include "AsioSession.h"
#include <boost/bind.hpp>
#include <iostream>
#include <thread>

AsioServer::AsioServer(boost::asio::io_service& inIO)
	: acceptor(inIO, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), PORT))
{
    for (int i = 0; i < MAX_SESSION_SIZE; ++i)
    {
        sessionQueue.push(std::make_shared<AsioSession>(inIO));
    }

    Accept();
    StartWorkerThreads(inIO);
}

AsioServer::~AsioServer()
{

}

void AsioServer::OnCloseSession(UINT64 sessionId)
{
    auto session = connectedSessionList.find(sessionId);
    if (session == connectedSessionList.end())
    {
        return;
    }

    sessionQueue.push(session->second);

    if (isAccepting == false)
    {
        isAccepting = true;
        Accept();
    }
}

void AsioServer::Accept()
{
    if (sessionQueue.empty() == true)
    {
        isAccepting = false;
        return;
    }

    std::shared_ptr<AsioSession> newSession = sessionQueue.front();
    sessionQueue.pop();

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
    session->Receive();
}

int AsioServer::GetCoreCount()
{
    SYSTEM_INFO systemInfo;
    GetSystemInfo(&systemInfo);

    return static_cast<int>(systemInfo.dwNumberOfProcessors * 2);
}

void AsioServer::StartWorkerThreads(boost::asio::io_service& io)
{
    int coreCount = GetCoreCount();
    for (int i = 0; i < coreCount; ++i)
    {
        workerThreadList.push_back(std::make_shared<std::thread>([&io]
            {
                io.run();
            }));
    }

    while (stopThread == false)
    {
        Sleep(1000);
    }

    for (auto& thread : workerThreadList)
    {
        thread->join();
    }
    workerThreadList.clear();
}