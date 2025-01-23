#ifndef GRID_H_
#define GRID_H_

typedef enum {
  CLOSED,
  OPEN,
  START,
  STOP,
} TileType;

typedef struct {
  TileType **matrix;
  int row_count;
  int col_count;
} TileMap;

void TileMap_Init(TileMap *grid, int row_count, int col_count);
void TileMap_Drop(TileMap *grid);

TileType TileMap_get(TileMap *grid, int x, int y);

#endif // GRID_H_
