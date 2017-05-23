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

	//패킷의 크기를 1바이트 단위크기로 만들수있게 하기 위한 것
	//이게 없으면 버스의 효율을 위해서 기본크기가 버스가 한번에
	//읽을수 있는 크기로 변한다.


	class SocketNetwork
	{

	public:
		SocketNetwork() = default;
		~SocketNetwork();

		MyReturnVal Init();

		MyReturnVal Connect(const char* pAddr, const int pPort);

		int Send(const short packetId, const short dataSize, char* dataBody);

		auto GetReceivedPacketQue();

		auto GetSendFunc();

		MyReturnVal Release();

	private:
		

		State m_State{ State::Disconnect };

		SOCKET m_Sockfd = INVALID_SOCKET;

		concurrency::concurrent_queue<std::shared_ptr<char>> m_RawPacketPPLQue;

		std::thread m_Thead;
		
		std::mutex m_Mutex;

		void ReceiveThreadFunc();

		int Recv(char* pBuffer);

		MyReturnVal AddRawPacketToQue(const char* pBuffer,const int pLen);

	};

}

