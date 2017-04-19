#include "pch.h"
#include "Login.h"
#include "../../network/Client/Client/Network.h"

void chatClient::Login::init()
{
	loginWindow.setTitle(L"Login");


	loginWindow.addln(L"LoginId", GUITextField::Create(none));


	loginWindow.addln(L"LoginPassword", GUITextField::Create(none));


	loginWindow.addln(L"LoginButton", GUIButton::Create(L"Login"));

	loginWindow.setCenter(Window::Center());

	m_data->m_Network = new chatClient::Network();
	m_data->m_Network->Init();
}

void chatClient::Login::update()
{
	if (loginWindow.button(L"LoginButton").pushed)
	{
		m_data->loginID = loginWindow.textField(L"LoginId")._get_text();
		m_data->loginPassWord = loginWindow.textField(L"LoginPassword")._get_text();
	
		//커넥트
		if (m_data->m_Network->Connect("127.0.0.1", 23452) == false)
		{
			font(L"Connect Failed").draw();
		}	
		//로그인 정보 보내기
		if (SendLoginPack() == -1)
		{
			font(L"Send Failed").draw();
		}
	}
	//TODO:아이디 패스워드가 맞는지 확인하는 부분
	auto packet = m_data->m_Network->GetPacket();
	
	//맞으면
	if (packet.PacketId == (short)PACKET_ID::LOGIN_IN_RES)
	{
		m_data->str = L"로그인 성공";
		changeScene(L"Lobby");
	}
	//아니면
}

int chatClient::Login::SendLoginPack()
{
	auto returnVal = 0;
	if (m_IsLogedIn == false)
	{
		char id[16]{ 0, };
		const auto w_StrLoginId = m_data->loginID.c_str();
		Util::UnicodeToAnsi(w_StrLoginId, 16, id);

		char pw[16]{ 0, };
		const auto w_StrPassword = m_data->loginPassWord.c_str();
		Util::UnicodeToAnsi(w_StrPassword, 16, pw);

		PktLogInReq loginPacket{ 0, };
		strncpy_s(loginPacket.szID, MAX_USER_ID_SIZE + 1, id, MAX_USER_ID_SIZE);
		strncpy_s(loginPacket.szPW, MAX_USER_PASSWORD_SIZE + 1, pw, MAX_USER_PASSWORD_SIZE);

		returnVal = m_data->m_Network->Send((short)PACKET_ID::LOGIN_IN_REQ, sizeof(loginPacket), (char*)&loginPacket);
	}

	
	return returnVal;
}
