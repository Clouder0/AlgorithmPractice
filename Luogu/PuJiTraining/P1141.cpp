#include <cstdio>
using namespace std;
#define getId(x, y) (((x - 1) * n) + y)
int fa[1001000];
int h[1001000];
char all[2][1010];
int n, m, i, j;
inline char nc()
{
    static char buf[400000], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 400000, stdin), p1 == p2) ? EOF : *p1++;
}
//读入优化
void read(char *s)
{
    static char c;
    for (c = nc(); c != '1' && c != '0'; c = nc());
    for (; c == '0' || c == '1'; *++s = c, c = nc());
}
void read(int &r)
{
    static char c;  r = 0;
    for (c = nc(); c > '9' || c < '0'; c = nc());
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = nc());
}
//并查集
inline int find(const int &x)
{
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}
inline void unite(const int &a, const int &b)
{
    int t1 = find(a), t2 = find(b);
    if (t1 == t2)
        return;
    h[t1] > h[t2] ? fa[t2] = t1, h[t1] += h[t2] : fa[t1] = t2, h[t2] += h[t1]; //类似按秩合并的做法，合并同时将儿子的大小加入父亲的大小中
}
//
int main()
{
    read(n);
    read(m);
    int n2 = n * n;
    for (int i = 1; i <= n2; ++i)
        fa[i] = i, h[i] = 1; //初始化每个点都是单独的联通块，大小为1
    
    int now = 0, pre = 1;
    //第一行特判，不需要与上一行作比较
    i = 1;
    read(all[now]);
    for (j = 2; j <= n; ++j)//j从2开始，可以略过第一个格子，最左上角的格子无需判断
        if (all[now][j] != all[now][j - 1])
            unite(getId(i, j), getId(i, j - 1));

    for (i = 2; i <= n; ++i)
    {
        now ^= 1;//使用滚动数组
        pre ^= 1;
        read(all[now]);
        if (all[now][1] != all[pre][1])
            unite(getId(i, 1), getId(i - 1, 1));//第一个格子无需与左边判断
        for (j = 2; j <= n; ++j)
        {
            if (all[now][j] != all[now][j - 1]) //因为是按行按列遍历，实际上只需要处理每个点的上方点和左边点的合并
                unite(getId(i, j), getId(i, j - 1));
            if (all[now][j] != all[pre][j])
                unite(getId(i, j), getId(i - 1, j));
        }
    }
    int x, y;
    for (i = 1; i <= m; ++i)
    {
        read(x);
        read(y);
        printf("%d\n", h[find(getId(x,y))]);
    }
    return 0;
}