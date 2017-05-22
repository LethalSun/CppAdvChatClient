#pragma once
//TODO: pch 는 많이 수정되지 않는 파일, 디파인은 
#include <Siv3D.hpp>
#include <HamFramework.hpp>
#include <array>
#include <unordered_map>
#include <vector>
#include <string>
#include "Define.h"
#include "MyScene.h"

using Manager = SceneManager<String, chatClient::MyScene>;