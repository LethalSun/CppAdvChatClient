#pragma once

namespace MDNetwork
{
	class SocketNetwork;

	using SendFunc = std::function<int(const short, const short, char*)>;
	using LoginPacketQue = concurrency::concurrent_queue<short>;

	class ClientLogic
	{
	public:

		ClientLogic();

		~ClientLogic();
		//send �Լ��� �޾ƿ��� �Լ�
		void GetNetworkSendFunc(SendFunc pSendfunc);

		//--++�α���
		
		//�α��� ������Ʈ ��Ŷ�� ������ �Լ�
		int SendPktLogInReq(char* pID, char* pPW);
		
		//�������� ���� �޾ƿ��� �Լ�.
		int SetLOGIN_IN_RES_Que(LoginPacketQue* pQue);

		//�������� �α��� �Ǿ����� Ȯ���� �ϴ� �Լ�.
		bool IsLogin();



	private:
		
		//send �Լ�
		SendFunc m_SendFunc;

		char* m_ID = nullptr;

		char* m_Pw = nullptr;

		short m_LoginState = 0;

		//�α��� ���������� ������ ������ �Լ�
		void OnLOGIN_IN_RES();

		LoginPacketQue* m_LoginQue;




	};

}
