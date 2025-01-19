#include "main.h"
#include "engine.h"
#include "grid.h"

int main() {
  Engine engine;
  Engine_Init(&engine);

  Grid grid;
  Grid_Init(&grid, R_COUNT, C_COUNT);

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
      case SDL_QUIT:
        quit = true;
        break;
      default:
        break;
      }
    }

    SDL_FillRect(engine.canvas, NULL,
                 SDL_MapRGB(engine.canvas->format, 0xFF, 0x0, i));

    if (i == 255) {
      i = 0;
    } else {
      i++;
    }

    SDL_UpdateWindowSurface(engine.window);
    usleep(16666);
  }

  Grid_Drop(&grid);
  Engine_Drop(&engine);

  return 0;
}
