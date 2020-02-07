#include <cstdio>
#include <queue>
#include <vector>
using namespace std;
//读入优化
inline char nc()
{
    static char buf[100000], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
}
template <typename T>
inline void read(T &r)
{
    static char c;r = 0;
    for (c = nc(); c > '9' || c < '0'; c = nc());
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = nc());
}
const int maxn = 5e3 + 10;
int n, m, k, ans;
int a[maxn], b[maxn], c[maxn];
int last[maxn]; //last[i]记录i最后能在哪里被留守
priority_queue<int, vector<int>, greater<int>> q;
vector<int> defback[maxn]; //存储该点可以向前留守什么点
int main()
{
    read(n);
    read(m);
    read(k);
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        read(b[i]);
        read(c[i]);
        last[i] = i; //初始化
    }
    int u, v;
    for (; m; --m)
    {
        read(u);
        read(v);
        last[v] = last[v] > u ? last[v] : u; //取更大者，因为越后留守一定越好
    }
    for (int i = 1; i <= n; ++i)
        defback[last[i]].push_back(i);
    for (int i = 1; i <= n; ++i)
    {
        while (k < a[i] && !q.empty()) //不够的话，从已留守的城堡中取出权值最小的放弃，即反悔
            ++k, q.pop();
        //defended[q.top()] = false; 事实上并不需要对是否已经留守做标记，因为所有点最多会被判断留守一次，也就是最多被标true false一次

        if (k < a[i]) //如果取完还是不够，那没办法了，输出-1
            goto fail;

        //占领当前点
        k += b[i];
        //往前留守，这里不用考虑当前点，因为当前点要么也在vector中，要么在后面可以被留守
        for (vector<int>::iterator it = defback[i].begin(); it != defback[i].end(); ++it)
            --k, q.push(c[*it]); //可以直接全部push到留守集合中，等后面再反悔，不用考虑会不会让k<0
    }
    //最后一步后还要判断k是否大于0进行一次反悔
    while (k < 0 && !q.empty())
        ++k, q.pop();
    if (k < 0)
        goto fail;
    while (!q.empty())//统计已留守点的权值和
        ans += q.top(), q.pop();
    printf("%d", ans);
    return 0;
fail:
    puts("-1");
    return 0;
}