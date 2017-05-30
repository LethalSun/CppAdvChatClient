#pragma once
#include <iostream>
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <thread>
#include <mutex>
#include <unordered_map>
#include <array>
#include <deque>
#include <concurrent_queue.h>
#include <concurrent_unordered_map.h>
#include <algorithm>
#include <functional>
#include "Util.h"
#include "Packet.h"
#include "PacketID.h"
#include "Usings.h"

const int MaxPacketSize = 1024;
const int BUFFERSIZE = 4096;
