#pragma once
#include "pch.h"

namespace MDNetwork
{
	using LoginPacketQue = concurrency::concurrent_queue<short>;
	using LOGIN_IN_RES_Func = std::function<void(PacketBodyPtr)>;
	class LoginObserver
	{
	public:
		LoginObserver();
		~LoginObserver();

		LOGIN_IN_RES_Func GetLOGIN_IN_RES_Func();

		LoginPacketQue* GetLOGIN_IN_RES_Que();
		
	private:

		void NotifyLOGIN_IN_RES(PacketBodyPtr pPacket);

		LoginPacketQue m_loginPacketQue;
	};

}

