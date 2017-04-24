#include "pch.h"
#include "ChatMain.h"
#include "../../network/Client/Client/Network.h"
namespace chatClient
{


	void ChatMain::init()
	{
		Window::Resize(1280, 720);

		/* 디버깅용 박스 출력
		showWindow.style.showBoxModel = true;
		inputWindow.style.showBoxModel = true;
		roomWindow.style.showBoxModel = true;
		memberWindow.style.showBoxModel = true;
		*/
		MakeRoomIndex();

		InitRoomWindow();

		InitInputWindow();

		InitShowWindow();

		MakeMemberIndex();

		InitMemberWindow();

		//roomInfos.reserve(20);
	}

	void ChatMain::update()
	{

		if (m_IsRoomListEnd == false)
		{
			SendGetRoomListPacket();

		}
		else
		{
			SetRoomList();
			++m_timer;
			if (m_timer < 60)
			{
				m_IsRoomListEnd = false;
				IsRoomSeted = false;
				m_timer = 0;
			}
		}

		GetPacket();

		CheckRoomListButton();
		if (m_RoomId > 0 && m_RoomId <= 7)
		{
			GetMemberList();
			SetMemberList();
			updateTextField();
		}
		else
		{
		}



	}

	int ChatMain::updateTextField()
	{
		if (m_RoomId > 0 && m_RoomId <= 7)
		{
			inputWindow.textArea(L"InputField").enabled = true;
			showWindow.textArea(L"ShowField").enabled = true;
			showWindow.textArea(L"ShowField").setText(m_PresentText);
			if (inputWindow.textArea(L"InputField").hasChanged)
			{
				auto str = inputWindow.textArea(L"InputField")._get_text();
				if (str.endsWith(L'\n'))
				{
					m_PresentText = m_PresentText + str;
					inputWindow.textArea(L"InputField").setText(L"");
				}
			}
		}
		else
		{
			inputWindow.textArea(L"InputField").enabled = false;
			showWindow.textArea(L"ShowField").enabled = false;
			return 0;
		}
		return 0;
	}

	int ChatMain::GetPacket()
	{
		auto packet = m_data->m_Network->GetPacket();

		if (m_IsRoomListEnd == false && packet.PacketId == (short)PACKET_ID::LOBBY_ENTER_ROOM_LIST_RES)
		{
			auto roomList = (PktLobbyRoomListRes*)packet.PacketData;
			auto count = roomList->Count - m_RoomIndex + 1;
			m_RoomIndex = roomList->Count;
			auto* roomInfo = roomList->RoomInfo;
			for (int i = 0; i < count; ++i)
			{
				roomInfos[i].RoomTitle = roomInfo->RoomTitle;
				roomInfos[i].RoomIndex = roomInfo->RoomIndex;
				roomInfos[i].RoomUserCount = roomInfo->RoomUserCount;
			}
			m_IsRoomListEnd = roomList->IsEnd;
			m_IsGeted == true;
		}

		return 0;
	}

	int ChatMain::SendGetRoomListPacket()
	{
		if (m_IsGeted == false)
		{
			return -10;
		}

		m_RoomIndex = m_RoomIndex +1;
		PktLobbyRoomListReq getRoomListPacket{ 0, };
		getRoomListPacket.StartRoomIndex = m_RoomIndex;

		auto returnVal = m_data->m_Network->Send(
			(short)PACKET_ID::LOBBY_ENTER_ROOM_LIST_REQ,
			sizeof(getRoomListPacket),
			(char*)&getRoomListPacket);

		m_IsGeted = false;

		return returnVal;
	}

	int ChatMain::SetRoomList()
	{
		if (IsRoomSeted)
		{
			for (int i = 0; i < 20; ++i)
			{
				roomWindow.text(roomIndex[i]).text = roomInfos[i].RoomTitle;
			}

			IsRoomSeted = true;
		}

		return 0;
	}

	int ChatMain::GetMemberList()
	{
		//서버로 부터 멤버 리스트를 받아온다.
		//변화가 있는지 확인을 해야됨
		return 0;
	}

