#pragma once
class ChatClient
{
public:
	ChatClient();
	~ChatClient();

	int Update();
private:

	//TODO: �Ű��� ��°��� �����Ѵ�.https://github.com/Siv3D/Reference-JP/wiki/%E3%82%B7%E3%83%BC%E3%83%B3%E7%AE%A1%E7%90%86

	//TODO: 1.�켱 ���� ������ ����
	//���� ���� ü���� �̷������ ����

	//TODO: 2.��ȭ�� ����
	//��ȭ�� �ִ� ����.

	//TODO: Ŭ���̾�Ʈ�� ����ɶ� ������ �����ϴ� ���� ���� ��Ʈ��Ʈ �ڿ��� �������Ѵ�.
	//TODO: MaxClientCount = 2000 
	//ExtraClientCount = 64 
	//MaxLobbyCount = 2 
	//MaxLobbyUserCount = 50 
	//MaxRoomCountByLobby = 20 
	//MaxRoomUserCount = 4

	String chatInput{};
	//TODO:���߿� �����
	const Font font;
	const Font font2;

};

