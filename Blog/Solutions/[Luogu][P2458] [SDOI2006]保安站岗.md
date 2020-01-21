[题目链接](https://www.luogu.com.cn/problem/P2458)
看起来似乎跟最小点覆盖有点像。但区别在于：  
最小点覆盖要求所有边在其中，而本题要求所有点在其中。  

即：一个点不选时，它的儿子不一定需要全选。
画图理解：

![Example](https://img-blog.csdnimg.cn/20191213134746401.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L01pc3NpbmdfQ2xvdWQ=,size_16,color_FFFFFF,t_70)

对于这样一幅图，本题中可以这样选择：$3,5$：
$3$将相邻的点$2,4$覆盖，而$5$将相邻的点$1,6$覆盖，因此所有点都被覆盖了。
那么就必须修改状态了。

# Dynamic Programing
考虑对于一个点，如果它被覆盖了，只有三种可能：
1. 自己被标记
2. 父亲被标记
3. 儿子被标记

因此我们设计状态：  
1. $dp[now][0]$为自己被标记
2. $dp[now][1]$为父亲被标记
3. $dp[now][2]$为儿子被标记  

那么如何转移呢？  

自己被标记时，儿子的3种状态都是合法的，因此有：
$$dp[now][0] = \sum \min(dp[son][0],dp[son][1],dp[son][2])$$

而父亲被标记时，儿子不能被父亲标记了，只能自己标记或者被儿子的儿子标记。
$$dp[now][1] = \sum \min(dp[son][0],dp[son][2])$$

被儿子标记的情况就复杂一些。首先，被儿子标记时，所有儿子肯定无法被父亲标记，因此首先有：
$$dp[now][2] = \sum \min(dp[son][0],dp[son][2])$$

但是至少需要有一个儿子标记自己，才能让当前节点被儿子控制。如果一遍下来都没有选取$dp[son][0]$的情况怎么办呢？

我们考虑一个儿子，如果它被儿子标记更优，我们却强制它标记自己，那么代价就是$dp[son][0] - dp[son][2]$。

那么我们在遍历儿子时记录，看是否有儿子选取了控制自己，如果没有的话，就选择代价最小的那个儿子强制标记它即可。
# Code
实现似乎没有太多坑点。  
但要注意：当一个点是叶子结点时，$dp[now][2]$即被儿子标记的代价一定是$+\infty$，在代码中我直接并在了最后的处理中。可以感受一下。

另外就是这题的数据问题，虽然说题面是严格父亲对应儿子，但我建单向边死活过不了第三个点，改成双向边后AC。

最后答案，根节点不能被父亲控制。
```cpp
#include <cstdio>
#include <cstring>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c; r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
struct node
{
    int to, next;
    node() {}
    node(const int &_to, const int &_next) : to(_to), next(_next) {}
} lines[3002];
int head[1501];
void add(const int &x, const int &y)
{
    static int tot = 0;
    lines[++tot] = node(y, head[x]), head[x] = tot;
}
template<typename T> inline T min(const T &a,const T &b){return a<b?a:b;}
template<typename T> inline T min(const T &a,const T &b,const T &c){return min(min(a,b),c);}
template<typename T> inline T max(const T &a,const T &b){return a>b?a:b;}
int n;
int w[1501];
int dp[1501][3];
//dp[i][0] 自己控制
//dp[i][1] 父亲控制
//dp[i][2] 儿子控制
void dfs(int now,int fa)
{
    int v,minp = 999999999;
    bool flag = true;//标记是否强制有一个儿子控制自己
    dp[now][0] = w[now];
    for(int p = head[now];p;p=lines[p].next)
    {
        v = lines[p].to;
        if(v == fa)
            continue;
        dfs(v,now);
        dp[now][0] += min(dp[v][2],dp[v][1],dp[v][0]);
        dp[now][1] += min(dp[v][0],dp[v][2]);
        if(dp[v][0] <= dp[v][2])
        {
            //此时可以直接选择这个儿子控制自己了
            flag = false;
            dp[now][2] += dp[v][0];
        }
        else
        {
            dp[now][2] += dp[v][2];
            minp = min(minp,dp[v][0] - dp[v][2]);
        }
    }
    if(flag)
        dp[now][2] += minp;
}
int main()
{
    read(n);
    int m,u,x;
    for(int i = 1;i<=n;++i)
    {
        read(u);
        read(w[u]);
        read(m);
        while(m--)
        {
            read(x);
            add(u,x);
            add(x,u);//居然要双向边?!
        }
    }
    dfs(1,0);
    printf("%d",min(dp[1][0],dp[1][2]));
    return 0;
}
```

