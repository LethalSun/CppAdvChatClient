#pragma once
#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <thread>
#include <mutex>
#include <deque>
#include "Util.h"
#include "Packet.h"
#include "PacketID.h"
namespace chatClient
{
	const int MaxPacketSize = 1024;

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

	enum class State
	{
		Disconnect = 0,
		Connecting = 1,
		Connected = 2,
	};

	class Network
	{
	public:
		Network() = default;

		~Network() = default;

		//윈속 초기화.
		int Init();

		//연결.
		bool Connect(const char*,const int);

		//매번 돌아가는 함수.
		int Update();

		int Send(const short, const short, char*);

		PacketBody GetPacket();

		int Release();

	private:
		State m_State{ State::Disconnect };

		SOCKET m_Sockfd = INVALID_SOCKET;
		
		std::deque<PacketBody> que;

		std::thread m_th;
		std::mutex m_Mutex;
		int Recv(char*);
		//TODO:받은 패킷을 후처리 하고 보낼패킷을 만드는 부분을 인터페이스로 옮긴다.
		int RecvProc(const char * ,const int);
		int AddPacketToQue(const short,const short,const char*);

		//
	};

}


