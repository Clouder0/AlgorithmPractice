#include <cstdio>
#include <vector>
#include <algorithm>
#include <ctype.h>
const int bufSize = 1e6;
using namespace std;
inline char nc()
{
    #ifdef DEBUG
    return getchar();
    #endif
    static char buf[bufSize], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
}
template<typename T>
inline T read(T &r)
{
    static char c;
    static int flag;
    flag = 1, r = 0;
    for (c = nc(); !isdigit(c); c = nc()) if (c == '-') flag = -1;
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r *= flag;
}
const int maxn = 6e3 + 100;
int T,n;
int H[maxn],cnt;
int L[maxn],R[maxn];
vector<int> V[maxn];
int f[maxn][maxn];
void dfs(int l,int r)
{
    if(f[l][r] != -1) return;
    f[l][r] = 0;
    if(l > r) return;
    dfs(l, r - 1), dfs(l + 1, r);
    f[l][r] = max(f[l][r - 1], f[l + 1][r]);
    int num = 0;
    for(vector<int>::iterator it = V[r].begin();it!=V[r].end();++it)
    {
        int L = *it;
        if (L == l) ++num;
        else if (L - 1 >= l) dfs(l, L - 1), dfs(L, r), f[l][r] = max(f[l][r], f[l][L - 1] + f[L][r]);
    }
    f[l][r] += num;
}
int main()
{
    read(T);
    while(T--)
    {
        read(n);
        for (int i = 1; i <= n; ++i) read(L[i]),read(R[i]),H[++cnt] = L[i],H[++cnt] = R[i];
        sort(H + 1,H + 1 + cnt),cnt = unique(H + 1,H + 1 + cnt) - H - 1;
        for(int i = 1;i<=cnt;++i) V[i].clear();
        for (int i = 1; i <= cnt; ++i) for(int j = 1;j<=cnt;++j) f[i][j] = -1;
        for (int i = 1; i <= n; ++i) 
        {
            L[i] = std::lower_bound(H + 1,H + 1 + cnt,L[i]) - H;
            R[i] = std::lower_bound(H + 1,H + 1 + cnt,R[i]) - H;
            V[R[i]].push_back(L[i]);
        }
        dfs(1,cnt);
        printf("%d\n",f[1][cnt]);
    }
    return 0;
}