#include "Network.h"

const char* SERVERRIP = "127.0.0.1";
const int SERVERPORT = 23452;
const int BUFFERSIZE = 4096;
namespace chatClient
{
	//�����ʱ�ȭ�� ���� �Ҵ�.
	int Network::Init()
	{
		//������ ������ üũ �����Ѵ�.MAKEWORD�� �ΰ��� ���� ����� ����� �ִ°�.
		WORD wVersionRequested = MAKEWORD(2, 2);
		//�ʱ�ȭ �� ������ ������ ���¸� �����ϴ� ����.
		WSADATA wsaData;

		//���ڷ� ���޵� ������ ���� �������� ������ ���� DLL�� �ʱ�ȭ �ϴ°�.
		auto returnVal = WSAStartup(wVersionRequested, &wsaData);

		//������ ���� �ʱ�ȭ�� �����ϸ� 0�� ��ȯ�Ѵ�.
		if (returnVal != 0)
		{
			return -1;
		}

		//����� �����ϵ��� ���ҽ��� �Ҵ��ϰ� �� ���ҽ��� ����Ҽ� �ִ� ���ϵ�ũ���� SOCKET �� ��ȯ �Ѵ�.
		//���� �ּ�ü�� ���� Ÿ�� ���������� �����Ѵ�, TCP�� ���� ��Ʈ�� udp�� ���� ��׷�(������ �׷�)�� �����Ѵ�.
		m_Sockfd = socket(AF_INET, SOCK_STREAM, 0);
		if (m_Sockfd == INVALID_SOCKET)
		{
			return -2;
		}


		return 0;
	}

	bool Network::Connect(const char* pAddr, const int pPort)
	{
		//SOCKADDR ���� �ּ� ����ü, SOCKADDR_IN�� TCP/IP���� ���Ǵ� ���� �ּ� ����ü ���� UDP������ ���
		SOCKADDR_IN serverAddr;
		serverAddr.sin_family = AF_INET;
		serverAddr.sin_port = htons(SERVERPORT);//TODO: pPort
		serverAddr.sin_addr.s_addr = inet_addr(SERVERRIP);//TODO: pAddr //���� 32��Ʈ ����ü�ε� IPv6�� ��� ����?

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
		//������ �ݴ´�
		closesocket(m_Sockfd);
		//������ ���� ���ҽ��� ��ȯ�Ѵ�.
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
			return 0;//���� ����
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

		while (dataSize - readPos > PACKET_HEADER_SIZE)//�����÷ο�� ���ٰ� ���������Ƿ� �Ƹ� 0�ΰ�� ���´�
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

