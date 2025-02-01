#include "tilemap.h"
#include "main.h"
#include <math.h>
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
      *TileMap_getXY(tilemap, i, j) = TILE_DEFAULT;
    }
  }

  tilemap->has_start = false;
  tilemap->has_stop = false;

  Tile t = {0, 0};

  tilemap->start = t;
  tilemap->stop = t;
}

TILETYPE *TileMap_getXY(TileMap *tilemap, int x, int y) {
  if (x < tilemap->row_count && y < tilemap->col_count) {
    TILETYPE **matrix = tilemap->matrix;
    return &matrix[y][x];
  }
  return NULL;
}

TILETYPE *TileMap_getTile(TileMap *tilemap, Tile *tile) {
  if (tile->x < tilemap->row_count && tile->y < tilemap->col_count) {
    TILETYPE **matrix = tilemap->matrix;
    return &matrix[tile->y][tile->x];
  }
  return NULL;
}

void TileMap_Drop(TileMap *tilemap) { free(tilemap->matrix); }

double Euclidean_Distance(Tile t1, Tile t2) {
  return sqrt(pow(t1.x - t2.x, 2) + pow(t1.y - t2.y, 2));
}

bool Tile_Equals(Tile t1, Tile t2) { return t1.x == t2.x && t1.y == t2.y; }
