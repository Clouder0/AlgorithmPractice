#include <cstdio>
#include <cstring>
const int maxn = 2e6 + 100;
int n;
char T[maxn];
namespace Inf
{
struct Information
{
    int next, id;
} I[maxn];
int head[maxn], tot;
inline void add(int x, int id) { I[++tot].next = head[x], head[x] = tot, I[tot].id = id; }
}
int to[maxn][26], fail[maxn], num[maxn], mark[maxn], cnt = 1;
void ins(char* s, int id)
{
    int p = 1;
    for (; *s != '\0'; ++s)
    {
        int c = *s - 'a';
        if(!to[p][c]) to[p][c] = ++cnt;
        p = to[p][c];
    }
    Inf::add(p, id);
}
void build()
{
    static int q[maxn * 26], qh = 1, qt = 0;
    for (int i = 0; i < 26; ++i) to[0][i] = 1;
    q[++qt] = 1;
    while(qt >= qh)
    {
        int u = q[qh++];
        for (int i = 0; i < 26; ++i)
        {
            if (to[u][i]) fail[to[u][i]] = to[fail[u]][i], q[++qt] = to[u][i];
            else to[u][i] = to[fail[u]][i];
        }
    }
}
namespace Tree
{
struct node
{
    int to, next;
} E[maxn];
int head[maxn];
inline void add(const int& x, const int& y)
{
    static int tot = 0;
    E[++tot].next = head[x],E[tot].to = y,head[x] = tot;
}
void buildtree() { for (int i = 2; i <= cnt; ++i) add(fail[i], i); }
}
void check(char *s)
{
    int p = 1;
    for (; *s != '\0'; ++s)
    {
        int c = *s - 'a';
        p = to[p][c], ++mark[p];
    }
}
void dfs(int u)
{
    for (int p = Tree::head[u]; p; p = Tree::E[p].next)
    {
        int v = Tree::E[p].to;
        dfs(v), mark[u] += mark[v];
    }
    for (int p = Inf::head[u]; p; p = Inf::I[p].next) num[Inf::I[p].id] = mark[u];
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%s", T + 1), ins(T + 1, i);
    build(), Tree::buildtree();
    scanf("%s", T + 1);
    check(T + 1);
    dfs(1);
    for (int i = 1; i <= n; ++i) printf("%d\n", num[i]);
    return 0;
}