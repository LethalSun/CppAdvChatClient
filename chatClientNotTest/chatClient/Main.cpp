// Siv3D March 2016
#include "ChatClient.h"
#include "Login.h"
#include "Lobby.h"
#include "ChatMain.h"
void Main()
{
	//Window::Resize(1280, 720);

	Graphics::SetBackground(Color(70, 80, 170));

	Manager manager;

	manager.add<chatClient::Login>(L"Login");
	manager.add<chatClient::Lobby>(L"Lobby");
	manager.add<chatClient::ChatMain>(L"ChatMain");

	while (System::Update())
	{
		if (!manager.updateAndDraw())
		{
			break;
		}
	}
}