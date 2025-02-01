#ifndef GRID_H_
#define GRID_H_

#include <stdbool.h>

typedef enum {
  TILE_PATH = 0xff00ff,
  TILE_CLOSED = 0x0000ff,
  TILE_OPEN = 0xffff00,
  TILE_START = 0x00ff00,
  TILE_STOP = 0xff0000,
  TILE_DEFAULT = 0xffffff,
  TILE_OBSTACLE = 0x000000,
} TILETYPE;

typedef struct {
  int x;
  int y;
} Tile;

typedef struct {
  TILETYPE **matrix;
  int row_count;
  int col_count;
  bool has_start;
  bool has_stop;
  Tile start;
  Tile stop;
} TileMap;

void TileMap_Init(TileMap *tilemap, int row_count, int col_count);
void TileMap_Drop(TileMap *tilemap);

TILETYPE *TileMap_getXY(TileMap *tilemap, int x, int y);
TILETYPE *TileMap_getTile(TileMap *tilemap, Tile *tile);

double Euclidean_Distance(Tile t1, Tile t2);

bool Tile_Equals(Tile t1, Tile t2);

#endif // GRID_H_