	int ChatMain::SetMemberList()
	{
		SetGuiText(memberWindow, L"Member1", L"person1");
		SetGuiText(memberWindow, L"Member2", L"person2");
		SetGuiText(memberWindow, L"Member3", L"person3");
		SetGuiText(memberWindow, L"Member4", L"person4");
		SetGuiText(memberWindow, L"Member5", L"person5");

		return 0;
	}
	int ChatMain::CheckRoomListButton()
	{
		if (roomWindow.button(L"Room1Button").pushed)
		{
			//서버에서 받아오는 방번호를 받아오는 부분
			m_RoomId = 1;
		}
		else if (roomWindow.button(L"Room2Button").pushed)
		{
			m_RoomId = 2;
		}
		else if (roomWindow.button(L"Room3Button").pushed)
		{
			m_RoomId = 3;
		}
		else if (roomWindow.button(L"Room4Button").pushed)
		{
			m_RoomId = 4;
		}
		else if (roomWindow.button(L"Room5Button").pushed)
		{
			m_RoomId = 5;
		}
		else if (roomWindow.button(L"Room6Button").pushed)
		{
			m_RoomId = 6;
		}
		else if (roomWindow.button(L"Room7Button").pushed)
		{
			m_RoomId = 7;
		}
		else if (roomWindow.button(L"LobbyButton").pushed)
		{
			m_RoomId = -1;
			changeScene(L"Lobby");
		}

		return 0;
	}

	void ChatMain::draw() const
	{
	}

	int ChatMain::InitRoomWindow()
	{

		roomWindow.setTitle(L"Room List");
		for (int i = 0; i < 20; i++)
		{
			AddTextAndButton(roomWindow, i, L"Room");
		}

		roomWindow.add(L"Lobby", GUIText::Create(L"To Lobby"));
		roomWindow.text(L"Lobby").style.width = 100;
		roomWindow.addln(L"LobbyButton", GUIButton::Create(L"Enter"));

		roomWindow.setPos(Point(0, 0));
		roomWindow.style.width = 250;

		return 1;
	}

	int ChatMain::InitInputWindow()
	{
		auto pos = roomWindow.getPos();

		auto dPos = roomWindow.getRect();

		auto WindowPos = static_cast<Point>(Window::Size());

		inputWindow.setTitle(L"Input");

		inputWindow.addln(L"InputField", GUITextArea::Create(2, 30));

		auto dWindowPos = inputWindow.getRect();

		inputWindow.setPos(Point(pos.x + dPos.w, WindowPos.y - dWindowPos.h));

		return 1;
	}

	int ChatMain::InitShowWindow()
	{
		auto pos = roomWindow.getPos();

		auto dPos = roomWindow.getRect();
		showWindow.setTitle(Format(L"Channel ID:",m_data->m_LobbyId));
		showWindow.addln(L"ShowField", GUITextArea::Create(25, 30));
		showWindow.setPos(Point(pos.x + dPos.w, 0));

		return 1;
	}

	int ChatMain::InitMemberWindow()
	{
		auto pos = roomWindow.getPos();

		auto dPos = roomWindow.getRect();

		memberWindow.setTitle(L"Member");

		for (int i = 0; i < 5; i++)
		{
			AddText(memberWindow, i, L"Empty");
		}

		memberWindow.setPos(Point(0, pos.y + dPos.h));

		memberWindow.style.width = 250;

		return 1;
	}

	int ChatMain::AddTextAndButton(GUI gui, int listIndex, String name)
	{
		auto index = roomIndex[listIndex];
		gui.add(index, GUIText::Create(name));
		gui.text(index).style.width = 100;

		auto indexButton = index + String(L"Button");
		gui.addln(indexButton, GUIButton::Create(L"Enter"));

		return 1;
	}

	int ChatMain::AddText(GUI gui, int listIndex, String name)
	{
		auto index = memberIndex[listIndex];
		gui.addln(index, GUIText::Create(name));
		gui.text(index).style.width = 100;

		return 1;
	}

	int ChatMain::MakeRoomIndex()
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

	int ChatMain::MakeMemberIndex()
	{
		memberIndex[0] = L"Member1";
		memberIndex[1] = L"Member2";
		memberIndex[2] = L"Member3";
		memberIndex[3] = L"Member4";
		memberIndex[4] = L"Member5";

		return 1;
	}

	int ChatMain::SetGuiText(GUI gui, String textName, String newText)
	{
		gui.text(textName).text = newText;
		return 0;
	}

}
