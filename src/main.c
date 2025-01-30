#include "main.h"
#include "engine.h"
#include "input.h"
#include "tilemap.h"
#include <SDL2/SDL_events.h>

int main() {
  Engine engine;
  Engine_Init(&engine);

  TileMap tilemap;
  TileMap_Init(&tilemap, R_COUNT, C_COUNT);

  SDL_Event e;

  int i = 0;

  bool quit = false;
  while (!quit) {
    while (SDL_PollEvent(&e)) {
      switch (e.type) {
      case SDL_KEYDOWN:
        if (e.key.keysym.sym == SDLK_ESCAPE) {
          quit = true;
        }
        break;
      case SDL_MOUSEBUTTONDOWN:
        Handle_Touch_Input(&tilemap, e.button.x, e.button.y);
        break;
      case SDL_QUIT:
        quit = true;
        break;
      default:
        break;
      }
    }

    /* SDL_FillRect(engine.canvas, NULL, */
    /*              SDL_MapRGB(engine.canvas->format, 0xFF, 0x0, i)); */

    Engine_Draw_TileMap(&engine, &tilemap);

    if (i == 255) {
      i = 0;
    } else {
      i++;
    }

    SDL_UpdateWindowSurface(engine.window);
    usleep(16666);
  }

  TileMap_Drop(&tilemap);
  Engine_Drop(&engine);

  return 0;
}
