# 题目
On the well-known testing system MathForces, a draw of $n$ rating units is arranged. The rating will be distributed according to the following algorithm: if $k$ participants take part in this event, then the $n$ rating is evenly distributed between them and rounded to the nearest lower integer, At the end of the drawing, an unused rating may remain — it is not given to any of the participants.

For example, if $n=5$ and $k=3$, then each participant will recieve an $1$ rating unit, and also $2$ rating units will remain unused. If $n=5$, and $k=6$, then none of the participants will increase their rating.

Vasya participates in this rating draw but does not have information on the total number of participants in this event. Therefore, he wants to know what different values of the rating increment are possible to get as a result of this draw and asks you for help.

For example, if $n=5$, then the answer is equal to the sequence $0,1,2,5$. Each of the sequence values (and only them) can be obtained as ⌊n/k⌋ for some positive integer $k$ (where $⌊x⌋$ is the value of $x$ rounded down): $0=⌊5/7⌋, 1=⌊5/5⌋, 2=⌊5/2⌋, 5=⌊5/1⌋$.

Write a program that, for a given $n$, finds a sequence of all possible rating increments.

# 输入
The first line contains integer number $t (1≤t≤10)$ — the number of test cases in the input. Then $t$ test cases follow.

Each line contains an integer $n(1≤n≤10^9)$ — the total number of the rating units being drawn.
# 输出
Output the answers for each of $t$ test cases. Each answer should be contained in two lines.

In the first line print a single integer $m$ — the number of different rating increment values that Vasya can get.

In the following line print $m$ integers in **ascending order** — the values of possible rating increments.
# 题目大意
给定$t$组数据，每组包含一个整数$n(1≤n≤10^9)$，求出所有n被整除能得出的商。
# 想法
朴素想法：枚举$1-n$，每个除一遍，加到$set$中去重，然后直接遍历输出即可。
复杂度$O(tn\log n)$，死路一条。

考虑到$x\times x=n$，我们可以最多枚举到$\sqrt n$，在枚举时同时加入$x$和$n/x$，那么式子看起来是这样：
$$n \div (n \div x) = x$$

$$n \div x = n \div x$$

即可保证所有整除商都被加入$set$中。
此时复杂度$O(t\sqrt n\log n)$，能过。
代码如下：

```cpp
#include <cstdio>
#include <set>
#include <cmath>
using namespace std;
int t, n;
set<int> out;
int main()
{
    scanf("%d", &t);
    while (t--)
    {
        out.clear();
        scanf("%d", &n);
        out.insert(0);
        int lim = sqrt(n);
        for (int i = 1; i <= lim; ++i)
        {
            out.insert(i);
            out.insert(n / i);
        }
        printf("%d\n",out.size());
        for (set<int>::iterator it = out.begin(); it != out.end(); ++it)
            printf("%d ", *it);
        printf("\n");
    }
    return 0;
}
```
但事实上，还有更简单的方法：我们可以去掉这个$set$！
在枚举$x = [1,\sqrt n]$时，我们会发现，每个$x$都是可以取到且不重复的，而$n \div x$实际上也是不重复的。证明如下：
$设n \div x_1 = k_1,n \div x_2 = k_2，其中x_1 > x_2$
则有：
$k_1 \times x_1 + t_1 = n,t1 \in [0,x_1)$
$k_2 \times x_2 + t_2 = n,t2 \in [0,x_2)$
假如$k_1 = k_2 = k$，那么：
$k \times x_1 + t_1 = k \times x_2 + t_2$
$k \times (x_1 - x_2) = t_2 - t_1$
$k = \frac{(t_2 - t_1)}{(x_1 - x_2)}$
然而：
$t_2 - t_1 \in (-x_1,x_2-x_1)$
那么$k \in (\frac{-x_1}{x_1 - x_2},\frac{x_2-x_1}{x_1-x_2})$
显然此时$k<0$，产生了矛盾。

因此，对于$x \in [1,\sqrt n]$，我们得到的所有的$x$和$n \div x$即为答案。
顺序枚举$x$，将$n \div x$存入另一个数组中，显然该数组中的数单调递减。
还需要特判最后$x = \sqrt n$时，$x = n \div x$的情况。
输出答案直接输出$[0,\sqrt n]$，再逆序输出保存数组中的结果即可。

复杂度$O(t\sqrt n)$，已经相当优秀了。
还有一种整除分块的方法，本蒟蒻还不会……
# Code

```cpp
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
int t, n, lim, cnt;
int save[50000];
int main()
{
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d", &n);
        lim = sqrt(n);
        cnt = 0;
        for (register int i = 1; i <= lim; ++i)
            save[++cnt] = n / i;
        if (cnt && lim == save[cnt]) //特判，注意有可能输入为0，这样cnt会被减为负数……
            --cnt;
        printf("%d\n", cnt + lim + 1);
        for (int i = 0; i <= lim; ++i)
            printf("%d ", i);
        for (int i = cnt; i; --i)
            printf("%d ", save[i]);
        putchar('\n');
    }
    return 0;
}
```

