#include "pch.h"
#include "Login.h"
#include "../../network/Client/Client/SocketNetwork.h"

namespace MDNetwork
{
	void Login::init()
	{
		loginWindow.setTitle(L"Login");


		loginWindow.addln(L"LoginId", GUITextField::Create(none));


		loginWindow.addln(L"LoginPassword", GUITextField::Create(none));


		loginWindow.addln(L"LoginButton", GUIButton::Create(L"Login"));

		loginWindow.setCenter(Window::Center());

		//m_data->m_Network = new chatClient::Network();
		//m_data->m_Network->Init();
		//m_data->m_LobbyId = -1;
	}

	void Login::update()
	{
		if (loginWindow.button(L"LoginButton").pushed)
		{
			int retVal = 0;
			
			m_data->loginID = loginWindow.textField(L"LoginId")._get_text();
			
			m_data->loginPassWord = loginWindow.textField(L"LoginPassword")._get_text();

			if (m_data->m_Logic->IsLogin() == false)
			{
				retVal = SendLoginPack();
			}
	

			
			
			if (retVal == -1)
			{
				font(L"Send Failed").draw();
			}
		}

		if (m_data->m_Logic->IsLogin() == true)
		{
			m_data->str = L"로그인 성공";
			changeScene(L"Lobby");
			return;
		}

	}

	int Login::SendLoginPack()
	{
		auto returnVal = 0;

		
		char id[16]{ 0, };

		const auto w_StrLoginId = m_data->loginID.c_str();

		Util::UnicodeToAnsi(w_StrLoginId, 16, id);

		
		char pw[16]{ 0, };

		const auto w_StrPassword = m_data->loginPassWord.c_str();

		Util::UnicodeToAnsi(w_StrPassword, 16, pw);

		
		returnVal = m_data->m_Logic->SendPktLogInReq(id,pw);

		
		return returnVal;
	}

}
