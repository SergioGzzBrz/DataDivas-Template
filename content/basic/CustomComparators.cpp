// Compare function
auto cmp = [](ll a, ll b) { return a < b; };

// Custom set comparator 
set<ll, decltype(cmp)> s; // c++20
set<ll, decltype(cmp)> s(cmp); // c++11

// Custom priority queue comparison
priority_queue<ll, vi, decltype(cmp)> pq(cmp);
priority_queue<ll, vi, greater<>> pq; // built-in greater

