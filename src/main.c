#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

const uint32_t W_WIDTH = 1280;
const uint32_t W_HEIGHT = 720;

int main() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("Could not initialize SDL\n");
  }

  SDL_Window *window = SDL_CreateWindow("a-star-c", SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED, W_WIDTH,
                                        W_HEIGHT, SDL_WINDOW_SHOWN);

  if (window == NULL) {
    printf("Could not create window\n");
  } else {
    SDL_Surface *canvas = SDL_GetWindowSurface(window);
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

      SDL_FillRect(canvas, NULL, SDL_MapRGB(canvas->format, 0xFF, 0x0, i));

      if (i == 255) {
        i = 0;
      } else {
        i++;
      }

      SDL_UpdateWindowSurface(window);
      usleep(16666);
    }
  }

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
