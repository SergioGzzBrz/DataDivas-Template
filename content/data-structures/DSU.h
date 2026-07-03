/**
 * Author: Unkown
 * Date: 2022-1-1
 * License: CC0
 * Source: idk
 * Description: Disjoint-set data structure.
 * Time: $O(\alpha(N))$
 */
#pragma once

const int MAXN = 1e5;
int dsu[MAXN + 1], rankk[MAXN + 1]{};

int get(int node) {
  return dsu[node] = (dsu[node] != node) ? get(dsu[node]) : node;
}

void dsu_union(int a, int b) {
  a = get(a); b = get(b);
  if (a == b)return;
  if (rankk[a] == rankk[b]) rankk[a]++;
  if (rankk[a] > rankk[b]) {
    dsu[b] = a;
  } else {
    dsu[a] = b;
  }
}
