#include "pch.h"
#include "Lobby.h"

void chatClient::Lobby::init()
{
	channelWindow.setTitle(L"Channel");


	channelWindow.add(L"channel1", GUIText::Create(L"channel 1"));

	channelWindow.addln(L"channel1Button", GUIButton::Create(L"Enter"));


	channelWindow.add(L"channel2", GUIText::Create(L"channel 2"));

	channelWindow.addln(L"channel2Button", GUIButton::Create(L"Enter"));


	channelWindow.add(L"channel3", GUIText::Create(L"channel 3"));

	channelWindow.addln(L"channel3Button", GUIButton::Create(L"Enter"));


	channelWindow.add(L"channel4", GUIText::Create(L"channel 4"));

	channelWindow.addln(L"channel4Button", GUIButton::Create(L"Enter"));


	channelWindow.add(L"channel5", GUIText::Create(L"channel 5"));

	channelWindow.addln(L"channel5Button", GUIButton::Create(L"Enter"));


	channelWindow.setCenter(Window::Center());
}

void chatClient::Lobby::update()
{
	m_data->debugFont(m_data->str).draw();
	CheckSelectedChannelNum();

	if (selectedChannelNum != -1)
	{
		//TODO:ü�� �ѹ��� �Ѱܼ� �˸��� ü�ε����͸� �޾ƿ´�.
		changeScene(L"ChatMain");
	}

}

void chatClient::Lobby::draw() const
{
	//TODO:ä�� ������ �޾ƿͼ� �׸��� �κ� ����� �ִ��� ��
}

int chatClient::Lobby::CheckSelectedChannelNum()
{
	if (channelWindow.button(L"channel1Button").pushed)
	{
		selectedChannelNum = 1; 
		return 0;
	}
	else if (channelWindow.button(L"channel2Button").pushed)
	{
		selectedChannelNum = 2;
		return 0;
	}
	else if (channelWindow.button(L"channel3Button").pushed)
	{
		selectedChannelNum = 3;
		return 0;
	}
	else if (channelWindow.button(L"channel4Button").pushed)
	{
		selectedChannelNum = 4;
		return 0;
	}
	else if (channelWindow.button(L"channel5Button").pushed)
	{
		selectedChannelNum = 5;
		return 0;
	}
	else
	{
		selectedChannelNum = -1;
		return -1;
	}
}
