#pragma once

#include "pch.h"

namespace MDNetwork
{
	using NotifyFuntion = std::function<void(PacketBodyPtr)>;
	using RawPacketQue = concurrency::concurrent_queue<RawPacketPtr>;
	using ObserverMap = concurrency::concurrent_unordered_map<PACKET_ID, NotifyFuntion>;

	class PacketProcessor
	{
	public:

		//생성자
		PacketProcessor() = default;
		//소멸자
		//스레드 정리
		~PacketProcessor();

		//네트워크의 패킷큐를 받아오는 함수
		void SetRawPacKetQue(RawPacketQue* pQue);

		//패킷을 처리하는 함수들을 맵에 등록한다.
		void AddFunctionToMap(short pPacketId, NotifyFuntion pLambda);

		//맵에서 함수를 제거
		void DeleteFunctionFromMap(short pPacketId);

		//스레드 종료 시키는 함수. 큐에 아이디가 0인 패킷을 넣는다.
		void EndThread();

	private:

		//패킷아이디 마다 저장되있는 패킷 함수를 실행시킨다.
		void ProcessPacket();

		//패킷을 처리하는 스레드함수 계속 패킷 프로세스를 실행한다. 
		void ProcessPacketThreadFunction();


		std::thread m_Thread;

		ObserverMap  m_ProcessFuctionsMap;
		RawPacketQue* m_RawPacketQue;
	};


}

