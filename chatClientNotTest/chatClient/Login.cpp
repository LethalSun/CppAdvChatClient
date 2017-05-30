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

		m_data->m_Scene = SceneState::LoginScene;

	}

	void Login::update()
	{
		if (m_data->m_Scene != SceneState::LoginScene)
		{
			return;
		}

		if (loginWindow.button(L"LoginButton").pushed)
		{
			LoginProcess();
		}

		CheckLoginState();

		return;

	}

	int Login::SendLoginPack()
	{
		auto returnVal = 0;

		
		char id[MAX_USER_ID_SIZE+1]{ 0, };

		const auto w_StrLoginId = m_data->loginID.c_str();

		Util::UnicodeToAnsi(w_StrLoginId, 16, id);

		
		char pw[MAX_USER_PASSWORD_SIZE+1]{ 0, };

		const auto w_StrPassword = m_data->loginPassWord.c_str();

		Util::UnicodeToAnsi(w_StrPassword, 16, pw);

		
		returnVal = m_data->m_Logic->SendPktLogInReq(id,pw);

		
		return returnVal;
	}

	int Login::LoginProcess()
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

		return 0;
	}

	int Login::CheckLoginState()
	{
		if (m_data->m_Logic->IsLogin() == true)
		{
			m_data->str = L"로그인 성공";
			m_data->m_Scene = SceneState::LobbyScene;
			changeScene(L"Lobby");
		}
		return 0;
	}

}
