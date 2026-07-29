/**
 * Author: Unknown
 * Date: 2026-07-29
 * Source: folklore
 * Description: Calculates a pow b mod in log(b)
 * Status: Works
 */
#pragma once

ll fastpow(ll a, ll b) {
  ll res = 1;
  while (b > 0) {
    if (b & 1) {
      res = res * a % mod;
    }
    a = a * a % mod;
    b >>= 1;
  }
  return res;
}
