#include <cstdio>

template <typename T> T fastpow(T x, T k) {
  T res = 1;
  while (k) {
    if (k & 1)
      res = res * x;
    x = x * x;
    k >>= 1;
  }
  return res;
}

template <typename T> T modpow(T x, T k, T mod) {
  k %= (mod - 1); // Fermat's little theorem
  T res = 1;
  while (k) {
    if (k & 1)
      res = res * x % mod;
    x = x * x % mod;
    k >>= 1;
  }
  return res;
}

int main() { return 0; }