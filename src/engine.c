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
  const int PADDING = 5;
  SDL_Rect tile_rect = {.w = (W_WIDTH / C_COUNT) - PADDING,
                        .h = (W_HEIGHT / R_COUNT) - PADDING,
                        .x = PADDING / 2,
                        .y = PADDING / 2};

  SDL_Rect border_rect = {
      .w = W_WIDTH / C_COUNT, .h = W_HEIGHT / R_COUNT, .x = 0, .y = 0};

  for (int i = 0; i < tilemap->row_count; i++) {
    for (int j = 0; j < tilemap->col_count; j++) {
      SDL_FillRect(engine->canvas, &border_rect, 0x000000);
      SDL_FillRect(engine->canvas, &tile_rect, tilemap->matrix[i][j].type);
      tile_rect.x += tile_rect.w + PADDING;
      border_rect.x += border_rect.w;
    }
    tile_rect.x = PADDING / 2;
    tile_rect.y += tile_rect.h + PADDING;
  }
}
