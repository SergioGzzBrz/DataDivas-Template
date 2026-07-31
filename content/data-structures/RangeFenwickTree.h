/**
 * Author: Gemini
 * Date: 2026-07-31
 * Description: Computes partial sums a[0] + a[1] + ... + a[pos - 1], and updates 
 * a range of elements a[i:j].
 * Time: Both operations are $O(\log N)$.
 * Status: Some testing
 */
#pragma once

struct FT {
  vector<ll> s0, s1;
  FT(int n) : s0(n), s1(n) {}
  void add(int pos, ll dif) {
    for (int i = pos; i < sz(s0); i |= i + 1)
      s0[i] += dif, s1[i] += dif * pos;
  }
  void update(int l, int r, ll dif) { // a[i] += dif for i in [l, r)
    add(l, dif); add(r, -dif);
  }
  ll query(int pos) { // sum of values in [0, pos)
    ll res = 0;
    for (int i = pos; i > 0; i &= i - 1)
      res += pos * s0[i-1] - s1[i-1];
    return res;
  }
  ll query(int l, int r) { // sum of values in [l, r)
    return query(r) - query(l);
  }
};
