/**
 * Author: Gemini
 * Date: 2026-07-22
 * Source: kactl
 * Description: A short self-balancing tree. It acts as a
 *  \textit{sequential container with log-time splits/joins based on index}, and
 *  is easy to augment with additional data AND lazy queries / updates (same as ST).
 *  For lazy, add push function before merge and split
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
  if (!n) return;
	each(n->l, f);
	f(n->val);
	each(n->r, f);
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
  auto [L, R] = split(t, pos-1);
  t = merge(merge(L, n), R);
}
