#include "Network.h"

const char* SERVERRIP = "127.0.0.1";
const int SERVERPORT = 23452;
const int BUFFERSIZE = 4096;
namespace chatClient
{
	//윈속초기화와 소켓 할당.
	int Network::Init()
	{
		//윈속의 버전을 체크 지정한다.MAKEWORD는 두개의 값을 워드로 만들어 주는것.
		WORD wVersionRequested = MAKEWORD(2, 2);
		//초기화 된 윈도우 소켓의 상태를 저장하는 변수.
		WSADATA wsaData;

		//인자로 전달된 윈도우 소켓 버전으로 윈도우 소켓 DLL을 초기화 하는곳.
		auto returnVal = WSAStartup(wVersionRequested, &wsaData);

		//윈도우 소켓 초기화는 성공하면 0을 반환한다.
		if (returnVal != 0)
		{
			return -1;
		}

		//통신이 가능하도록 리소스를 할당하고 그 리소스를 사용할수 있는 소켓디스크립터 SOCKET 을 반환 한다.
		//각각 주소체계 소켓 타입 프로토콜을 지정한다, TCP는 소켓 스트림 udp는 소켓 디그램(데이터 그램)을 선택한다.
		m_Sockfd = socket(AF_INET, SOCK_STREAM, 0);
		if (m_Sockfd == INVALID_SOCKET)
		{
			return -2;
		}


		return 0;
	}

	bool Network::Connect(const char* pAddr, const int pPort)
	{
		//SOCKADDR 소켓 주소 구조체, SOCKADDR_IN은 TCP/IP에서 사용되는 소켓 주소 구조체 물론 UDP에서도 사용
		SOCKADDR_IN serverAddr;
		serverAddr.sin_family = AF_INET;
		serverAddr.sin_port = htons(SERVERPORT);//TODO: pPort
		serverAddr.sin_addr.s_addr = inet_addr(SERVERRIP);//TODO: pAddr //지금 32비트 공용체인데 IPv6는 어떻게 하지?

		auto returnVal = connect(m_Sockfd, (SOCKADDR*)&serverAddr, sizeof(serverAddr));

		if (returnVal == SOCKET_ERROR)
		{
			return false;
		}

		m_State = State::Connected;

		m_th = std::thread([this]() { Update(); });

		return true;
	}

	int Network::Update()
	{
		auto returnVal = 0;

		while (true)
		{
			char RecvBuffer[BUFFERSIZE];

			auto length = Recv(RecvBuffer);

			if (length == 0)
			{
				returnVal = length;
				break;
			}

			if (length < 0)
			{
				returnVal = length;
				break;
			}

			RecvProc(RecvBuffer, length);
		}


		return returnVal;
	}

	int Network::Release()
	{
		//소켓을 닫는다
		closesocket(m_Sockfd);
		//윈도우 소켓 리소스를 반환한다.
		WSACleanup();


		return 0;
	}

	int Network::Send(const short packetId, const short dataSize, char* dataBody)
	{
		auto returnVal = 0;
		char data[MaxPacketSize] = { 0 };
		PacketHeder header{ packetId,dataSize };

		if (packetId == 31)
		{
			int a = 0;
		}
		memcpy(&data[0], (char*)&header, sizeof(header));

		if (dataSize != 0)
		{
			memcpy(&data[PACKET_HEADER_SIZE], (char*)dataBody, dataSize);
		}

		returnVal = send(m_Sockfd, data, dataSize + sizeof(header), 0);

		return returnVal;
	}

	PacketBody Network::GetPacket()
	{
		std::lock_guard<std::mutex> guard(m_Mutex);
		if (que.empty())
		{
			return PacketBody();
		}

		auto packet = que.front();

		if (packet.PacketId == 32)
		{
			int a = 0;
		}
		que.pop_front();

		return packet;
	}

	int Network::Recv(char* pBuffer)
	{
		int receivedLen;

		receivedLen = recv(m_Sockfd, pBuffer, BUFFERSIZE, 0);

		if (receivedLen == 0)
		{
			return 0;//연결 실패
		}

		if (receivedLen < 0)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				return -1;//WSAEWOULDBLOCK Error!
			}
		}

		return receivedLen;
	}

	int Network::RecvProc(const char * pBuffer, const int pReceivedLen)
	{
		auto readPos = 0;
		const auto dataSize = pReceivedLen;
		PacketHeder* pPacketHeader;

		while (dataSize - readPos > PACKET_HEADER_SIZE)//오버플로우는 없다고 가정했으므로 아마 0인경우 나온다
		{
			pPacketHeader = (PacketHeder*)&pBuffer[readPos];
			auto id = pPacketHeader->Id;
			auto size = pPacketHeader->BodySize;
			readPos += PACKET_HEADER_SIZE;

			AddPacketToQue(id, size, &pBuffer[readPos]);

			readPos += size;
		}


		return 0;
	}

	int Network::AddPacketToQue(const short pId, const short pSize, const char * pData)
	{
		auto newPacket = PacketBody();
		newPacket.PacketId = pId;
		newPacket.PacketBodySize = pSize;
		newPacket.PacketData = new char[pSize];
		memcpy(newPacket.PacketData, pData, pSize);

		std::lock_guard<std::mutex> guard(m_Mutex);

		que.push_back(newPacket);

		return 0;
	}
}

