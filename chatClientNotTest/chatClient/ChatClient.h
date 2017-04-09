#pragma once
class ChatClient
{
public:
	ChatClient();
	~ChatClient();

	int Update();
private:

	//TODO: 2.스테이트 패턴을 사용해서 윈도우 간의 전환.
	GUI loginWindow;
	//TODO: 1.우선 메인 윈도우 부터 구현
	GUI mainWindow;

	String loginID{};
	String loginPassWord{};

	//TODO:나중에 지울거
	const Font font;
	const Font font2;

};

