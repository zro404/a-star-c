#include "main.h"
#include "engine.h"
#include "input.h"
#include "pathfinder.h"
#include "tilemap.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>

int main() {
  Engine engine;
  Engine_Init(&engine);

  TileMap tilemap;
  TileMap_Init(&tilemap, R_COUNT, C_COUNT);

  PathFinder pathfinder;
  PathFinder_Init(&pathfinder);

  SDL_Event e;

  bool is_editable = true;
  bool quit = false;
  while (!quit) {
    while (SDL_PollEvent(&e)) {
      switch (e.type) {
      case SDL_KEYDOWN:
        if (e.key.keysym.sym == SDLK_ESCAPE) {
          quit = true;
        } else if (e.key.keysym.sym == SDLK_SPACE) {
          is_editable = false;
        }
        break;
      case SDL_MOUSEBUTTONDOWN:
        if (is_editable) {
          Handle_Touch_Input(&tilemap, e.button.x, e.button.y);
        }
        break;
      case SDL_QUIT:
        quit = true;
        break;
      default:
        break;
      }
    }

    if (!is_editable && !pathfinder.is_found) {
      PathFinder_Tick(&pathfinder, &tilemap);
    }

    Engine_Draw_TileMap(&engine, &tilemap);

    SDL_UpdateWindowSurface(engine.window);
    usleep(1000000 / FRAME_RATE);
  }

  TileMap_Drop(&tilemap);
  Engine_Drop(&engine);

  return 0;
}
