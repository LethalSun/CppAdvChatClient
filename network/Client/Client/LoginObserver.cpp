#include "pch.h"
#include "LoginObserver.h"

namespace MDNetwork
{
	LoginObserver::LoginObserver()
	{
	}


	LoginObserver::~LoginObserver()
	{
	}

	void LoginObserver::NotifyLOGIN_IN_RES(PacketBodyPtr pPacket)
	{
		auto pktID = pPacket->PacketId;
		auto pktSize = pPacket->PacketBodySize;
		auto Pkt = (MDNetwork::PktLobbyListRes*)pPacket->PacketData;


	}

}
