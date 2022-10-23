#include <algorithm>
#include <cstdio>
using namespace std;
#define ll long long
int n;
ll p;
int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19};
ll f1[1 << 8][1 << 8], f2[1 << 8][1 << 8], g[1 << 8][1 << 8];
inline ll add(ll a, ll b)
{
    ll res = a + b;
    if (res >= p) res -= p;
    return res;
}
struct node
{
    int val, S, big;
} A[510];
bool cmp(const node& a, const node& b)
{
    return a.big < b.big;
}
int main()
{
    scanf("%d %lld", &n, &p);
    for (int i = 2; i <= n; ++i)
    {
        A[i - 1].val = i;
        int x = i;
        for (int j = 0; j < 8; ++j)
            if ((x % primes[j]) == 0)
            {
                A[i - 1].S |= (1 << j);
                while ((x % primes[j]) == 0) x /= primes[j];
            }
        A[i - 1].big = x;
    }
    sort(A + 1, A + n, cmp);
    g[0][0] = 1;
    for (int i = 1; i < n; ++i)
    {
        if (A[i].big == 1 || A[i].big != A[i - 1].big)
            for (int j = 0; j < (1 << 8); ++j)
                for (int k = 0; k < (1 << 8); ++k) f1[j][k] = f2[j][k] = g[j][k];
        for (int j = (1 << 8) - 1; j >= 0; --j)
            for (int k = (1 << 8) - 1; k >= 0; --k)
            {
                if (!(j & A[i].S)) f1[j][k | A[i].S] = add(f1[j][k | A[i].S], f1[j][k]);
                if (!(k & A[i].S)) f2[j | A[i].S][k] = add(f2[j | A[i].S][k], f2[j][k]);
            }
        if (A[i].big == 1 || A[i].big != A[i + 1].big)
        {
            for (int j = (1 << 8) - 1; j >= 0; --j)
                for (int k = (1 << 8) - 1; k >= 0; --k)
                    g[j][k] = add(p - g[j][k], add(f1[j][k], f2[j][k]));
        }
    }
    ll res = 0;
    for (int i = 0; i < (1 << 8); ++i)
        for (int j = 0; j < (1 << 8); ++j) res = add(res, g[i][j]);
    printf("%lld\n", res);
    return 0;
}