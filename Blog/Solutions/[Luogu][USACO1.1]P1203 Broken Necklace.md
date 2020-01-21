# Solution
这道题数据规模奇小，因此大部分人都使用了暴力搜索的方法，这也是我一开始的想法。  
>对于 $100%$ 的数据，$3≤n≤350$  

的确可以如此，但暴力搜索的方法也需要进行一些奇怪的判断，因此我又决定直接打dp的解法，其实dp也是很自然的一种想法……
# Dynamic Programming
我们可以发现，每个点向左向右，取蓝色取红色能连续取的个数一定是确定的。  
于是我们定义dp数组：

~~~cpp
int lr[maxn];
//lr[i]代表从i点向左不取i点
//即在 [1,i-1] 范围内从i-1开始能连续取多少个红色珠子
int lb[maxn];
//lb[i]代表从i点向左不取i点
//即在 [1,i-1] 范围内从i-1开始能连续取多少个蓝色珠子
int rr[maxn];
//rr[i]代表从i点向右取i点
//即在[i,n] 范围内从i开始能连续取多少个红色珠子
int rb[maxn];
//rb[i]代表从i点向右取i点
//即在[i,n] 范围内从i开始能连续取多少个蓝色珠子
~~~
那么在一个点断开，能取得的珠子个数就是：
$$ans[i] = max(lr[i],lb[i]) + max(rr[i],rb[i])$$

相信转移方程非常自然吧，我们先考虑向左取的情况：

1. 前一个点为白色，那么有：
$$lr[i] = lr[i-1] + 1$$
$$lb[i] = lb[i-1] + 1$$
2. 前一个点为红色，那么有：
$$lr[i] = lr[i-1] + 1$$
$$lb[i] = 0$$
3. 前一个点为蓝色，那么有：
$$lr[i] = 0$$
$$lb[i] = lb[i-1] + 1$$

为什么考虑前一个点呢？  
因为$lr[i]$和$lb[i]$代表的是区间$[1,i-1]$内从点$i-1$开始取能连续取多少，因此实际考虑的是点$i-1$的颜色。  
向右的情况也是同理，有：

1. 当前点为白色，那么有：
$$rr[i] = rr[i+1] + 1$$
$$rb[i] = rb[i+1] + 1$$
2. 当前点为红色，那么有：
$$rr[i] = rr[i+1] + 1$$
$$rb[i] = 0$$
3. 当前点为蓝色，那么有：
$$rr[i] = 0$$
$$rb[i] = rb[i+1] + 1$$

实现也很简单：
~~~cpp
for (int i = 2; i <= n; ++i)
{
   if (s[i - 1] == 'w')
        lb[i] = lb[i - 1] + 1, lr[i] = lr[i - 1] + 1;
    else if (s[i - 1] == 'b')
        lb[i] = lb[i - 1] + 1, lr[i] = 0;
    else
        lb[i] = 0, lr[i] = lr[i - 1] + 1;
}
for (int i = n - 1; i; --i)
{
    if (s[i] == 'w')
        rb[i] = rb[i + 1] + 1, rr[i] = rr[i + 1] + 1;
    else if (s[i] == 'b')
        rb[i] = rb[i + 1] + 1, rr[i] = 0;
    else
        rb[i] = 0, rr[i] = rr[i + 1] + 1;
}
~~~
# Finally
于是我们处理出了每个点向左向右取红取蓝最多能连续取多少个珠子。  
那么从$i-1$点，向左最多能取多少呢？  
$$left[i-1] = max(lr[i],lb[i])$$
从$i$点，向右最多能取
$$right[i] = max(rr[i],rb[i])$$
假定我们断开$i-1$和$i$，那么答案就是：
$$ans = left[i-1] + right[i]$$
即
$$ans = max(lr[i],lb[i]) + max(rr[i],rb[i])$$
最后扫一遍统计答案即可。
~~~cpp
int ans = 0;
for (int i = 1; i <= n; ++i)
    ans = max(ans, max(lb[i], lr[i]) + max(rb[i], rr[i]));
~~~
当然，还要注意答案不能超过原始的长度。
# Code
拆环为链等细节就不赘述了。
~~~cpp
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 710;
char s[maxn];
int n,lb[maxn], lr[maxn], rb[maxn], rr[maxn];
inline int max(const int &a, const int &b) { return a > b ? a : b; }
int main()
{
    scanf("%d%s", &n, s + 1);
    memcpy(s + n + 1, s + 1, n);
    n <<= 1;
    for (int i = 2; i <= n; ++i)
    {
        if (s[i - 1] == 'w')
            lb[i] = lb[i - 1] + 1, lr[i] = lr[i - 1] + 1;
        else if (s[i - 1] == 'b')
            lb[i] = lb[i - 1] + 1, lr[i] = 0;
        else
            lb[i] = 0, lr[i] = lr[i - 1] + 1;
    }
    for (int i = n - 1; i; --i)
    {
        if (s[i] == 'w')
            rb[i] = rb[i + 1] + 1, rr[i] = rr[i + 1] + 1;
        else if (s[i] == 'b')
            rb[i] = rb[i + 1] + 1, rr[i] = 0;
        else
            rb[i] = 0, rr[i] = rr[i + 1] + 1;
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i)
        ans = max(ans, max(lb[i], lr[i]) + max(rb[i], rr[i]));
    if (ans > n >> 1)
        ans = n >> 1;
    printf("%d\n", ans);
    return 0;
}
~~~