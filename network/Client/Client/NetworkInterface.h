#pragma once

#include "pch.h"

namespace MDNetwork
{

	class Observer;

	using NotifyFuntion = std::function<void(PacketBodyPtr)>;
	using GetFromNetworkQue = concurrency::concurrent_queue<RawPacketPtr>;
	using ObserverMap = concurrency::concurrent_unordered_map<PACKET_ID, NotifyFuntion>;

	class NetworkInterface
	{
	public:
		NetworkInterface() = default;
		~NetworkInterface() = default;

		void run();

		void Subscribe(short pPacketId, NotifyFuntion pFunctor);

		void UnSubscribe(short pPacketId, NotifyFuntion pFunctor);

		void SetRawPacketQue(GetFromNetworkQue * pQue);

	private:

		void Broadcast(short pId, short pSize, char* pData);

		void PacketProcessThreadFunction();

		std::thread m_Thead;

		//std::unordered_map<PACKET_ID, NotifyFuntion> m_ObserverMap;
		ObserverMap  m_ObserverMap;
		GetFromNetworkQue* m_RawPacketQue;

	};

}
/*
namespace chatClient
{

	

#include "pch.h"
#include "ClientLogic.h"

	


}

*/
