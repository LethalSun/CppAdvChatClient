#include "pch.h"
#include "ChatClient.h"


ChatClient::ChatClient()
	:loginWindow(GUIStyle::Default)
	, font{30}
	, font2{20}
{
	loginWindow.setTitle(L"name");
	loginWindow.addln(L"mainText",GUIText::Create(L"Login"));
	loginWindow.addln(L"LoginId", GUITextField::Create(none));
	loginWindow.addln(L"LoginPassword", GUITextField::Create(none));
	loginWindow.addln(L"LoginButton", GUIButton::Create(L"Login"));
	//loginWindow.setCenter(Window::Center());
}


ChatClient::~ChatClient()
{
}

int ChatClient::Update()
{
	if (loginWindow.button(L"LoginButton").pushed)
	{
		loginID = loginWindow.textField(L"LoginId")._get_text();
		loginPassWord = loginWindow.textField(L"LoginPassword")._get_text();
	}
	
	//font(loginID).drawCenter(Window::Center());
	//font2(loginPassWord).draw(Mouse::Pos());
	return 0;
}
