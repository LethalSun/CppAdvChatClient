#include "pch.h"
#include "ChatClient.h"


ChatClient::ChatClient()
	:loginWindow(GUIStyle::Default)
{
	loginWindow.setTitle(L"name");
	loginWindow.addln(GUIText::Create(L"Login"));
	loginWindow.addln(L"LoginId", GUITextField::Create(none));
	loginWindow.addln(L"LoginPassword", GUITextField::Create(none));
	loginWindow.addln(L"LoginButton", GUIButton::Create(L"Login"));
}


ChatClient::~ChatClient()
{
}

int ChatClient::Update()
{
	return 0;
}
