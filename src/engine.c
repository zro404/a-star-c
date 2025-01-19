#include "engine.h"
#include "main.h"

void Engine_Init(Engine *engine) {

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("Could not initialize SDL\n");
  }

  SDL_Window *window = SDL_CreateWindow("a-star-c", SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED, W_WIDTH,
                                        W_HEIGHT, SDL_WINDOW_SHOWN);
  if (window == NULL) {
    printf("Could not create window\n");
  }

  SDL_Surface *canvas = SDL_GetWindowSurface(window);

  engine->window = window;
  engine->canvas = canvas;
}

void Engine_Drop(Engine *engine) {
  SDL_DestroyWindow(engine->window);
  SDL_Quit();
}
