/**
 * Author: Simon Lindholm
 * Date: 2016-03-22
 * License: CC0
 * Source: hacKIT, NWERC 2015
 * Description: A multiset with support for finding the n'th
 * element, and finding the index of an element.
 * Erase and count don't work immediately.
 * lower_bound and upper_bound are swapped here
 * Time: O(\log N)
 */
#pragma once

#include <bits/extc++.h> /** keep-include */
using namespace __gnu_pbds;

template <class value, class cmp = less_equal<value> >
using ordered_multiset =
    tree<value, null_type, cmp, rb_tree_tag, tree_order_statistics_node_update>;

template <class T>
int erase_all(ordered_multiset<T>& s, const T& element) {
  int erased = 0;
  auto it = s.lower_bound(element - 1);
  while (it != s.end() && *it == element) {
    s.erase(it++);
    erased++;
  }
  return erased;
}

template <class T>
int count_all(ordered_multiset<T>& s, const T& element) {
  return s.order_of_key(element + 1) - s.order_of_key(element);
}