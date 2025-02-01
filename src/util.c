#include "util.h"

int imin(int i1, int i2) {
  if (i1 < i2) {
    return i1;
  }
  return i2;
}

int imax(int i1, int i2) {
  if (i1 > i2) {
    return i1;
  }
  return i2;
}
