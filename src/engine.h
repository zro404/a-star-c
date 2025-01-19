#ifndef ENGINE_H_
#define ENGINE_H_

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
typedef struct {
  SDL_Window *window;
  SDL_Surface *canvas;
} Engine;

void Engine_Init(Engine *engine);
void Engine_Drop(Engine *engine);

#endif // ENGINE_H_
