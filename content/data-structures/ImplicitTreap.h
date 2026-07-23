/**
 * Author: Gemini
 * Date: 2026-07-22
 * Source: kactl
 * Description: A short self-balancing tree. It acts as a
 *  \textit{sequential container with log-time splits/joins based on index}, and
 *  is easy to augment with additional data.
 * Time: $O(\log N)$
 * Status: stress-tested
 */
#pragma once

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct Node {
  Node *l = 0, *r = 0;
  ll val, y, c = 1;

  Node(ll val) : val(val), y(rng()) {}
  void recalc();
};

ll cnt(Node* n) {
  return n ? n->c : 0;
}
void Node::recalc() {
  c = cnt(l) + cnt(r) + 1;
}

// In-order traversal (reconstructs the dynamic array)
template <class F>
void each(Node* n, F f) {
  if (n) {
    each(n->l, f);
    f(n->val);
    each(n->r, f);
  }
}

// Splits into L (first k elements) and R (the rest)
pair<Node*, Node*> split(Node* n, ll k) {
  if (!n)
    return {};
  if (cnt(n->l) >= k) {
    auto [L, R] = split(n->l, k);
    n->l = R;
    n->recalc();
    return {L, n};
  } else {
    auto [L, R] = split(n->r, k - cnt(n->l) - 1);
    n->r = L;
    n->recalc();
    return {n, R};
  }
}

// Merges L and R. Assumes L comes before R in array order.
Node* merge(Node* l, Node* r) {
  if (!l)
    return r;
  if (!r)
    return l;
  if (l->y > r->y) {
    l->r = merge(l->r, r);
    return l->recalc(), l;
  } else {
    r->l = merge(l, r->l);
    return r->recalc(), r;
  }
}

// Inserts a node 'n' at array index 'pos'
void insert(Node*& t, Node* n, ll pos) {
  auto [L, R] = split(t, pos);
  t = merge(merge(L, n), R);
}

// Moves the subarray [l, r) so that it starts at index k
void move(Node*& t, ll l, ll r, ll k) {
  auto [a, bc] = split(t, l);
  auto [b, c] = split(bc, r - l);

  if (k <= l) {
    auto [a1, a2] = split(a, k);
    t = merge(merge(merge(a1, b), a2), c);
  } else {
    auto [c1, c2] = split(c, k - r);
    t = merge(merge(a, c1), merge(b, c2));
  }
}