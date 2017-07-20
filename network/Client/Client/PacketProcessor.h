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

		//������
		PacketProcessor() = default;
		//�Ҹ���
		//������ ����
		~PacketProcessor();

		//��Ʈ��ũ�� ��Ŷť�� �޾ƿ��� �Լ�
		void SetRawPacKetQue(RawPacketQue* pQue);

		//��Ŷ�� ó���ϴ� �Լ����� �ʿ� ����Ѵ�.
		void AddFunctionToMap(short pPacketId, NotifyFuntion pLambda);

		//�ʿ��� �Լ��� ����
		void DeleteFunctionFromMap(short pPacketId);

		//������ ���� ��Ű�� �Լ�. ť�� ���̵� 0�� ��Ŷ�� �ִ´�.
		void EndThread();

	private:

		//��Ŷ���̵� ���� ������ִ� ��Ŷ �Լ��� �����Ų��.
		void ProcessPacket();

		//��Ŷ�� ó���ϴ� �������Լ� ��� ��Ŷ ���μ����� �����Ѵ�. 
		void ProcessPacketThreadFunction();


		std::thread m_Thread;

		ObserverMap  m_ProcessFuctionsMap;
		RawPacketQue* m_RawPacketQue;
	};


}

