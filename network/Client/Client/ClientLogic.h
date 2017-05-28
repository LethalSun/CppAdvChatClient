#pragma once

namespace MDNetwork
{
	class ClientLogic
	{
	public:

		ClientLogic();

		~ClientLogic();

		//�α���
		//�α��� ������Ʈ ��Ŷ�� ������ �Լ�
		int SendPktLogInReq(char* pID, char* pPW);

		//�α��� ���������� ������ ������ �Լ�
		void OnLOGIN_IN_RES();

		//�������� �α��� �Ǿ����� Ȯ���� �ϴ� �Լ�.
		bool IsLogin();



	private:

		//�α���
		char* m_ID = nullptr;
		char* m_Pw = nullptr;
		bool m_LoginState = false;


	};

}
