#include "pch.h"
#include "ChatClient.h"


ChatClient::ChatClient()
	:loginWindow(GUIStyle::Default)
	, channelWindow(GUIStyle::Default)
	,mainWindow(GUIStyle::Default)
	, font{30}
	, font2{20}
{
	//init login window
	loginWindow.setTitle(L"Login");
	//loginWindow.addln(L"mainText",GUIText::Create(L"Login"));
	loginWindow.addln(L"LoginId", GUITextField::Create(none));
	loginWindow.addln(L"LoginPassword", GUITextField::Create(none));
	loginWindow.addln(L"LoginButton", GUIButton::Create(L"Login"));
	//loginWindow.setCenter(Window::Center());

	//init  chennel window
	channelWindow.setTitle(L"Channel");
	channelWindow.setPos(Point(200, 300));
	channelWindow.add(L"channel0", GUIText::Create(L"hello    "));
	channelWindow.addln(L"channel0Button", GUIButton::Create(L"Enter"));
	channelWindow.add(L"channel1", GUIText::Create(L"hell     "));
	channelWindow.addln(L"channel0Button", GUIButton::Create(L"Enter"));
	channelWindow.add(L"channel2", GUIText::Create(L"hello    "));
	channelWindow.addln(L"channel0Button", GUIButton::Create(L"Enter"));
	channelWindow.add(L"channel3", GUIText::Create(L"hi       "));
	channelWindow.addln(L"channel0Button", GUIButton::Create(L"Enter"));
	channelWindow.add(L"channel4", GUIText::Create(L"who?     "));
	channelWindow.addln(L"channel0Button", GUIButton::Create(L"Enter"));
	
	//init main window

	mainWindow.setTitle(L"Main");
	mainWindow.setPos(Point{ 500,500 });
	mainWindow.style.showBoxModel = true;
	mainWindow.addln(L"testText", GUIText::Create(L"hello"));
	mainWindow.addln(L"inputField", GUITextArea::Create(4,20));

	mainWindow.textArea(L"inputField").style.padding.left = 50;
	mainWindow.textArea(L"inputField").style.padding.right = 50;
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

	chatInput = mainWindow.textArea(L"inputField")._get_text();

	//font(chatInput).drawCenter(600,360);
	//PutText(L"a:", chatInput);
	//font(loginID).drawCenter(Window::Center());
	//font2(loginPassWord).draw(Mouse::Pos());
	return 0;
}
