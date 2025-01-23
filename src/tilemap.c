#include "tilemap.h"
#include "main.h"

void TileMap_Init(TileMap *grid, int row_count, int col_count) {

  grid->matrix = malloc(sizeof(TileType *) * row_count +
                        sizeof(TileType) * col_count * row_count);
  grid->col_count = col_count;
  grid->row_count = row_count;
}

TileType TileMap_get(TileMap *grid, int x, int y) {
  if (x < grid->row_count && y < grid->col_count) {
    TileType **matrix = grid->matrix;
    return matrix[x][y];
  }
  return -1;
}

void TileMap_Drop(TileMap *grid) { free(grid->matrix); }
