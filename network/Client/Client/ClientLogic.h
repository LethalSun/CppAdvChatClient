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
		//send 함수를 받아오는 함수
		void GetNetworkSendFunc(SendFunc pSendfunc);

		//--++로그인
		
		//로그인 리퀘스트 패킷을 보내는 함수
		int SendPktLogInReq(char* pID, char* pPW);
		
		//옵저버로 부터 받아오는 함수.
		int SetLOGIN_IN_RES_Que(LoginPacketQue* pQue);

		//서버에서 로그인 되었는지 확인을 하는 함수.
		bool IsLogin();



	private:
		
		//send 함수
		SendFunc m_SendFunc;

		char* m_ID = nullptr;

		char* m_Pw = nullptr;

		short m_LoginState = 0;

		//로그인 리스폰스가 왔을때 로직의 함수
		void OnLOGIN_IN_RES();

		LoginPacketQue* m_LoginQue;




	};

}
