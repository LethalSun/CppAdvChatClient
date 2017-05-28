#pragma once
#include "pch.h"

namespace MDNetwork
{
	using LoginPacketQue = concurrency::concurrent_queue<std::shared_ptr<PacketBody>>;

	class LoginObserver
	{
	public:
		LoginObserver();
		~LoginObserver();

		void NotifyLOGIN_IN_RES(PacketBodyPtr pPacket);
	private:

		LoginPacketQue m_loginPacketQue;
	};

}

