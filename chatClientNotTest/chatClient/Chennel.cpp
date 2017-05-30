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

		//방 리스트 받아오기
		GetRoomList();
		//멤버 리스트 받아오기

		//roomInfos.reserve(20);
	}

	void Chennel::update()
	{
		//입장 공지 확인
		CheckNewMenber();

		SetNewUser();
		
		//퇴장 공지 확인

		//방정보 갱신 확인

		//채팅 확인
		

		CheckRoomListButton();
		if (m_RoomId > 0 && m_RoomId <= 5)
		{
			GetMemberList();
			SetMemberList();

		}
		else
		{
		}
		//처음 받아오 방,멤버의 리스트 갱신된 리스트를 표시하는 함수.
		UpdateLobbyMember();
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

	int Chennel::SetRoomList()
	{
		//if (IsRoomSeted)
		//{
		//	for (int i = 0; i < 20; ++i)
		//	{
		//		roomWindow.text(m_RoomIndex[i]).text = roomInfos[i].RoomTitle;
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
			auto buttonIndex = m_RoomIndex[i] + String(L"Button");
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

	bool Chennel::CheckNewMenber()
	{
		m_data->m_Logic->IsThereNewUser();
		char m_NewUser[MAX_USER_ID_SIZE + 1];
		m_data->m_Logic->GetNewUser(m_NewUser);

		if (*m_NewUser != '\0')
		{
			wchar_t buffer[MAX_USER_ID_SIZE + 1];
			Util::AnsiToUnicode(m_NewUser, MAX_USER_ID_SIZE + 1, buffer);
			m_NewUserId.push_back(buffer);

			return true;
		}

		return false;
	}

	void Chennel::SetNewUser()
	{

		for (auto user : m_MemberList)
		{
			if (m_NewUserId.empty())
			{
				break;
			}

			if (user.IsEmpty)
			{
				user.MenberId = m_NewUserId.front();
				m_NewUserId.pop_front();
			}
		}
	}

	int Chennel::GetRoomList()
	{
		m_data->m_Logic->SendPktRoomList(0);

		auto lastRoomindex = m_data->m_Logic->TryGetRoomList();

		for (int i = 0; i <= lastRoomindex; ++i)
		{
			auto roomInfo = m_data->m_Logic->CopyRoomList();
			short index, count;
			String title;

			std::tie(index, count, title) = roomInfo;

			m_RoomList[i].RoomIndex = index;
			m_RoomList[i].RoomUserCount = count;
			m_RoomList[i].RoomTitle = title;
		}
		
		return 0;
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

	int Chennel::InitRoomWindow()
	{
		roomWindow.setTitle(L"Room List");
		for (int i = 0; i < 5; i++)
		{
			AddTextAndButton(roomWindow, i, m_RoomIndex[i]);
		}

		roomWindow.add(L"Lobby", GUIText::Create(L"Exit to Login"));
		roomWindow.text(L"Lobby").style.width = 100;
		roomWindow.addln(L"LobbyButton", GUIButton::Create(L"Enter"));

		roomWindow.setPos(Point(0, 0));
		roomWindow.style.width = 250;

		return 1;
	}

	int Chennel::InitMemberWindow()
	{
		auto pos = showWindow.getPos();

		auto dPos = showWindow.getRect();

		memberWindow.setTitle(L"Member");

		for (int i = 0; i < 20; i++)
		{
			AddText(memberWindow, i, m_MemberIndex[i]);
		}

		memberWindow.setPos(Point(pos.x + dPos.w, 0));

		memberWindow.style.width = 250;

		return 1;
	}

	int Chennel::AddTextAndButton(GUI gui, int listIndex, String name)
	{
		auto index = m_RoomIndex[listIndex];
		gui.add(index, GUIText::Create(name));
		gui.text(index).style.width = 100;

		auto indexButton = index + String(L"Button");
		gui.addln(indexButton, GUIButton::Create(L"Enter"));

		return 1;
	}

	int Chennel::AddText(GUI gui, int listIndex, String name)
	{
		auto index = m_MemberIndex[listIndex];
		gui.addln(index, GUIText::Create(name));
		gui.text(index).style.width = 100;

		return 1;
	}

	int Chennel::MakeRoomIndex(int pNum)
	{
		for (int i = 0; i < pNum; ++i)
		{
			m_RoomIndex[i] = Format(L"Room", i + 1, L":");
		}

		return 1;
	}

	int Chennel::MakeMemberIndex(int pNum)
	{
		for (int i = 0; i < pNum; ++i)
		{
			m_MemberIndex[i] = Format(L"Member", i + 1, L":");
		}
		return 1;
	}

	int Chennel::SetGuiText(GUI gui, String textName, String newText)
	{
		gui.text(textName).text = newText;
		return 0;
	}


	void Chennel::draw() const
	{
	}

}
