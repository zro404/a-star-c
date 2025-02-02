#include "input.h"
#include "main.h"
#include "tilemap.h"

void Handle_Touch_Input(TileMap *tilemap, int x, int y) {
  x = x / (W_WIDTH / C_COUNT);
  y = y / (W_HEIGHT / R_COUNT);

  Tile *tile = TileMap_getXY(tilemap, x, y);

  if (!tilemap->has_start) {
    tile->type = TILE_START;
    tilemap->start = tile;
    tilemap->has_start = true;
    return;
  } else if (!tilemap->has_stop) {
    tile->type = TILE_STOP;
    tilemap->stop = tile;
    tilemap->has_stop = true;
    return;
  }

  switch (tile->type) {
  case TILE_START:
    tile->type = TILE_DEFAULT;
    tilemap->has_start = false;
    break;

  case TILE_STOP:
    tile->type = TILE_DEFAULT;
    tilemap->has_stop = false;
    break;

  case TILE_DEFAULT:
    tile->type = TILE_OBSTACLE;
    break;

  default:
    tile->type = TILE_DEFAULT;
    break;
  }
}
