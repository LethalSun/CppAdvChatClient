#pragma once
#pragma once
#pragma comment(lib, "ws2_32")
#include <iostream>
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <thread>
#include <mutex>
#include <deque>
#include <concurrent_queue.h>
#include <algorithm>
#include "Util.h"
#include "Packet.h"
#include "PacketID.h"
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
#pragma pack(push,1)

	struct PacketHeder
	{
		short Id;
		short BodySize;
	};

	const int PACKET_HEADER_SIZE = sizeof(PacketHeder);

	struct PacketBody
	{
		PacketBody() = default;

		short PacketId = 0;
		short PacketBodySize = 0;
		char* PacketData = nullptr;
	};
#pragma pack(pop)


	class SocketNetwork
	{

	public:
		SocketNetwork() = default;
		~SocketNetwork();

		MyReturnVal Init();

		MyReturnVal Connect(const char* pAddr, const int pPort);

		int Send(const short packetId, const short dataSize, char* dataBody);

		MyReturnVal Release()
		{
			//소켓을 닫는다
			closesocket(m_Sockfd);
			//윈도우 소켓 리소스를 반환한다.
			WSACleanup();

			return MyReturnVal::ResultOK;
		}
	private:
		

		State m_State{ State::Disconnect };

		SOCKET m_Sockfd = INVALID_SOCKET;

		concurrency::concurrent_queue<char*> m_RawPacketPPLQue;

		std::thread m_Thead;
		
		std::mutex m_Mutex;

		void ReceiveThreadFunc();

		int Recv(char* pBuffer);

		MyReturnVal AddRawPacketToQue(const char* pBuffer,const int pLen);

	};

}

