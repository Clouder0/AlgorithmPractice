#include <algorithm>
#include <cstdio>
using namespace std;
#define int unsigned long long
int n, p, q, A, B, P[30], Q[30], lP, lQ;
int minLen, ansp, ansq;
int minn;
int num2arr(int num, int* arr)
{
    int p = 0;
    while (num) arr[++p] = num % 10, num /= 10;
    return p;
}
int arr2num(int* arr, int len)
{
    __int128 res = 0;
    for (int i = len; i; --i) res = res * 10 + arr[i];
    return res;
}
int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }
int subp[30], subq[30], erased[30], bin[10], bin2[10], leadZero1;
bool check(int a[], int b[], int la, int lb)
{
    for (int i = 0; i <= 9; ++i) bin2[i] = 0;
    int p = 1;
    for (int i = 1; i <= lb; ++i)
    {
        while (p <= la && a[p] != b[i])
        {
            bin2[a[p]]++;
            ++p;
        }
        if (p > la) return false;
        ++p;
    }
    int leadZero = 0;
    while (p <= la)
    {
        if (a[p] != 0)
            bin2[a[p]]++;
        else
            ++leadZero;
        ++p;
    }
    for (int i = 1; i <= 9; ++i)
        if (bin[i] != bin2[i]) return false;
    return bin[0] >= bin2[0] && bin[0] <= bin2[0] + leadZero;
    return true;
}
void dfs(int pos, int len, int elen)
{
    if (pos == lP + 1)
    {
        if (!len) return;
        __int128 nowp = arr2num(subp, len);
        if (nowp >= minn) return;
        if (nowp == 0) return;
        if (nowp % A != 0) return;
        __int128 nowq = nowp / A * B;
        int lsq = num2arr(nowq, subq);
        for (int i = 0; i <= 9; ++i) bin[i] = 0;
        for (int i = 1; i <= elen; ++i) bin[erased[i]]++;
        if (!check(Q, subq, lQ, lsq)) return;
        minn = nowp, minLen = len, ansp = nowp, ansq = nowq;
        return;
    }
    erased[elen + 1] = P[pos];
    dfs(pos + 1, len, elen + 1);
    subp[len + 1] = P[pos];
    dfs(pos + 1, len + 1, elen);
}
signed main()
{
    scanf("%llu", &n);
    while (n--)
    {
        minLen = 40;
        minn = 1ull << 63;
        scanf("%llu%llu", &p, &q);
        int g = gcd(p, q);
        if (g == 1)
        {
            printf("%llu %llu\n", p, q);
            continue;
        }
        A = p / g, B = q / g;
        lP = num2arr(p, P), lQ = num2arr(q, Q);
        dfs(1, 0, 0);
        printf("%llu %llu\n", ansp, ansq);
    }
    return 0;
}