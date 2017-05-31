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
		~NetworkInterface();

		void run();

		void Subscribe(short pPacketId, NotifyFuntion pFunctor);

		void UnSubscribe(short pPacketId, NotifyFuntion pFunctor);

		void SetRawPacketQue(GetFromNetworkQue * pQue);

		void SetIsEnd();

	private:
		bool IsEnd = false;

		void Broadcast(short pId, short pSize, char* pData);

		void PacketProcessThreadFunction();

		std::thread m_Thead;

		//std::unordered_map<PACKET_ID, NotifyFuntion> m_ObserverMap;

		//ppl컨테이너들
		ObserverMap  m_ObserverMap;
		GetFromNetworkQue* m_RawPacketQue;

	};

}
