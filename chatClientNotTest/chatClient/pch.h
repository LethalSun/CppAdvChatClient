#pragma once
//TODO: pch �� ���� �������� �ʴ� ����, �������� 
#include <Siv3D.hpp>
#include <HamFramework.hpp>
#include <array>
#include <unordered_map>
#include <vector>
#include <string>
#include "Define.h"
#include "MyScene.h"
#include "../../network/Client/Client/SocketNetwork.h"
#include "../../network/Client/Client/NetworkInterface.h"
#include "../../network/Client/Client/ClientLogic.h"
#include "../../network/Client/Client/LoginObserver.h"
#include "../../network/Client/Client/LobbyObserver.h"
using Manager = SceneManager<String, MDNetwork::MyScene>;