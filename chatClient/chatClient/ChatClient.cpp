#include "pch.h"
#include "ChatClient.h"


ChatClient::ChatClient()
	:loginWindow(GUIStyle::Default)
{
	loginWindow.setTitle(&(Define::name));
}


ChatClient::~ChatClient()
{
}

int ChatClient::Update()
{
	return 0;
}
