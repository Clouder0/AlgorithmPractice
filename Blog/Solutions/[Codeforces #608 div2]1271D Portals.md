# Description
You play a strategic video game (yeah, we ran out of good problem legends). In this game you control a large army, and your goal is to conquer $n$ castles of your opponent.

Let's describe the game process in detail. Initially you control an army of $k$ warriors. Your enemy controls n castles; to conquer the $i$-th castle, you need at least ai warriors (you are so good at this game that you don't lose any warriors while taking over a castle, so your army stays the same after the fight). After you take control over a castle, you recruit new warriors into your army — formally, after you capture the $i$-th castle, $b_i$ warriors join your army. Furthermore, after capturing a castle (or later) you can defend it: if you leave at least one warrior in a castle, this castle is considered defended. Each castle has an importance parameter $c_i$, and your total score is the sum of importance values over all defended castles. There are two ways to defend a castle:
if you are currently in the castle $i$, you may leave one warrior to defend castle $i$;
there are $m$ one-way portals connecting the castles. Each portal is characterised by two numbers of castles $u$ and $v$ (for each portal holds $u>v$). A portal can be used as follows: if you are currently in the castle u, you may send one warrior to defend castle $v$. 
Obviously, when you order your warrior to defend some castle, he leaves your army.

You capture the castles in fixed order: you have to capture the first one, then the second one, and so on. After you capture the castle $i$
(but only before capturing castle i+1) you may recruit new warriors from castle $i$, leave a warrior to defend castle $i$, and use any number of portals leading from castle $i$ to other castles having smaller numbers. As soon as you capture the next castle, these actions for castle $i$ won't be available to you.

If, during some moment in the game, you don't have enough warriors to capture the next castle, you lose. Your goal is to maximize the sum of importance values over all defended castles (note that you may hire new warriors in the last castle, defend it and use portals leading from it even after you capture it — your score will be calculated afterwards).
Can you determine an optimal strategy of capturing and defending the castles?
## Input
The first line contains three integers $n, m and k (1≤n≤5000, 0≤m≤min(\frac{n(n−1)}{2},3⋅10^5), 0≤k≤5000$) — the number of castles, the number of portals and initial size of your army, respectively.

Then $n$ lines follow. The $i$-th line describes the $i$-th castle with three integers $a_i$, $b_i$ and $c_i (0≤a_i,b_i,c_i≤5000)$ — the number of warriors required to capture the $i$ -th castle, the number of warriors available for hire in this castle and its importance value.

Then $m$ lines follow. The $i$-th line describes the $i$-th portal with two integers $u_i$ and $v_i (1≤v_i<u_i≤n)$, meaning that the portal leads from the castle $u_i$ to the castle $v_i$. There are no two same portals listed.

It is guaranteed that the size of your army won't exceed 5000 under any circumstances (i. e. $k+∑_{i=1}^{n}b_i≤5000$).
## Output
If it's impossible to capture all the castles, print one integer $−1$.
Otherwise, print one integer equal to the maximum sum of importance values of defended castles.
# 题意
按顺序占领$1-n$所有城堡，可以选择在该城堡刚被占领时留下一个士兵获得权值，也可以通过$u,v$单向边来在后面占领该城堡获得权值。
# 思路
---
### update at 19/12/19  
之前的做法过于混乱（甚至我自己都觉得像是瞎蒙的），因此~~借鉴了其他神犇的题解~~仔细思考后发现可以使用反悔型贪心来做这道题。  
思路为：  
一路扫过去，每次都假定留守所有可留守的点，发现当前的士兵不够则从已留守的点中选取权值最小的放弃留守。  
依然是基于 靠后留守更优 策略，预处理出每个点可留守的集合，遍历到该点直接将可留守的全部push到已留守集合中，再遍历下一个点。  在遍历点过程中发现士兵不够，pop已留守集合，如果pop空了还不够，说明游戏失败。
代码一起放到后面了。自我感觉注释够详细了。

