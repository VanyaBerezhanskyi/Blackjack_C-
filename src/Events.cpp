#include "Events.h"

Uint32 GAME_STARTED = SDL_RegisterEvents(1);
Uint32 HIT_BUTTON_PRESSED = SDL_RegisterEvents(1);
Uint32 STAND_BUTTON_PRESSED = SDL_RegisterEvents(1);
Uint32 PLAYER_SUM_UPDATED = SDL_RegisterEvents(1);
Uint32 DEALER_SUM_UPDATED = SDL_RegisterEvents(1);
Uint32 PLAYER_WIN = SDL_RegisterEvents(1);
Uint32 PLAYER_LOSE = SDL_RegisterEvents(1);
Uint32 DRAW = SDL_RegisterEvents(1);
Uint32 ROUND_ENDED = SDL_RegisterEvents(1);
Uint32 CARDS_RETURNED = SDL_RegisterEvents(1);
Uint32 GAME_ENDED = SDL_RegisterEvents(1);