﻿// Siv3D March 2016
#include "ChatClient.h"
#include "Login.h"
#include "Lobby.h"
#include "Chennel.h"
#include "ChatMain.h"


const char IpAddr[] = "127.0.0.1";
const int Port = 23452;


void Main()
{
	//Window::Resize(1280, 720);

	Graphics::SetBackground(Color(70, 80, 170));
	
	//--++네트워크 객체 생성
	MDNetwork::SocketNetwork network;
	//윈속 초기화
	network.Init();
	//서버에 커넥트 시도 //성공하면 리시브 스레드 생성됨. 
	//리시브 펑크가 돌아감. //윈도우 api 리시브는 블럭함수 이므로 패킷을 받을때까지 스레드는 블럭됨.
	network.Connect(IpAddr, Port);

	//--++네트워크 인터페이스 객체 생성
	MDNetwork::NetworkInterface networkInterface;

	//네트워크 객체로 부터 패킷을 담을 큐를 받아옴, ppl컨테이너 사용.
	networkInterface.SetRawPacketQue(network.GetReceivedPacketQue());

	//네트워크 인터페이스 스레드 패킷을 분류하고, 각각의 옵저버들에게 패킷도착을 알려준다.
	networkInterface.run();

	//--++로직 클래스 생성.
	MDNetwork::ClientLogic logic;

	//네트워크 객체로 부터 패킷을 보내는 함수를 받아온다.
	logic.GetNetworkSendFunc(network.GetSendFunc());



	//--++옵저버들 생성.


	//--옵저버:LOGIN_IN_RES
	MDNetwork::LoginObserver loginObserver;
	
	//등록:옵저버->서브젝트
	networkInterface.Subscribe(static_cast<short>(
		MDNetwork::PACKET_ID::LOGIN_IN_RES),
		loginObserver.GetLOGIN_IN_RES_Func());

	//등록:로직->옵저버
	logic.SetLOGIN_IN_RES_Que(
		loginObserver.GetLOGIN_IN_RES_Que());


	//--옵저버:LOBBY_LIST_RES
	MDNetwork::LobbyObserver lobbyObserver;

	//등록:옵저버->서브젝트
	networkInterface.Subscribe(static_cast<short>(
		MDNetwork::PACKET_ID::LOBBY_LIST_RES),
		lobbyObserver.GetLOBBY_LIST_RES_Func());

	//등록:로직->옵저버
	logic.SetLOBBY_LIST_RES_Que(
		lobbyObserver.GetLOBBY_LIST_RES_Que());


	//--옵저버:LOBBY_ENTER_RES

	//등록:옵저버->서브젝트
	networkInterface.Subscribe(static_cast<short>(
		MDNetwork::PACKET_ID::LOBBY_ENTER_RES),
		lobbyObserver.GetLOBBY_ENTER_RES_Func());

	//등록:로직->옵저버
	logic.SetLOBBY_ENTER_RES_Que(
		lobbyObserver.GetLOBBY_ENTER_RES_Que());


	//--옵저버:LOBBY_ENTER_USER_NTF

	//등록:옵저버->서브젝트
	networkInterface.Subscribe(static_cast<short>(
		MDNetwork::PACKET_ID::LOBBY_ENTER_USER_NTF),
		lobbyObserver.GetLOBBY_ENTER_USER_NTF_Func());

	//등록:로직->옵저버
	logic.SetLOBBY_ENTER_USER_NTF_Que(
		lobbyObserver.GetLOBBY_ENTER_USER_NTF_Que());
	
	
	//--옵저버:LOBBY_ENTER_ROOM_LIST_RES

	//등록:옵저버->서브젝트
	networkInterface.Subscribe(static_cast<short>(
		MDNetwork::PACKET_ID::LOBBY_ENTER_ROOM_LIST_RES),
		lobbyObserver.GetLOBBY_ENTER_ROOM_LIST_RES_Func());

	//등록:로직->옵저버
	logic.SetLOBBY_ENTER_ROOM_LIST_RES_Que(
		lobbyObserver.GetPktLobbyRoomListResQue());

	
	//--옵저버:LOBBY_ENTER_USER_LIST_RES
	
	//등록:옵저버->서브젝트
	networkInterface.Subscribe(static_cast<short>(
		MDNetwork::PACKET_ID::LOBBY_ENTER_USER_LIST_RES),
		lobbyObserver.GetLOBBY_ENTER_USER_LIST_RES_Func());
	//등록:로직->옵저버
	logic.SetLOBBY_ENTER_USER_LIST_RES_Que(
		lobbyObserver.GetPktLobbyUserListResQue());
	
	
	//--옵저버:LOBBY_LEAVE_RES
	
	//등록:옵저버->서브젝트
	networkInterface.Subscribe(static_cast<short>(
		MDNetwork::PACKET_ID::LOBBY_LEAVE_RES),
		lobbyObserver.GetLOBBY_LEAVE_RES_Func());
	//등록:로직->옵저버
	logic.SetLOBBY_LEAVE_RES_Que(
		lobbyObserver.GetPktLobbyLeaveResQue());
	
	
	//--옵저버:LOBBY_LEAVE_USER_NTF
	
	//등록:옵저버->서브젝트
	networkInterface.Subscribe(static_cast<short>(
		MDNetwork::PACKET_ID::LOBBY_LEAVE_USER_NTF),
		lobbyObserver.GetLOBBY_LEAVE_USER_NTF_Func());
	
	//등록:로직->옵저버
	logic.SetLOBBY_LEAVE_USER_NTF(
		lobbyObserver.GetPktLobbyLeaveUserInfoNtfQue());


	//--++옵저버:LOBBY_CHAT_RES

	//등록:옵저버->서브젝트
	networkInterface.Subscribe(static_cast<short>(
		MDNetwork::PACKET_ID::LOBBY_CHAT_RES),
		lobbyObserver.GetLOBBY_CHAT_RES_Func());
	//등록:로직->옵저버
	logic.SetLOBBY_CHAT_RES(
		lobbyObserver.GetPktLobbyChatResQue());

	//--++옵저버:LOBBY_CHAT_NTF

	//등록:옵저버->서브젝트
	networkInterface.Subscribe(static_cast<short>(
		MDNetwork::PACKET_ID::LOBBY_CHAT_NTF),
		lobbyObserver.GetLOBBY_CHAT_NTF_Func());
	//등록:로직->옵저버
	logic.SetLOBBY_CHAT_NTF(
		lobbyObserver.GetPktLobbyChatNtfQue());

	//--++옵저버:
	//등록:옵저버->서브젝트
	//등록:로직->옵저버

	//Siv3D 신 관리 매니저.
	Manager manager;
	
	manager.add<MDNetwork::Login>(L"Login");
	manager.add<MDNetwork::Lobby>(L"Lobby");
	manager.add<MDNetwork::Chennel>(L"Chennel");
	manager.add<MDNetwork::ChatMain>(L"ChatMain");
	manager.get()->m_Logic = &logic;
	while (System::Update())
	{
		if (!manager.updateAndDraw())
		{
			break;
		}
	}

	networkInterface.SetIsEnd();
}