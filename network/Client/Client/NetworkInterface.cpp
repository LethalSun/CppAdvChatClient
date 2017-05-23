#include "NetworkInterface.h"

namespace MDNetwork
{
	void NetworkInterface::run()
	{

	}

	void NetworkInterface::Subscribe(short pPacketId, NotifyFuntion pFunctor)
	{
		if (m_ObserverMap.find(static_cast<PACKET_ID>(pPacketId)) == m_ObserverMap.end())
		{
			m_ObserverMap.insert(std::make_pair(pPacketId, pFunctor));
		}
		else
		{
			return;
		}
		
	}

	void NetworkInterface::UnSubscribe(short pPacketId, NotifyFuntion pFunctor)
	{
		//TODO:�̱���.
	}

	void NetworkInterface::SetRawPacketQue(GetFromNetworkQue* pQue)
	{
		m_RawPacketQue = pQue;
	}

	void NetworkInterface::Broadcast(short pId, short pSize, char * pData)
	{
		//��¥ ��Ŷ�� ���̵�, ũ��, ���� ��Ŷ���� �ٽ� �ٵ� �����.
		auto newPacket = std::make_shared<PacketBody>(0);

		newPacket.get()->PacketId = pId;
		newPacket.get()->PacketBodySize = pSize;
		memcpy(newPacket.get()->PacketData, pData, pSize);

		//���̵� ���� �ϴ� �ݹ��Լ��� ã�´�.
		auto destObserver = m_ObserverMap.find((PACKET_ID)pId);

		//���ٸ� �Ѿ�� ������ �����ؼ� �� �����ڿ� ��Ŷ�� �־� �ش�.
		if (destObserver == m_ObserverMap.end())
		{
			OutputDebugString(L"fail to find observer");
		}
		else
		{
			auto OnNotify = destObserver->second;
			OnNotify(newPacket);
		}

	}

	void NetworkInterface::PacketProcessThreadFunction()
	{
		//ť�� �ִ� ó������ ���� ��Ŷ���� ����� �����.
		std::shared_ptr<char> rawPacket;

		while (m_RawPacketQue->try_pop(rawPacket))
		{
			auto packet =  (PacketHeder*)rawPacket.get();

			Broadcast(packet->Id,packet->BodySize,&rawPacket.get()[PACKET_HEADER_SIZE]);
		}

		
	}

}
