#include "pch.h"
#include "ChatMain.h"

void chatClient::ChatMain::init()
{
	Window::Resize(1280, 720);
	showWindow.style.showBoxModel = true;
	inputWindow.style.showBoxModel = true;
	roomWindow.style.showBoxModel = true;
	memberWindow.style.showBoxModel = true;
	
	MakeRoomIndex();
	
	InitRoomWindow();

	InitInputWindow();

	InitShowWindow();

	MakeMemberIndex();

	InitMemberWindow();
}

void chatClient::ChatMain::update()
{
}

void chatClient::ChatMain::draw() const
{
}

int chatClient::ChatMain::InitRoomWindow()
{

	roomWindow.setTitle(L"Room List");
	for (int i = 0; i < 7; i++)
	{
		AddTextAndButton(roomWindow, i, L"Room1");
	}

	roomWindow.add(L"Lobby", GUIText::Create(L"To Lobby"));
	roomWindow.text(L"Lobby").style.width = 100;
	roomWindow.addln(L"LobbyButton", GUIButton::Create(L"Enter"));

	roomWindow.setPos(Point(0, 0));
	roomWindow.style.width = 250;

	return 1;
}

int chatClient::ChatMain::InitInputWindow()
{
	auto pos = roomWindow.getPos();
	
	auto dPos = roomWindow.getRect();
	
	auto WindowPos = static_cast<Point>( Window::Size());
	
	inputWindow.setTitle(L"Input");
	
	inputWindow.addln(L"InputField", GUITextArea::Create(2, 30));

	auto dWindowPos = inputWindow.getRect();
	
	inputWindow.setPos(Point(pos.x + dPos.w, WindowPos.y - dWindowPos.h));
	
	return 1;
}

int chatClient::ChatMain::InitShowWindow()
{
	auto pos = roomWindow.getPos();

	auto dPos = roomWindow.getRect();
	showWindow.setTitle(L"Chat");
	showWindow.addln(L"ShowField", GUITextArea::Create(25, 30));
	showWindow.setPos(Point(pos.x + dPos.w, 0));

	return 1;
}

int chatClient::ChatMain::InitMemberWindow()
{
	auto pos = roomWindow.getPos();

	auto dPos = roomWindow.getRect();

	memberWindow.setTitle(L"Member");

	for (int i = 0; i < 5; i++)
	{
		AddText(memberWindow, i, L"member1");
	}

	memberWindow.setPos(Point(0,pos.y + dPos.h));
	
	memberWindow.style.width = 250;

	return 1;
}

int chatClient::ChatMain::AddTextAndButton(GUI gui, int listIndex, String name)
{
	auto index = roomIndex[listIndex];
	gui.add(index, GUIText::Create(name));
	gui.text(index).style.width = 100;

	auto indexButton = index + String(L"Button");
	gui.addln(indexButton, GUIButton::Create(L"Enter"));

	return 1;
}

int chatClient::ChatMain::AddText(GUI gui, int listIndex, String name)
{
	auto index = memberIndex[listIndex];
	gui.addln(index, GUIText::Create(name));
	gui.text(index).style.width = 100;

	return 1;
}

int chatClient::ChatMain::MakeRoomIndex()
{
	roomIndex[0] = L"Room1";
	roomIndex[1] = L"Room2";
	roomIndex[2] = L"Room3";
	roomIndex[3] = L"Room4";
	roomIndex[4] = L"Room5";
	roomIndex[5] = L"Room6";
	roomIndex[6] = L"Room7";

	return 1;
}

int chatClient::ChatMain::MakeMemberIndex()
{
	memberIndex[0] = L"Member1";
	memberIndex[1] = L"Member2";
	memberIndex[2] = L"Member3";
	memberIndex[3] = L"Member4";
	memberIndex[4] = L"Member5";

	return 1;
}