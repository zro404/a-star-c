#ifndef GRID_H_
#define GRID_H_

typedef enum {
  TILE_CLOSED = 0x0000ff,
  TILE_OPEN = 0xffff00,
  TILE_START = 0x00ff00,
  TILE_STOP = 0xff0000,
  TILE_DEFAULT = 0xffffff,
} TILETYPE;

typedef struct {
  TILETYPE **matrix;
  int row_count;
  int col_count;
} TileMap;

void TileMap_Init(TileMap *tilemap, int row_count, int col_count);
void TileMap_Drop(TileMap *tilemap);

TILETYPE *TileMap_get(TileMap *tilemap, int x, int y);

#endif // GRID_H_
