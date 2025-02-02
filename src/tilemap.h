#ifndef GRID_H_
#define GRID_H_

#include <stdbool.h>

typedef enum {
  TILE_DEFAULT = 0xf5f5f5,
  TILE_OBSTACLE = 0x000000,
  TILE_START = 0x32a852,
  TILE_STOP = 0xa8324c,
  TILE_OPEN = 0xd7d957,
  TILE_CLOSED = 0x3267a8,
  TILE_PATH = 0xde4ecf,
} TILETYPE;

typedef struct Tile_T {
  TILETYPE type;
  int x, y;
  double f, g, h;
  struct Tile_T *parent;
} Tile;

typedef struct {
  Tile **matrix;
  int row_count;
  int col_count;
  bool has_start;
  bool has_stop;
  Tile *start;
  Tile *stop;
} TileMap;

void TileMap_Init(TileMap *tilemap, int row_count, int col_count);
void TileMap_Drop(TileMap *tilemap);

Tile *TileMap_getXY(TileMap *tilemap, int x, int y);
Tile *TileMap_getTile(TileMap *tilemap, Tile *tile);

double Euclidean_Distance(Tile *t1, Tile *t2);

bool Tile_Equals(Tile *t1, Tile *t2);

#endif // GRID_H_
