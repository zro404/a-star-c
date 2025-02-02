#include "pathfinder.h"
#include "main.h"
#include "tilemap.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void PathFinder_Init(PathFinder *pathfinder) {
  pathfinder->is_found = false;

  NodeList open_list;
  open_list.len = 0;
  open_list.list = malloc(sizeof(Tile *) * C_COUNT * R_COUNT);
  pathfinder->open_list = open_list;

  NodeList closed_list;
  closed_list.len = 0;
  closed_list.list = malloc(sizeof(Tile *) * C_COUNT * R_COUNT);
  pathfinder->closed_list = closed_list;
}

void PathFinder_Tick(PathFinder *pf, TileMap *tilemap) {
  NodeList *ol = &pf->open_list;
  NodeList *cl = &pf->closed_list;
  if (ol->len == 0 && cl->len == 0) {
    ol->list[ol->len++] = tilemap->start;
  }

  if (ol->len > 0) {
    double min_val = ol->list[0]->f;
    Tile *min;
    int min_i;
    for (int i = 0; i < ol->len; i++) {
      if (min_val >= ol->list[i]->f) {
        min = ol->list[i];
        min_val = min->f;
        min_i = i;
      }
    }

    ol->list[min_i] = ol->list[ol->len - 1];
    ol->len--;

    // Generate Neighbors
    for (int i = -1; i <= 1; i++) {
      for (int j = -1; j <= 1; j++) {
        if (i == 0 && j == 0)
          continue;

        int x = min->x + i;
        int y = min->y + j;

        if (x < 0 || y < 0 || x >= C_COUNT || y >= R_COUNT)
          continue;

        Tile *node = TileMap_getXY(tilemap, x, y);

        if (node->type == TILE_OBSTACLE)
          continue;

        if (node == tilemap->stop) {
          node->parent = min;
          while (node != NULL) {
            if (node == tilemap->stop) {
              node = node->parent;
              continue;
            }
            node->type = TILE_PATH;
            if (node == tilemap->start) {
              node->type = TILE_START;
            }
            node = node->parent;
          }
          pf->is_found = true;
          return;
        }

        double f, h, g = 0;
        if (node->parent) {
          g = node->parent->g + Euclidean_Distance(node, node->parent);
        }
        h = Euclidean_Distance(node, tilemap->stop);
        f = g + h;

        bool skip = false;
        for (int k = 0; k < ol->len; k++) {
          if (node == ol->list[k]) {
            if (f > ol->list[k]->f) {
              skip = true;
              break;
            }
          }
        }
        if (skip)
          continue;

        for (int k = 0; k < cl->len; k++) {
          if (node == cl->list[k]) {
            if (f > cl->list[k]->f) {
              skip = true;
              break;
            }
          }
        }
        if (skip)
          continue;

        node->f = f;
        node->g = g;
        node->h = h;
        node->parent = min;
        ol->list[ol->len++] = node;
        if (node != tilemap->start) {
          node->type = TILE_OPEN;
        }
      }
    }
    cl->list[cl->len++] = min;
    if (min != tilemap->start) {
      min->type = TILE_CLOSED;
    }
  }
}

void PathFinder_Drop(PathFinder *pathfinder) {
  free(pathfinder->open_list.list);
  free(pathfinder->closed_list.list);
}
