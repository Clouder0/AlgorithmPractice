#include <algorithm>
#include <cstdio>
#include <ctype.h>
#include <vector>
using namespace std;
const int bufSize = 1e6;
inline char nc()
{
#ifdef DEBUG
    return getchar();
#endif
    static char buf[bufSize], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
}
inline void read(char* s)
{
    static char c;
    for (; !isalpha(c); c = nc())
        ;
    for (; isalpha(c); c = nc()) *s++ = c;
    *s = '\0';
}
template <typename T>
inline T read(T& r)
{
    static char c;
    static int flag;
    flag = 1, r = 0;
    for (c = nc(); !isdigit(c); c = nc())
        if (c == '-') flag = -1;
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r *= flag;
}
const int maxn = 5e5 + 100;
int n, m, in[maxn], out[maxn], start[maxn], s[maxn], top;
vector<int> V[maxn];
void dfs(int u)
{
    for (int& p = start[u]; p < V[u].size();)
    {
        int v = V[u][p++];
        dfs(v);
    }
    s[++top] = u;
}
int main()
{
    scanf("%d%d",&n,&m);
    for (int i = 1, a, b; i <= m; ++i) scanf("%d%d", &a, &b), V[a].push_back(b), out[a]++, in[b]++;
    for (int i = 1; i <= n; ++i) sort(V[i].begin(), V[i].end());
    int x = 1, y = 0, num1 = 0, num2 = 0, num3 = 0;
    for (int i = 1; i <= n; ++i)
        if (out[i] == in[i] + 1)
            x = i, ++num1;
        else if (out[i] + 1 == in[i])
            y = i, ++num2;
        else if(in[i] != out[i]) ++num3;
    if(num1 == 1 && num2 == 1 && num3 == 2) dfs(x);
    else if(num3 == 0) dfs(x);
    else goto no;
    while(top) printf("%d ",s[top--]);
    return 0;
no:
    puts("No");
    return 0;
}