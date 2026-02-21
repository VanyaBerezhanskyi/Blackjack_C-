#pragma once

#include "SDL.h"

class Messenger
{
public:
	static Messenger& getInstance();

	void broadcastEvent(Uint32 e, void* param1 = nullptr, void* param2 = nullptr);
};