#include "engine.h"
#include "main.h"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_surface.h>
#include <stdio.h>

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

void Engine_Draw_TileMap(Engine *engine, TileMap *tilemap) {
  SDL_Rect rect = {
      .w = W_WIDTH / C_COUNT, .h = W_HEIGHT / R_COUNT, .x = 0, .y = 0};

  for (int i = 0; i < tilemap->row_count; i++) {
    for (int j = 0; j < tilemap->col_count; j++) {
      SDL_FillRect(engine->canvas, &rect,
                   SDL_MapRGB(engine->canvas->format, 0xFF, i * 25, j * 25));
      rect.x += rect.w;
    }
    rect.x = 0;
    rect.y += rect.h;
  }
}
