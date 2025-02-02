#ifndef PATHFINDER_H_
#define PATHFINDER_H_

#include "main.h"
#include "tilemap.h"
#include <stdbool.h>

typedef struct {
  Tile **list;
  int len;
} NodeList;

typedef struct {
  bool is_found;
  NodeList open_list;
  NodeList closed_list;
} PathFinder;

void PathFinder_Init(PathFinder *pathfinder);
void PathFinder_Tick(PathFinder *pathfinder, TileMap *tilemap);
void PathFinder_Drop(PathFinder *pathfinder);

#endif // PATHFINDER_H_
