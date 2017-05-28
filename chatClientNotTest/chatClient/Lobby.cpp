#include "pch.h"
#include "Lobby.h"
#include "../../network/Client/Client/Network.h"
namespace chatClient
{


	void Lobby::init()
	{
		channelWindow.setTitle(L"Channel");
		//처음 로비 리스트 가져오기.
		GetLobbyListFromServer();

		//표시.
		AddTextAndButton(channelWindow, 0);
		AddTextAndButton(channelWindow, 1);

		//TODO: 로비 리스트 가져오기 확인용 임시 버튼 
		auto index = L"test";
		channelWindow.add(index, GUIText::Create(L"getLobby"));
		channelWindow.text(index).style.width = 100;
		auto indexButton = index + String(L"Button");
		channelWindow.addln(indexButton, GUIButton::Create(L"Enter"));
		
		channelWindow.setCenter(Window::Center());
	}

	void Lobby::update()
	{
		//TODO: 디버그
		m_data->debugFont(m_data->str).draw();

		if (timer >= 5)
		{
			GetLobbyListFromServer();
			RenewChannel();
			timer = 0;
		}
		else
		{
			++timer;
		}

		CheckSelectedChannelNum();

		if (selectedChannelNum > -1)
		{
			m_data->m_LobbyId = m_ChennelList[selectedChannelNum].LobbyId;
			//채널 입장 패킷 보내는 부분

			EnterLobby();

			if (m_IsAvailable == true)
			{
				changeScene(L"ChatMain");
			}
		}

		GetPacket();

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

	int Lobby::GetLobbyListFromServer()
	{
		auto returnVal = -1;

		SendGetLobbyPacket();

		return returnVal;
	}

	int Lobby::SendGetLobbyPacket()
	{
		auto returnVal = m_data->m_Network->Send(
			(short)MDNetwork::PACKET_ID::LOBBY_LIST_REQ,
			0,
			nullptr);

		return returnVal;
	}

	int Lobby::SendEnterLobbyPacket()
	{
		auto lobbyId = m_data->m_LobbyId;

		MDNetwork::PktLobbyEnterReq lobbyInPacket{0,};
		lobbyInPacket.LobbyId = lobbyId;

		auto returnVal = m_data->m_Network->Send(
			(short)MDNetwork::PACKET_ID::LOBBY_ENTER_REQ,
			sizeof(lobbyInPacket),
			(char*)&lobbyInPacket);

		return returnVal;
	}

	int Lobby::EnterLobby()
	{
		if (SendEnterLobbyPacket() == -1)
		{
			font(L"Send Failed").draw();
		}

		return 0;
	}
	int Lobby::GetPacket()
	{
		auto packet = m_data->m_Network->GetPacket();

		if (packet.PacketId == (short)MDNetwork::PACKET_ID::LOBBY_ENTER_RES)
		{
			auto pck = (MDNetwork::PktLobbyEnterRes*)packet.PacketData;
			//MaxUserCount; 이거는 입장가능한지 확인할수 있을것같은데
			//MaxRoomCount;는 어떻게 사용해야 할까? 
			//TODO:최대 유저수로 입장가능여부 확인?
			auto userCount = pck->MaxUserCount;
			auto roomCount = pck->MaxRoomCount;
			m_IsAvailable = true;
		}
		else if (packet.PacketId == (short)MDNetwork::PACKET_ID::LOBBY_LIST_RES)
		{

			auto LobbyInfo = (MDNetwork::PktLobbyListRes*)packet.PacketData;
			auto LobbyCount = LobbyInfo->LobbyCount;
			auto* LobbyList = LobbyInfo->LobbyList;

			for (int i = 0; i < LobbyCount; i++)
			{
				if (i > 1)
				{
					break;
				}
				auto index = LobbyList[i].LobbyId;
				m_ChennelList[i].LobbyId = index;
				m_ChennelList[i].LobbyName = Format(L"channel", index,
					L" ", LobbyList[i].LobbyUserCount, L"/50");
				m_ChennelList[i].LobbyUserCount = LobbyList[i].LobbyUserCount;

			}

		}
		return 0;
	}
}
