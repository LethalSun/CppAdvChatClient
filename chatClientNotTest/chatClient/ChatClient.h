#pragma once
class ChatClient
{
public:
	ChatClient();
	~ChatClient();

	int Update();
private:

	//TODO: 2.������Ʈ ������ ����ؼ� ������ ���� ��ȯ.
	GUI loginWindow;
	//TODO: 1.�켱 ���� ������ ���� ����
	GUI mainWindow;

	String loginID{};
	String loginPassWord{};

	//TODO:���߿� �����
	const Font font;
	const Font font2;

};

