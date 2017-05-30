#include "pch.h"
#include "NetworkInterface.h"

namespace MDNetwork
{
	void NetworkInterface::run()
	{
		m_Thead = std::thread([this]() {  PacketProcessThreadFunction(); });
	}

	void NetworkInterface::Subscribe(short pPacketId, NotifyFuntion pFunctor)
	{
		if (m_ObserverMap.find(static_cast<PACKET_ID>(pPacketId)) == m_ObserverMap.end())
		{
			m_ObserverMap.insert(std::make_pair(static_cast<PACKET_ID>(pPacketId), pFunctor));
		}
		else
		{
			return;
		}
		
	}

	void NetworkInterface::UnSubscribe(short pPacketId, NotifyFuntion pFunctor)
	{
		//TODO:미구현.
	}

	void NetworkInterface::SetRawPacketQue(GetFromNetworkQue* pQue)
	{
		m_RawPacketQue = pQue;
	}

	void NetworkInterface::Broadcast(short pId, short pSize, char * pData)
	{
		//진짜 패킷의 아이디, 크기, 실제 패킷으로 다시 바디를 만든다.
		auto newPacket = std::make_shared<PacketBody>();

		newPacket.get()->PacketId = pId;
		newPacket.get()->PacketBodySize = pSize;
		newPacket.get()->PacketData = new char[newPacket.get()->PacketBodySize];
		memcpy(newPacket.get()->PacketData, pData, pSize);

		//아이디에 대응 하는 콜백함수를 찾는다.
		auto destObserver = m_ObserverMap.find((PACKET_ID)pId);

		//없다면 넘어가고 있으면 실행해서 각 관찰자에 패킷을 넣어 준다.
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
		//큐에 있는 처리되지 않은 패킷에서 헤더를 때어낸다.
		

		while (true)
		{
			std::shared_ptr<char> rawPacket;

			if (m_RawPacketQue->try_pop(rawPacket))
			{
				auto packet = (PacketHeder*)rawPacket.get();

				Broadcast(packet->Id, packet->BodySize, &rawPacket.get()[PACKET_HEADER_SIZE]);
			}
			
		}

		
	}

}