---
能不能占领完城堡很好判断，只需要每次都取光士兵而不留守扫一遍，如果这种情况下都有无法占领的城堡，那一定没法占领完。
如果要留守城堡$i$，那么一定是在最后留守最好。
因此可以开一个$last$数组，$last[i]$标记要留守$i$的最晚位置是哪里。
现在开始思考留守的实质：如果在位置$i$留守，就是使区间$[last[i]+1,n]$的可用士兵数量减少$1$。
我们要保证这段位置的可用士兵数量减少$1$之后还能占领所有的城堡。
于是有：
~~~cpp
inline bool check(const int &p)
{
    for(int i = p;i<=n;++i)
        if(a[i] + 1 > d[i])//d[i]代表占领i前的可用士兵数量
            return false;
    return true;
}
~~~
随后思考要怎么选择留守哪些城堡。可以发现，贪心地留守权值大的城堡一定是最优的。
因为留守一个城堡影响的是$[last[i]+1,n]$整个区间，我们可以讨论：
如果$c[i1] > c[i2]$，且$last[i1] < last[i2]$，即$i1$的权值比$i2$大，有3种情况：
1.[last[i1]+1,n]的区间全部减去2个士兵后依然能占领所有城堡。那么就是$i1$和$i2$都留守的情况，此时操作顺序不会影响结果。
2.[last[i1]+1,last[i2]]的区间减去1个士兵能满足，[last[i2]+1,n]减去2个士兵能满足，由于我们先处理权值大的，处理完$i1$后还能处理$i2$，也可以得到正确答案。
3.[last[i1]+1,n]的区间减去1个士兵能满足，此时$i1$与$i2$只能选择一个，那么肯定是选取$i1$好。
选取$i1$和$i2$的区别就在于$[last[i1]+1,last[i2]]$这段区间，是否会对结果造成影响呢？
我们将选择$i1$看做消耗$[last[i1]+1,last[i2]]$和$[last[i2]+1,n]$内的士兵数量。
假定有一个$i3$的选择，，且$c[i3] < c[i1]$，如果$last[i3] > last[i2]$，很显然选择$i1$和$i2$是等效的。
如果$last[i3] < last[i1]$，那么选取$i3$的代价比选取$i1$更大且得利更少，因此此时先选择$i1$可以保证整体更优。
如果$last[i3]在[last[i1+1],last[i2]]$之间，若选$i1$后还能选$i3$则肯定选$i1$，若选$i1$后不能选$i3$，那么选$i3$后肯定也不能选$i1$，但$c[i3] < c[i1]$，因此可能情况下还是选$i1$更好。
另外，若$c[i1] > c[i2]$且$last[i1] > last[i2]$，很显然此时选择i1比选择i2好。
可能写的有点乱……
# Code
~~~cpp
#include <cstdio>
#include <algorithm>
template <typename T> inline T max(const T &a,const T &b){return a>b?a:b;}
inline char nc()
{
    static char buf[1000000],*p1 = buf,*p2 = buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;
}
void read(int &r)
{
    static char c;r=0;
    for(c=nc();c>'9'||c<'0';c=nc());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=nc());
}
int n,m,k;
int last[5001];//last[i]保存i点最晚能在哪里被派兵守卫
int a[5001],b[5001],c[5001],d[5001];//d[i]代表占领i前到达i这里的兵力
int q[5001];
bool cmp(const int &a,const int &b)
{
    return c[a] > c[b];
}
inline bool check(const int &p)
{
    for(int i = p;i<=n;++i)
        if(a[i] + 1 > d[i])
            return false;
    return true;
}
int main()
{
    read(n);
    read(m);
    read(k);
    int now = k;//现在兵力
    for(int i = 1;i<=n;++i)
    {
        read(a[i]);
        read(b[i]);
        read(c[i]);
        d[i] = now;
        if(now < a[i])
        {
            printf("-1");
            return 0;
        }
        now += b[i];//顺便判断是否能占领所有城堡，也就是判断每次取完兵能否一路全部占领
        q[i] = last[i] = i;
    }
    int u,v;
    for(;m;--m)
    {
        read(u);
        read(v);
        last[v] = max(last[v],u);
    }
    std::sort(q+1,q+1+n,cmp);//按照贡献值排序
    int ans = 0;
    for(int i = 1;i<=n;++i)
    {
        if(check(last[q[i]] + 1))
        {
            for(int j = last[q[i]] + 1;j<=n;++j)
                --d[j];
            ans += c[q[i]];
        }
    }
    printf("%d",ans);
    return 0;
}
~~~
这里是反悔贪心的代码：
~~~cpp
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
~~~