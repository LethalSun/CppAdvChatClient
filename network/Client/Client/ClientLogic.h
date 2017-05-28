#pragma once

namespace MDNetwork
{
	class ClientLogic
	{
	public:

		ClientLogic();

		~ClientLogic();

		//로그인
		//로그인 리퀘스트 패킷을 보내는 함수
		int SendPktLogInReq(char* pID, char* pPW);

		//로그인 리스폰스가 왔을때 로직의 함수
		void OnLOGIN_IN_RES();

		//서버에서 로그인 되었는지 확인을 하는 함수.
		bool IsLogin();



	private:

		//로그인
		char* m_ID = nullptr;
		char* m_Pw = nullptr;
		bool m_LoginState = false;


	};

}
