#include "tilemap.h"
#include "main.h"
#include <stdio.h>

void TileMap_Init(TileMap *tilemap, int row_count, int col_count) {
  tilemap->matrix = malloc(sizeof(TILETYPE *) * row_count);
  for (int i = 0; i < col_count; i++) {
    tilemap->matrix[i] = malloc(sizeof(TILETYPE) * col_count);
  }

  tilemap->col_count = col_count;
  tilemap->row_count = row_count;

  for (int i = 0; i < row_count; i++) {
    for (int j = 0; j < col_count; j++) {
      *TileMap_get(tilemap, i, j) = TILE_DEFAULT;
    }
  }
}

TILETYPE *TileMap_get(TileMap *tilemap, int x, int y) {
  if (x < tilemap->row_count && y < tilemap->col_count) {
    TILETYPE **matrix = tilemap->matrix;
    return &matrix[x][y];
  }
  return NULL;
}

void TileMap_Drop(TileMap *tilemap) { free(tilemap->matrix); }
