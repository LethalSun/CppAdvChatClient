#include "pch.h"
#include "Lobby.h"
#include "../../network/Client/Client/Network.h"
namespace MDNetwork
{

	void Lobby::init()
	{
		channelWindow.setTitle(L"Channel");
		
		//처음 로비 리스트 가져오기.
		GetLobbyListFromServer();

		//표시.
		AddTextAndButton(channelWindow, 0);
		AddTextAndButton(channelWindow, 1);

		channelWindow.setCenter(Window::Center());
	}

	void Lobby::update()
	{
		m_data->debugFont(m_data->str).draw();
		
		GetLobbyListFromServer();
		
		RenewChannel();
		
		EnterLobby();

	}

	void Lobby::draw() const
	{
		//TODO:채널 정보를 받아와서 그리는 부분 몇명이 있는지 등
	}

	int Lobby::AddTextAndButton(GUI gui, int listIndex)
	{
		auto index = ToString(listIndex, 10);
		
		gui.add(index, GUIText::Create(m_ChennelList[listIndex].LobbyName));
		gui.text(index).style.width = 100;

		gui.addln(index, GUIButton::Create(L"Enter"));

		return 1;
	}

	int Lobby::RenewChannel()
	{
		//TODO: 로비의 갯수가 바뀌거나 로비의 아이디가 바뀌나?
		channelWindow.text(L"0").text = m_ChennelList[0].LobbyName;
		channelWindow.text(L"1").text = m_ChennelList[1].LobbyName;
		return 0;
	}

	int Lobby::CheckSelectedChannelNum()
	{
		if (channelWindow.button(L"0").pushed)
		{
			selectedChannelNum = 0;
			return 0;
		}
		else if (channelWindow.button(L"1").pushed)
		{
			selectedChannelNum = 1;
			return 0;
		}
		else
		{
			selectedChannelNum = -1;
			return -1;
		}
	}

	bool Lobby::IsChennelSelected()
	{

		if (selectedChannelNum == 0 || selectedChannelNum == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
		
	}

	int Lobby::GetLobbyListFromServer()
	{
		auto returnVal = -1;

		if (refreshTimeForChennelList >= 5)
		{
			m_data->m_Logic->SendPktLobbyListInfo();
			refreshTimeForChennelList = 0;
			return returnVal;
		}


		auto TotalNum = -1;
		m_data->m_Logic->GetLobbyList(TotalNum);

		for (int i = 0; i < TotalNum; ++i)
		{
			auto channelInfo = m_data->m_Logic->GetLobbyList(i);

			short id = -1, userNum = -1;

			std::tie(id, userNum) = channelInfo;

			m_ChennelList[i].LobbyName = Format(L"channel", id,
							L" ", userNum, L"/50");
			m_ChennelList[i].LobbyId = id;
			m_ChennelList[i].LobbyUserCount = userNum;
		}

		++refreshTimeForChennelList;

		return 0;
	}

	int Lobby::EnterLobby()
	{
		if (m_NumOfCheckingForIsAllowed == 0)
		{
			CheckSelectedChannelNum();


			if (IsChennelSelected())
			{
				auto lobID = m_ChennelList[selectedChannelNum].LobbyId;
				m_data->m_Logic->SendPktLobbyEnter(lobID);
				m_NumOfCheckingForIsAllowed = 1;
			}
		}
		else if (m_NumOfCheckingForIsAllowed == 120)
		{
			selectedChannelNum = -1;
			m_NumOfCheckingForIsAllowed == 0;
		}
		else
		{
			if (m_data->m_Logic->IsLobbyEnterAllowed())
			{
				auto tuple = m_data->m_Logic->GetUserAndRoomCount();

				short UserNum = 0;
				short RoomNum = 0;

				std::tie(UserNum, RoomNum) = tuple;
				m_data->m_LobbyInfo.LobbyId = m_ChennelList[selectedChannelNum].LobbyId;
				m_data->m_LobbyInfo.LobbyName = m_ChennelList[selectedChannelNum].LobbyName;
				m_data->m_LobbyInfo.RoomCount = RoomNum;
				m_data->m_LobbyInfo.UserCount = UserNum;

				changeScene(L"Chennel");
			}

			m_NumOfCheckingForIsAllowed = ++m_NumOfCheckingForIsAllowed;
		}

		return 0;
	}
	
}
