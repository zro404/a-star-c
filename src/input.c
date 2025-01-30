#include "input.h"
#include "main.h"
#include "tilemap.h"
#include <stdio.h>

void Handle_Touch_Input(TileMap *tilemap, int x, int y) {
  x = x / (W_WIDTH / C_COUNT);
  y = y / (W_HEIGHT / R_COUNT);

  TILETYPE *tile = TileMap_get(tilemap, x, y);

  if (!tilemap->has_start) {
    *tile = TILE_START;
    tilemap->has_start = true;
    return;
  } else if (!tilemap->has_stop) {
    *tile = TILE_STOP;
    tilemap->has_stop = true;
    return;
  }

  switch (*tile) {
  case TILE_START:
    *tile = TILE_DEFAULT;
    tilemap->has_start = false;
    break;

  case TILE_STOP:
    *tile = TILE_DEFAULT;
    tilemap->has_stop = false;
    break;

  case TILE_DEFAULT:
    *tile = TILE_OBSTACLE;
    break;

  default:
    *tile = TILE_DEFAULT;
    break;
  }
}
