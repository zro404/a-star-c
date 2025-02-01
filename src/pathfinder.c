#include "pathfinder.h"
#include "main.h"
#include "tilemap.h"
#include <stdio.h>

Node Node_New(Tile tile, Node parent);
Node NodeList_Pop(NodeList *node_list, int i);

void Plot_Path(TileMap *tilemap, Node stop);
void Update_TileMap(TileMap *tilemap, NodeList *open_list,
                    NodeList *closed_list);

void PathFinder_Init(PathFinder *pathfinder) {
  pathfinder->is_found = false;

  NodeList open_list;
  open_list.len = 0;
  pathfinder->open_list = open_list;

  NodeList closed_list;
  closed_list.len = 0;
  pathfinder->closed_list = closed_list;
}

void PathFinder_Tick(PathFinder *pathfinder, TileMap *tilemap) {
  NodeList *ol = &pathfinder->open_list;
  NodeList *cl = &pathfinder->closed_list;
  if (ol->len == 0 && cl->len == 0) {
    Node s_node = {.tile = tilemap->start, .f = 0.0f, .h = 0.0f, .g = 0.0f};
    s_node.parent = NULL;
    ol->list[ol->len++] = s_node;
  }

  if (ol->len != 0) {
    int min = 0;
    double min_val = ol->list[0].f;
    for (int i = 0; i < ol->len; i++) {
      if (ol->list[i].f <= min_val) {
        min = i;
      }
    }

    Node min_node = ol->list[min];

    // Expand to min's neighbors
    Node nl[8];
    int ni = -1;
    Node n;

    for (int i = -1; i <= 1; i++) {
      for (int j = -1; j <= 1; j++) {
        if (i == 0 && j == 0)
          continue;

        Tile t = min_node.tile;

        int x = t.x + i;
        int y = t.y + j;

        if (x < 0 || y < 0 || x > C_COUNT || y > R_COUNT)
          continue;

        Tile nt = {x, y};
        n = Node_New(nt, min_node);
        n.g = min_node.g + Euclidean_Distance(t, nt);
        n.h = Euclidean_Distance(nt, tilemap->stop);
        n.f = n.g + n.h;

        nl[++ni] = n;
      }
    }

    for (int i = 0; i <= ni; i++) {
      if (Tile_Equals(nl[i].tile, tilemap->stop)) {
        /* Plot_Path(tilemap, nl[i]); */
        pathfinder->is_found = true;
        /* return; */
        break;
      }

      for (int j = 0; j < ol->len; j++) {
        if (Tile_Equals(nl[i].tile, ol->list[j].tile)) {
          if (nl[i].f > ol->list[j].f) {
            continue;
          }
        }
      }

      for (int j = 0; j < cl->len; j++) {
        if (Tile_Equals(nl[i].tile, cl->list[j].tile)) {
          if (nl[i].f < cl->list[j].f) {
            cl->list[j] = nl[i];
            continue;
          }
        }
      }

      ol->list[ol->len++] = nl[i];
    }

    cl->list[cl->len++] = NodeList_Pop(ol, min);

    Update_TileMap(tilemap, ol, cl);
  }
}

void Update_TileMap(TileMap *tilemap, NodeList *open_list,
                    NodeList *closed_list) {
  for (int i = 0; i < open_list->len; i++) {
    *TileMap_getTile(tilemap, &open_list->list[i].tile) = TILE_OPEN;
  }

  for (int i = 0; i < closed_list->len; i++) {
    *TileMap_getTile(tilemap, &closed_list->list[i].tile) = TILE_CLOSED;
  }
}

// BUG
void Plot_Path(TileMap *tilemap, Node stop) {
  Node *node = &stop;
  while (node->parent != NULL) {
    *TileMap_getTile(tilemap, &node->tile) = TILE_PATH;
    node = node->parent;
  }
}

Node Node_New(Tile tile, Node parent) {
  Node node = {
      tile, 0.0f, 0.0f, 0.0f, &parent,
  };
  return node;
}

Node NodeList_Pop(NodeList *node_list, int i) {
  Node n = node_list->list[i];
  node_list->list[i] = node_list->list[node_list->len - 1];
  node_list->len--;
  return n;
}
