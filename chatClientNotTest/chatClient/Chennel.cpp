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
		GetUserList();
		SetUserList();
		//roomInfos.reserve(20);
	}

	void Chennel::update()
	{
		SetRoomList();
	
		//입장 공지 확인
		CheckNewMenber();

		SetNewUser();
		
		//퇴장 공지 확인
		CheckLeavedMember();

		RemoveUser();

		//방정보 갱신 확인


		//채팅 확인
		GetTextFromInput();

		CheckRoomListButton();

		//방에 입장,로비 퇴장
		if (m_RoomId > 0 && m_RoomId <= 5)
		{

		}
		else
		{

		}

		//방,멤버의 리스트 갱신표시하는 함수.
		UpdateLobbyMember();
		UpdateLobbyRoom();
		//메시지를 갱신한다.
		updateTextField();


	}

	int Chennel::updateTextField()
	{
		showWindow.textArea(L"ShowField").setText(m_PresentText);
		return 0;
	}

	int Chennel::SetRoomList()
	{
		auto lastRoomindex = m_data->m_Logic->TryGetRoomList();

		for (int i = 0; i <= lastRoomindex; ++i)
		{
			std::wstring buffer;
			auto roomInfo = m_data->m_Logic->CopyRoomList(buffer);
			short index, count;


			std::tie(index, count) = roomInfo;

			m_RoomList[i].RoomIndex = index;
			m_RoomList[i].UserCount = count;
			m_RoomList[i].Title = buffer;
		}
		return 0;
	}

	int Chennel::UpdateLobbyMember()
	{
		int i = 0;
		for (auto user : m_MemberList)
		{
			if (!user.IsEmpty)
			{
				SetGuiText(memberWindow, m_MemberIndex[i], user.MenberId);
			}
			++i;
		}
		return 0;
	}

	int Chennel::UpdateLobbyRoom()
	{
		int i = 0;
		for (auto room : m_RoomList)
		{
			if (room.RoomIndex != -1)
			{
				auto id = room.RoomIndex;
				auto title = room.Title;
				auto usercount = room.UserCount;

				String newStr = Format(m_RoomIndex[i], title, usercount, L"/4", L"[", id, L"]");

				SetGuiText(roomWindow, m_RoomIndex[i], newStr);
			}
		}
		return 0;
	}

	void Chennel::GetTextFromInput()
	{
		inputWindow.textArea(L"InputField").enabled = true;
		showWindow.textArea(L"ShowField").enabled = true;
		showWindow.textArea(L"ShowField").setText(m_PresentText);

		if (inputWindow.textArea(L"InputField").hasChanged)
		{
			auto str = inputWindow.textArea(L"InputField")._get_text();
			if (str.endsWith(L'\n'))
			{
				m_data->m_Logic->SendPktLobbyChatReq(str.c_str());
				inputWindow.textArea(L"InputField").setText(L"");
			}
		}

		m_data->m_Logic->CollectMsg();

		std::wstring buffer;

		m_data->m_Logic->GetMsg(buffer);

		String msg = buffer;

		if (m_PresentText.endsWith(L'\n'))
		{
			m_PresentText += msg;
		}
		else
		{
			m_PresentText += L'\n' + msg;
		}
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
			auto id = Util::CharToWstring(m_NewUser).c_str();
			m_NewUserId.push_back(id);

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

	bool Chennel::CheckLeavedMember()
	{
		m_data->m_Logic->IsThereLevedUser();
		char m_LevedUser[MAX_USER_ID_SIZE + 1];
		m_data->m_Logic->GetLevedUser(m_LevedUser);

		if (*m_LevedUser != '\0')
		{
			auto id = Util::CharToWstring(m_LevedUser).c_str();
			m_LeavedUserId.push_back(id);

			return true;
		}

		return false;
	}

	void Chennel::RemoveUser()
	{

		while (!m_LeavedUserId.empty())
		{
			for (auto user : m_MemberList)
			{
				if (!user.IsEmpty)
				{
					if (user.MenberId == m_LeavedUserId.front())
					{
						m_LeavedUserId.pop_front();
						user.IsEmpty = true;
						user.MenberId.clear();
					}
				}
			}
		}
	}

	int Chennel::GetRoomList()
	{
		m_data->m_Logic->SendPktRoomList(0);
		
		return 0;
	}

	int Chennel::GetUserList()
	{
		//m_data->m_Logic->SendPktLobbyUserList(0);

		return 0;
	}

	int Chennel::SetUserList()
	{
		auto lastUserIndex = m_data->m_Logic->TryGetUserList();

		for (int i = 0; i <= lastUserIndex; ++i)
		{
			std::wstring buffer;
			auto userinfo = m_data->m_Logic->CopyUserList(buffer);

				m_MemberList[i].MenberId = buffer;
				m_MemberList[i].IsEmpty = false;
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
		inputWindow.textArea(L"InputField").enabled = true;

		return 1;
	}

	int Chennel::InitShowWindow()
	{
		auto pos = roomWindow.getPos();

		auto dPos = roomWindow.getRect();
		showWindow.setTitle(Format(L"Channel ID:", m_data->m_LobbyInfo.LobbyId));
		showWindow.addln(L"ShowField", GUITextArea::Create(25, 30));
		showWindow.setPos(Point(pos.x + dPos.w, 0));
		showWindow.textArea(L"ShowField").enabled = true;
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
