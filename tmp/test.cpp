#include <bits/stdc++.h>

using i64 = long long;

template<typename T = int, std::size_t SIZ = int(1e6)>
struct deque {
  std::vector<T> q;
  int head, tail, anchor;
  constexpr deque() { q.resize(6 * SIZ), head = tail = anchor = 6 * SIZ / 2; }
  inline constexpr T &operator[](std::size_t idx) {
    assert(idx + head < tail);
    return q[idx + head];
  }
  inline constexpr bool empty() { return head == tail; }
  inline constexpr bool full() { return head == 0 || tail == q.size() - 1; }
  inline constexpr std::size_t size() { return tail - head; }
  inline constexpr void clear() { head = tail = anchor; }
  inline constexpr void pop_back() { assert(!empty()), tail--; }
  inline constexpr void pop_front() { assert(!empty()), head++; }
  inline constexpr void push_back(const T &rhs) { q[tail++] = rhs; }
  inline constexpr void push_front(const T &rhs) { q[--head] = rhs; }
  inline constexpr T back() {
    assert(!empty());
    return q[tail - 1];
  }
  inline constexpr T front() {
    assert(!empty());
    return q[head];
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  return 0;
}