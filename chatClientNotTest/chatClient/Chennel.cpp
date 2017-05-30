#include "pch.h"
#include "Chennel.h"
#include "../../network/Client/Client/Network.h"

namespace MDNetwork
{


	void Chennel::init()
	{
		Window::Resize(1280, 720);

		/* 디버깅용 박스 출력
		showWindow.style.showBoxModel = true;
		inputWindow.style.showBoxModel = true;
		roomWindow.style.showBoxModel = true;
		memberWindow.style.showBoxModel = true;
		*/

		MakeRoomIndex(5);

		InitRoomWindow();

		InitInputWindow();

		InitShowWindow();

		MakeMemberIndex(20);

		InitMemberWindow();

		//roomInfos.reserve(20);
	}

	void Chennel::update()
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

		UpdateLobbyMember();

		CheckRoomListButton();
		if (m_RoomId > 0 && m_RoomId <= 5)
		{
			GetMemberList();
			SetMemberList();

		}
		else
		{
		}

		updateTextField();


	}

	int Chennel::updateTextField()
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

		return 0;
	}

	int Chennel::GetPacket()
	{
		//auto packet = m_data->m_Network->GetPacket();
		////TODO: 언오디드 맵을 사용하는것이 좋음.
		//if (m_IsRoomListEnd == false && packet.PacketId == (short)MDNetwork::PACKET_ID::LOBBY_ENTER_ROOM_LIST_RES)
		//{
		//	auto roomList = (MDNetwork::PktLobbyRoomListRes*)packet.PacketData;
		//	auto count = roomList->Count - m_RoomIndex + 1;
		//	m_RoomIndex = roomList->Count;
		//	auto* roomInfo = roomList->RoomInfo;
		//	for (int i = 0; i < count; ++i)
		//	{
		//		roomInfos[i].RoomTitle = roomInfo->RoomTitle;
		//		roomInfos[i].RoomIndex = roomInfo->RoomIndex;
		//		roomInfos[i].RoomUserCount = roomInfo->RoomUserCount;
		//	}
		//	m_IsRoomListEnd = roomList->IsEnd;
		//	m_IsGeted == true;
		//}
		//else if (packet.PacketId = (short)MDNetwork::PACKET_ID::LOBBY_ENTER_USER_NTF)
		//{
		//	auto newMemberPacket = (MDNetwork::PktLobbyNewUserInfoNtf*)packet.PacketData;
		//	
		//	char *memberId = newMemberPacket->UserID;
		//	wchar_t wMemberId[16];
		//	Util::AnsiToUnicode(memberId, 16, wMemberId);
		//	
		//	for (auto iter : m_members)
		//	{
		//		if (iter.IsEmpty == true)
		//		{
		//			iter.MenberId = wMemberId;
		//			break;
		//		}
		//	}
		//}
		//
		//
		return 0;
	}

	int Chennel::SendGetRoomListPacket()
	{
		//if (m_IsGeted == false)
		//{
		//	return -10;
		//}
		//
		//m_RoomIndex = m_RoomIndex +1;
		//MDNetwork::PktLobbyRoomListReq getRoomListPacket{ 0, };
		//getRoomListPacket.StartRoomIndex = m_RoomIndex;
		//
		//auto returnVal = m_data->m_Network->Send(
		//	(short)MDNetwork::PACKET_ID::LOBBY_ENTER_ROOM_LIST_REQ,
		//	sizeof(getRoomListPacket),
		//	(char*)&getRoomListPacket);
		//
		//m_IsGeted = false;
		//
		//return returnVal;

		return 0;
	}

	int Chennel::SetRoomList()
	{
		//if (IsRoomSeted)
		//{
		//	for (int i = 0; i < 20; ++i)
		//	{
		//		roomWindow.text(roomIndex[i]).text = roomInfos[i].RoomTitle;
		//	}
		//
		//	IsRoomSeted = true;
		//}
		//
		return 0;
	}

	int Chennel::UpdateLobbyMember()
	{

		memberWindow.text(L"Member1").text = m_members[0].MenberId;
		memberWindow.text(L"Member2").text = m_members[1].MenberId;
		memberWindow.text(L"Member3").text = m_members[2].MenberId;
		memberWindow.text(L"Member4").text = m_members[3].MenberId;
		memberWindow.text(L"Member5").text = m_members[4].MenberId;

		return 0;
	}

	int Chennel::GetMemberList()
	{
		//서버로 부터 멤버 리스트를 받아온다.
		//변화가 있는지 확인을 해야됨
		return 0;
	}

	int Chennel::SetMemberList()
	{
		SetGuiText(memberWindow, L"Member1", L"person1");
		SetGuiText(memberWindow, L"Member2", L"person2");
		SetGuiText(memberWindow, L"Member3", L"person3");
		SetGuiText(memberWindow, L"Member4", L"person4");
		SetGuiText(memberWindow, L"Member5", L"person5");

		return 0;
	}
	int Chennel::CheckRoomListButton()
	{
		for (int i = 0; i < 5; ++i)
		{
			auto buttonIndex = roomIndex[i] + String(L"Button");
			if (roomWindow.button(buttonIndex).pushed)
			{
				m_RoomId = i + 1;
			}
		}

		if (roomWindow.button(L"LobbyButton").pushed)
		{
			m_RoomId = -1;
			changeScene(L"Lobby");
		}

		return 0;
	}

	void Chennel::draw() const
	{
	}

	int Chennel::InitRoomWindow()
	{
		roomWindow.setTitle(L"Room List");
		for (int i = 0; i < 5; i++)
		{
			AddTextAndButton(roomWindow, i, roomIndex[i]);
		}

		roomWindow.add(L"Lobby", GUIText::Create(L"Exit to Login"));
		roomWindow.text(L"Lobby").style.width = 100;
		roomWindow.addln(L"LobbyButton", GUIButton::Create(L"Enter"));

		roomWindow.setPos(Point(0, 0));
		roomWindow.style.width = 250;

		return 1;
	}

	int Chennel::InitInputWindow()
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

	int Chennel::InitShowWindow()
	{
		auto pos = roomWindow.getPos();

		auto dPos = roomWindow.getRect();
		showWindow.setTitle(Format(L"Channel ID:", m_data->m_LobbyInfo.LobbyId));
		showWindow.addln(L"ShowField", GUITextArea::Create(25, 30));
		showWindow.setPos(Point(pos.x + dPos.w, 0));

		return 1;
	}

	int Chennel::InitMemberWindow()
	{
		auto pos = showWindow.getPos();

		auto dPos = showWindow.getRect();

		memberWindow.setTitle(L"Member");

		for (int i = 0; i < 20; i++)
		{
			AddText(memberWindow, i, memberIndex[i]);
		}

		memberWindow.setPos(Point(pos.x + dPos.w, 0));

		memberWindow.style.width = 250;

		return 1;
	}

	int Chennel::AddTextAndButton(GUI gui, int listIndex, String name)
	{
		auto index = roomIndex[listIndex];
		gui.add(index, GUIText::Create(name));
		gui.text(index).style.width = 100;

		auto indexButton = index + String(L"Button");
		gui.addln(indexButton, GUIButton::Create(L"Enter"));

		return 1;
	}

	int Chennel::AddText(GUI gui, int listIndex, String name)
	{
		auto index = memberIndex[listIndex];
		gui.addln(index, GUIText::Create(name));
		gui.text(index).style.width = 100;

		return 1;
	}

	int Chennel::MakeRoomIndex(int pNum)
	{
		for (int i = 0; i < pNum; ++i)
		{
			roomIndex[i] = Format(L"Room", i + 1, L":");
		}

		return 1;
	}

	int Chennel::MakeMemberIndex(int pNum)
	{
		for (int i = 0; i < pNum; ++i)
		{
			memberIndex[i] = Format(L"Member", i + 1, L":");
		}
		return 1;
	}

	int Chennel::SetGuiText(GUI gui, String textName, String newText)
	{
		gui.text(textName).text = newText;
		return 0;
	}

}
