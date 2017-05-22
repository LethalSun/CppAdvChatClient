#include "SocketNetwork.h"


namespace MDNetwork
{
	SocketNetwork::~SocketNetwork()
	{
		Release();
	}

	MyReturnVal SocketNetwork::Init()
	{//윈속의 버전을 체크 지정한다.MAKEWORD는 두개의 값을 워드로 만들어 주는것.
		WORD wVersionRequested = MAKEWORD(2, 2);
		//초기화 된 윈도우 소켓의 상태를 저장하는 변수.
		WSADATA wsaData;

		//인자로 전달된 윈도우 소켓 버전으로 윈도우 소켓 DLL을 초기화 하는곳.
		auto returnVal = WSAStartup(wVersionRequested, &wsaData);

		//윈도우 소켓 초기화는 성공하면 0을 반환한다.
		if (returnVal !=0)
		{
			return MyReturnVal::ResultSocketInitFail;
		}

		//통신이 가능하도록 리소스를 할당하고 그 리소스를 사용할수 있는 소켓디스크립터 SOCKET 을 반환 한다.
		//각각 주소체계 소켓 타입 프로토콜을 지정한다, TCP는 소켓 스트림 udp는 소켓 디그램(데이터 그램)을 선택한다.
		m_Sockfd = socket(AF_INET, SOCK_STREAM, 0);
		if (m_Sockfd == INVALID_SOCKET)
		{
			return MyReturnVal::ResultSocketAllocFail;
		}


		return MyReturnVal::ResultOK;
	}

	MyReturnVal SocketNetwork::Connect(const char * pAddr, const int pPort)
	{	
		//SOCKADDR 소켓 주소 구조체, SOCKADDR_IN은 TCP/IP에서 사용되는 소켓 주소 구조체 물론 UDP에서도 사용
		SOCKADDR_IN serverAddr;
		serverAddr.sin_family = AF_INET;
		serverAddr.sin_port = htons(pPort);//포트 설정 리틀엔디안에서 빅엔디안드로 바꿈
		serverAddr.sin_addr.s_addr = inet_addr(pAddr); //지금 32비트 공용체인데 IPv6는 어떻게 하지?

		auto returnVal = connect(m_Sockfd, (SOCKADDR*)&serverAddr, sizeof(serverAddr));

		if (returnVal == SOCKET_ERROR)
		{
			return MyReturnVal::ResultConnectError;
		}

		m_State = State::Connected;

		m_Thead = std::thread([this]()	{  ReceiveThreadFunc(); });

		return MyReturnVal::ResultOK;
	}

	int SocketNetwork::Send(const short packetId, const short dataSize, char * dataBody)
	{
		auto returnVal = 0;
		char data[MaxPacketSize] = { 0 };
		PacketHeder header{ packetId,dataSize };

		memcpy(&data[0], (char*)&header, sizeof(header));

		if (dataSize != 0)
		{
			memcpy(&data[PACKET_HEADER_SIZE], (char*)dataBody, dataSize);
		}

		returnVal = send(m_Sockfd, data, dataSize + sizeof(header), 0);

		return returnVal;
	}

	auto SocketNetwork::GetReceivedPacketQue()
	{
		return &m_RawPacketPPLQue;
	}

	auto SocketNetwork::GetSendFunc()
	{
		return [this](const short packetId, const short dataSize, char* dataBody) 
		{
			Send(packetId, dataSize, dataBody);
		};
	}

	MyReturnVal SocketNetwork::Release()
	{
		//소켓을 닫는다
		closesocket(m_Sockfd);
		//윈도우 소켓 리소스를 반환한다.
		WSACleanup();

		return MyReturnVal::ResultOK;
	}

	void SocketNetwork::ReceiveThreadFunc()
	{

		while (true)
		{
			char RecvBuffer[BUFFERSIZE];

			//일단 리시브는 한번에 다받을수 있는 길이라고 가정한다.
			auto length = Recv(RecvBuffer);

			if (length == 0)
			{
				break;
			}

			if (length < 0)
			{
				/*
				ResultConnectClosedRemotly = -4,
				ResultReciveError = -5,
				ResultNone = -6,
				ResultPacketIsBig = -7,
				*/
				break;
			}
			//따로 패킷 처리 해줄 필요 없이 그냥 큐에 넣고, 처리는 인터페이스에서 해준다.
			AddRawPacketToQue(RecvBuffer, length);

		}

	}

	int SocketNetwork::Recv(char *pBuffer)
	{
		int receivedLen;

		receivedLen = recv(m_Sockfd, pBuffer, BUFFERSIZE, 0);

		if (receivedLen == 0)
		{
			return static_cast<int>(MyReturnVal::ResultConnectClosedRemotly);//연결 실패
		}

		if (receivedLen < 0)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				return static_cast<int>(MyReturnVal::ResultReciveError);//WSAEWOULDBLOCK Error!
			}
			else
			{
				return static_cast<int>(MyReturnVal::ResultNone);
			}
		}

		if (receivedLen > PACKET_HEADER_SIZE + BUFFERSIZE)
		{
			return static_cast<int>(MyReturnVal::ResultPacketIsBig);
		}

		return receivedLen;
	}

	MyReturnVal SocketNetwork::AddRawPacketToQue(const char * pBuffer, const int pLen)
	{
		std::shared_ptr<char> rawPacket(new char[BUFFERSIZE], 
			[](char* pBuffer) 
			{
				std::cout << "temp buffer deleted\n";
				delete[] pBuffer;
			});

		//memcpy대신 사용.
		//std::copy(pBuffer, pBuffer + pLen, rawPacket.get()); 
		memcpy(rawPacket.get(), pBuffer, pLen);
		m_RawPacketPPLQue.push(rawPacket.get());

		return MyReturnVal::ResultOK;
	}


