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

	LOGIN_IN_RES_Func LoginObserver::GetLOGIN_IN_RES_Func()
	{
		return [this](PacketBodyPtr pPacket)
		{
			NotifyLOGIN_IN_RES(pPacket);
		};
	}

	LoginPacketQue* LoginObserver::GetLOGIN_IN_RES_Que()
	{
		return &m_loginPacketQue;
	}

	void LoginObserver::NotifyLOGIN_IN_RES(PacketBodyPtr pPacket)
	{
		auto pktID = pPacket->PacketId;
		auto pktSize = pPacket->PacketBodySize;
		//패킷베이스의 에러코드를 확인 할수 있을수도. 
		auto Pkt = (MDNetwork::PktLobbyListRes*)pPacket->PacketData;

		m_loginPacketQue.push(pktID);

	}

}
