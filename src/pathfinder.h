#ifndef PATHFINDER_H_
#define PATHFINDER_H_

#include "main.h"
#include "tilemap.h"
#include <stdbool.h>

typedef struct Node_T {
  Tile tile;
  double f, g, h;
  struct Node_T *parent;
} Node;

typedef struct {
  Node list[C_COUNT * R_COUNT];
  int len;
} NodeList;

typedef struct {
  bool is_found;
  NodeList open_list;
  NodeList closed_list;
} PathFinder;

void PathFinder_Init(PathFinder *pathfinder);
void PathFinder_Tick(PathFinder *pathfinder, TileMap *tilemap);

#endif // PATHFINDER_H_
