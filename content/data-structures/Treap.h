/**
 * Author: Gemini
 * Date: 2026-07-03
 * Source: folklore
 * Description: A short self-balancing tree. It acts as a
 *  \textit{binary tree with log-time splits/joins based on its value}, and
 *  is easy to augment with additional data.
 * Time: $O(\log N)$
 * Status: It worked on a few treap problems
 */
#pragma once

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct Node {
	Node *l = 0, *r = 0;
	ll key, y, c = 1, sum; 
	
	Node(ll key) : key(key), y(rng()), sum(key) {}
	void recalc();
};

ll cnt(Node* n) { return n ? n->c : 0; }
ll get_sum(Node* n) { return n ? n->sum : 0; }

void Node::recalc() { 
	c = cnt(l) + cnt(r) + 1; 
	sum = get_sum(l) + get_sum(r) + key;
}

// Splits Treap into L (keys <= k) and R (keys > k)
pair<Node*, Node*> split(Node* n, ll k) {
	if (!n) return {};
	if (n->key <= k) {
		auto [L, R] = split(n->r, k);
		n->r = L;
		n->recalc();
		return {n, R};
	} else {
		auto [L, R] = split(n->l, k);
		n->l = R;
		n->recalc();
		return {L, n};
	}
}

// Merges L and R. Assumes max(L->key) < min(R->key)
Node* merge(Node* l, Node* r) {
	if (!l) return r;
	if (!r) return l;
	if (l->y > r->y) {
		l->r = merge(l->r, r);
		return l->recalc(), l;
	} else {
		r->l = merge(l, r->l);
		return r->recalc(), r;
	}
}

// Inserts a new node into the correct sorted position
void insert(Node*& t, Node* n) {
	auto [L, R] = split(t, n->key);
	t = merge(merge(L, n), R);
}

// Erases all nodes with exact key 'k' (or just one if you split differently)
void erase(Node*& t, ll k) {
	auto [L, R] = split(t, k - 1);
	auto [M, RR] = split(R, k);
	// Note: if memory limit is tight, delete M here
	t = merge(L, RR);
}

// Unites two Treaps with interleaved keys. 
// log(n) if dealing with ranges that do not overlap very often. Otherwise nlogn
Node* unite(Node* l, Node* r) {
    if (!l) return r;
    if (!r) return l;
    
    if (l->y < r->y) swap(l, r); 
    auto [L, R] = split(r, l->key);
    l->l = unite(l->l, L);
    l->r = unite(l->r, R);
    l->recalc();
    return l;
}
