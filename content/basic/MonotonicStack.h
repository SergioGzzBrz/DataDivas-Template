/**
 * Author: Sergio
 * Date: 2026-07-30
 * Source: folklore
 * Description: Decreasing Monotonic Stack. Finds nearest bigger values 
 * to left and right
 * Time: $O(N)$
 */
#pragma once

void solve() {
  ll n;
  cin >> n;
  vi a(n);
  trav(u, a) {
    cin >> u;
  };
  stack<pi> s;

  // gets all subarrays in range (l, r) exclusive including m
  auto getNumberOfSubarrays = [&](ll l, ll m, ll r) {
    ll left = m - l;
    ll right = r - m;
    return left * right;
  };

  ll ans = 0;
  rep(i, 0, n) {
    ll x = a[i], xi = i;

    // change to > for increasing stack
    while (sz(s) && s.top().f < x) {
      auto [y, yi] = s.top();
      s.pop();
      if (sz(s)) {
        // max between (zi, xi) not inclusive
        auto [z, zi] = s.top();
        ans += y * getNumberOfSubarrays(zi, yi, xi);
      } else {
        ans += y * getNumberOfSubarrays(-1, yi, xi);
      }
    }

    s.emplace(x, xi);
  }

  while (sz(s)) {
    auto [y, yi] = s.top();
    s.pop();
    if (sz(s)) {  // (copy this from rep above)
      // max between (zi, n) not inclusive
      auto [z, zi] = s.top();
      ans += y * getNumberOfSubarrays(zi, yi, n);
    } else {
      ans += y * getNumberOfSubarrays(-1, yi, n);
    }
  }
  cout << ans << endl;
}
