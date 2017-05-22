#include "SocketNetwork.h"


namespace MDNetwork
{
	SocketNetwork::~SocketNetwork()
	{
		Release();
	}

	MyReturnVal SocketNetwork::Init()
	{//������ ������ üũ �����Ѵ�.MAKEWORD�� �ΰ��� ���� ����� ����� �ִ°�.
		WORD wVersionRequested = MAKEWORD(2, 2);
		//�ʱ�ȭ �� ������ ������ ���¸� �����ϴ� ����.
		WSADATA wsaData;

		//���ڷ� ���޵� ������ ���� �������� ������ ���� DLL�� �ʱ�ȭ �ϴ°�.
		auto returnVal = WSAStartup(wVersionRequested, &wsaData);

		//������ ���� �ʱ�ȭ�� �����ϸ� 0�� ��ȯ�Ѵ�.
		if (returnVal !=0)
		{
			return MyReturnVal::ResultSocketInitFail;
		}

		//����� �����ϵ��� ���ҽ��� �Ҵ��ϰ� �� ���ҽ��� ����Ҽ� �ִ� ���ϵ�ũ���� SOCKET �� ��ȯ �Ѵ�.
		//���� �ּ�ü�� ���� Ÿ�� ���������� �����Ѵ�, TCP�� ���� ��Ʈ�� udp�� ���� ��׷�(������ �׷�)�� �����Ѵ�.
		m_Sockfd = socket(AF_INET, SOCK_STREAM, 0);
		if (m_Sockfd == INVALID_SOCKET)
		{
			return MyReturnVal::ResultSocketAllocFail;
		}


		return MyReturnVal::ResultOK;
	}

	MyReturnVal SocketNetwork::Connect(const char * pAddr, const int pPort)
	{	
		//SOCKADDR ���� �ּ� ����ü, SOCKADDR_IN�� TCP/IP���� ���Ǵ� ���� �ּ� ����ü ���� UDP������ ���
		SOCKADDR_IN serverAddr;
		serverAddr.sin_family = AF_INET;
		serverAddr.sin_port = htons(pPort);//��Ʈ ���� ��Ʋ����ȿ��� �򿣵�ȵ�� �ٲ�
		serverAddr.sin_addr.s_addr = inet_addr(pAddr); //���� 32��Ʈ ����ü�ε� IPv6�� ��� ����?

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
		//������ �ݴ´�
		closesocket(m_Sockfd);
		//������ ���� ���ҽ��� ��ȯ�Ѵ�.
		WSACleanup();

		return MyReturnVal::ResultOK;
	}

	void SocketNetwork::ReceiveThreadFunc()
	{

		while (true)
		{
			char RecvBuffer[BUFFERSIZE];

			//�ϴ� ���ú�� �ѹ��� �ٹ����� �ִ� ���̶�� �����Ѵ�.
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
			//���� ��Ŷ ó�� ���� �ʿ� ���� �׳� ť�� �ְ�, ó���� �������̽����� ���ش�.
			AddRawPacketToQue(RecvBuffer, length);

		}

	}

	int SocketNetwork::Recv(char *pBuffer)
	{
		int receivedLen;

		receivedLen = recv(m_Sockfd, pBuffer, BUFFERSIZE, 0);

		if (receivedLen == 0)
		{
			return static_cast<int>(MyReturnVal::ResultConnectClosedRemotly);//���� ����
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

		//memcpy��� ���.
		//std::copy(pBuffer, pBuffer + pLen, rawPacket.get()); 
		memcpy(rawPacket.get(), pBuffer, pLen);
		m_RawPacketPPLQue.push(rawPacket.get());

		return MyReturnVal::ResultOK;
	}


