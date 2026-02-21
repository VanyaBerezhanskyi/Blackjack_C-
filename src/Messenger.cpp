#include "Messenger.h"

Messenger& Messenger::getInstance()
{
	static Messenger instance;

	return instance;
}

void Messenger::broadcastEvent(Uint32 e, void* param1, void* param2)
{
	SDL_Event event{};

	event.type = e;

	event.user.data1 = param1;
	event.user.data2 = param2;

	SDL_PushEvent(&event);
}