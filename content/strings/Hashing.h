
/**
 * Author: Simon Lindholm
 * Date: 2015-03-15
 * License: CC0
 * Source: own work
 * Description:\\
\begin{minipage}{75mm}
Self-explanatory methods for string hashing. 
When comparing $n^2$ strings, change: 
--- ll -> \_\_int128  
--- static const \_\_int128 M = (\_\_int128(1) << 61) - 1;
\end{minipage}
\begin{minipage}{15mm}
\includegraphics[width=\textwidth]{content/strings/HashingScenarios}
\end{minipage}
 * Status: stress-tested
 */
#pragma once

struct HashedString {
  static const ll M = 1e9 + 9;
  static ll B;
  // pow[i] contains B^i % M
  static vector<ll> pow;
  // p_hash[i] is the hash of the first i characters of the given string
  vector<ll> p_hash;

  // can be changed to vi
  HashedString(const string& s) : p_hash(s.size() + 1) {
    while (pow.size() <= s.size()) {
      pow.push_back((pow.back() * B) % M);
    }

    p_hash[0] = 0;
    for (int i = 0; i < s.size(); i++) {
      p_hash[i + 1] = ((p_hash[i] * B) % M + s[i]) % M;
    }
  }

  // r inclusive, 0 index
  ll get_hash(int start, int end) {
    ll raw_val = (p_hash[end + 1] - (p_hash[start] * pow[end - start + 1]));
    return (raw_val % M + M) % M;
  }
};

ll HashedString::B = rng(HashedString::M - 1);
vi HashedString::pow = {1};
