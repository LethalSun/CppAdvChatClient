// Siv3D March 2016
#include "ChatClient.h"

void Main()
{
	Window::Resize(1280, 720);

	Graphics::SetBackground(Color(70, 80, 170));

	ChatClient cc;

	while (System::Update())
	{

		cc.Update();
	}
}