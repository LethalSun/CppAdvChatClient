#include "pch.h"
#include "Login.h"

void chatClient::Login::init()
{
	loginWindow.setTitle(L"Login");


	loginWindow.addln(L"LoginId", GUITextField::Create(none));


	loginWindow.addln(L"LoginPassword", GUITextField::Create(none));


	loginWindow.addln(L"LoginButton", GUIButton::Create(L"Login"));

	loginWindow.setCenter(Window::Center());
}

void chatClient::Login::update()
{
	if (loginWindow.button(L"LoginButton").pushed)
	{
		m_data->loginID = loginWindow.textField(L"LoginId")._get_text();
		m_data->loginPassWord = loginWindow.textField(L"LoginPassword")._get_text();
		//TODO:���̵� �н����尡 �´��� Ȯ���ϴ� �κ�
		
		//������
		changeScene(L"Lobby");
		//�ƴϸ�
	}
}
