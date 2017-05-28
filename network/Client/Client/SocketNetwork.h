#pragma once
#pragma comment(lib, "ws2_32")
#include "pch.h"
namespace MDNetwork
{
	enum class MyReturnVal
	{
		ResultOK = 1,
		ResultFail = 0,
		ResultSocketInitFail = -1,
		ResultSocketAllocFail = -2,
		ResultConnectError = -3,
		ResultConnectClosedRemotly = -4,
		ResultReciveError = -5,
		ResultNone = -6,
		ResultPacketIsBig = -7,
	};

	enum class State
	{
		Disconnect = 0,
		Connecting = 1,
		Connected = 2,
	};

	const int MaxPacketSize = 1024;
	const int BUFFERSIZE = 4096;

	using RawPacketPPLQue = concurrency::concurrent_queue<std::shared_ptr<char>>;
	using SendFunc = std::function<int(const short, const short, char*)>;

	class SocketNetwork
	{

	public:
		SocketNetwork() = default;
		~SocketNetwork();

		MyReturnVal Init();

		MyReturnVal Connect(const char* pAddr, const int pPort);

		RawPacketPPLQue* GetReceivedPacketQue();

		SendFunc GetSendFunc();

		MyReturnVal Release();

	private:

		int Send(const short packetId, const short dataSize, char* dataBody);

		State m_State{ State::Disconnect };

		SOCKET m_Sockfd = INVALID_SOCKET;

		RawPacketPPLQue m_RawPacketPPLQue;

		std::thread m_Thead;
		
		std::mutex m_Mutex;

		void ReceiveThreadFunc();

		int Recv(char* pBuffer);

		MyReturnVal AddRawPacketToQue(const char* pBuffer,const int pLen);

	};

}

