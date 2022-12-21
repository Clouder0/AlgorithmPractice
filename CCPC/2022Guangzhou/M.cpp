#include <algorithm>
#include <cstdio>
#include <ctype.h>
const int bufSize = 1e6;
#define int long long
inline char nc() {
#ifdef DEBUG
  return getchar();
#endif
  static char buf[bufSize], *p1 = buf, *p2 = buf;
  return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2)
             ? EOF
             : *p1++;
}
inline void read(char *s) {
  static char c;
  for (; !isalpha(c); c = nc())
    ;
  for (; isalpha(c); c = nc())
    *s++ = c;
  *s = '\0';
}
template <typename T> inline T read(T &r) {
  static char c;
  static int flag;
  flag = 1, r = 0;
  for (c = nc(); !isdigit(c); c = nc())
    if (c == '-')
      flag = -1;
  for (; isdigit(c); c = nc())
    r = r * 10 + c - 48;
  return r *= flag;
}
long long n, m, k;
// T supports long long/int
template <const unsigned int _MOD, typename T>
struct ModNum
{
  T x;
  ModNum() { x = 0; }
  template <typename _Tp>
  ModNum(_Tp t) : x(t)
  {
  }
  ModNum(const ModNum& other) : x(other.x) {}
  explicit operator T() const { return x; }
  ModNum& operator+=(const ModNum& other)
  {
    x += other.x;
    if (this->x >= _MOD) x -= _MOD;
    return *this;
  }
  ModNum& operator-=(const ModNum& other) { return *this += _MOD - other.x; }
  ModNum& operator*=(const ModNum& other)
  {
    unsigned long long ret = 1ll * x * other.x;
    if (ret >= _MOD) ret %= _MOD;
    this->x = ret;
    return *this;
  }
  ModNum inv() const
  {
    T a = x, b = _MOD, u = 1, v = 0;
    while (b)
    {
      T t = a / b;
      a -= t * b;
      std::swap(a, b);
      u -= t * v;
      std::swap(u, v);
    }
    return ModNum(u);
  }
  ModNum& operator/=(const ModNum& other) { return *this *= other.inv(); }
  friend ModNum operator+(const ModNum& a, const ModNum& b) { return ModNum(a) += b; }
  friend ModNum operator-(const ModNum& a, const ModNum& b) { return ModNum(a) -= b; }
  friend ModNum operator*(const ModNum& a, const ModNum& b) { return ModNum(a) *= b; }
  friend ModNum operator/(const ModNum& a, const ModNum& b) { return ModNum(a) /= b; }
  bool operator==(const ModNum& other) { return x == other.x; }
  bool operator!=(const ModNum& other) { return x != other.x; }
  bool operator<(const ModNum& other) { return x < other.x; }
  bool operator>(const ModNum& other) { return x > other.x; }
  bool operator<=(const ModNum& other) { return x <= other.x; }
  bool operator>=(const ModNum& other) { return x >= other.x; }

  template <typename _Istream>
  friend _Istream& operator>>(_Istream& is, ModNum& self)
  {
    return is >> self.m_val;
  }
  template <typename _Ostream>
  friend _Ostream& operator<<(_Ostream& os, const ModNum& self)
  {
    return os << self.m_val;
  }
};
const int mod = 1e9 + 7;
int need[70], up[70], bits;
ModNum<mod, unsigned int> C[20][20];
ModNum<mod, unsigned int> f[70][500][30];
ModNum<mod, unsigned int> dfs(int bit, int left, int lim) {
  if(left < 0) return 0;
  if (bit == 0)
    return left == 0;
  left <<= 1;
  left += need[bit];
  if (left > k * k)
    return 0;
  if (f[bit][left][lim] != -1)
    return f[bit][left][lim];
  ModNum<mod, unsigned int> res = 0;
  if (up[bit] == 0) {
    // lim all zero, no other choice
    for (int i = 0; i <= k - lim; ++i) {
      // choose i in limit-less to be 1
      res += C[k - lim][i] * dfs(bit - 1, left - i * (k - i), lim);
    }
  } else {
    // lim can be 0/1, 1 still in limit while 0 free of limit
    for (int ones = 0; ones <= k; ++ones) {
      // choose ones 1 in total
      for (int from_lim = 0; from_lim <= lim && from_lim <= ones; ++from_lim) {
        // choose from_lim 1s in limited, while ones-from_lim from free
        if (k - lim >= ones - from_lim)
          res += C[lim][from_lim] * C[k - lim][ones - from_lim] *
                 dfs(bit - 1, left - ones * (k - ones), from_lim);
      }
    }
  }
  // printf("f[%d][%d][%d]=%d\n", bit, left, lim, res.x);
  return f[bit][left][lim] = res;
}
signed main() {
  read(n), read(m), read(k);
  C[0][0] = 1;
  for (int i = 1; i <= k; ++i) {
    C[i][0] = 1;
    for (int j = 1; j <= i; ++j)
      C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
  }
  int bits1 = 0;
  while (m)
    up[++bits1] = m & 1, m >>= 1;
  int bits2 = 0;
  while (n)
    need[++bits2] = n & 1, n >>= 1;
  bits = std::max(bits1, bits2);
  for (int i = 1; i <= bits; ++i)
    for (int j = 0; j <= k * k; ++j)
      for (int l = 0; l <= k; ++l)
        f[i][j][l] = -1;
  // printf("bit %d\n", bits);
  printf("%lld\n", dfs(bits, 0, k).x);
  return 0;
}