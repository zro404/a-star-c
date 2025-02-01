#include "input.h"
#include "main.h"
#include "tilemap.h"
#include <stdio.h>

void Handle_Touch_Input(TileMap *tilemap, int x, int y) {
  x = x / (W_WIDTH / C_COUNT);
  y = y / (W_HEIGHT / R_COUNT);

  TILETYPE *current_tile = TileMap_getXY(tilemap, x, y);
  Tile tile = {x, y};

  if (!tilemap->has_start) {
    *current_tile = TILE_START;
    tilemap->start = tile;
    tilemap->has_start = true;
    return;
  } else if (!tilemap->has_stop) {
    *current_tile = TILE_STOP;
    tilemap->stop = tile;
    tilemap->has_stop = true;
    return;
  }

  switch (*current_tile) {
  case TILE_START:
    *current_tile = TILE_DEFAULT;
    tilemap->has_start = false;
    break;

  case TILE_STOP:
    *current_tile = TILE_DEFAULT;
    tilemap->has_stop = false;
    break;

  case TILE_DEFAULT:
    *current_tile = TILE_OBSTACLE;
    break;

  default:
    *current_tile = TILE_DEFAULT;
    break;
  }
}
