[题目链接](https://codeforces.com/contest/1263/problem/A)
# 题目描述
You have three piles of candies: red, green and blue candies:

the first pile contains only red candies and there are $r$ candies in it,
the second pile contains only green candies and there are $g$ candies in it,
the third pile contains only blue candies and there are $b$ candies in it. 

Each day Tanya eats exactly two candies of different colors. She is free to choose the colors of eaten candies: the only restriction that she can't eat two candies of the same color in a day.

Find the maximal number of days Tanya can eat candies? Each day she needs to eat exactly two candies.

# 输入
The first line contains integer $t (1≤t≤1000)$ — the number of test cases in the input. 
Then $t$ test cases follow.

Each test case is given as a separate line of the input. It contains three integers $r$, $g$ and $b(1≤r,g,b≤10^8)$ — the number of red, green and blue candies, respectively.
# 输出
Print $t$ integers: the $i$-th printed integer is the answer on the $i$-th test case in the input.

# 题目大意
给定$t$组测试数据。
每组数据包含$r,g,b$三个数，代表3种糖的数量。
每天只能吃不同的两种糖，两种各吃一颗。
求最多能吃多少天。
# 解法
容易发现哪种颜色都没有关系，因此直接假定：
$r>g>b$
那么怎么吃最优呢？最优吃法应当是固定的。我考虑计算$r与g$的差值。
设$delta = r - g$，

那么若$delta >= b$，即把b和r一起吃完b后，只剩下$r-b,g$，此时$r-b>=g$，那么再一起吃$g$天即可。
此时$ans = b + g$。

若$delta < b$，那么我们把$r$和$b$一起吃，吃$delta$天，使得$r$吃完后与$g$相等。
随后均分剩余的$b$给另外两堆，每堆吃$(b-delta)/2$天。这里向下取整，如果多了一颗糖不能凑成一对，对结果没有影响。
随后吃$g-(b-delta)/2$天即可把剩下两堆一起吃完。
若$(b-delta)/2$为奇数，那么最后会剩下一颗糖，否则全部吃完。
统计答案，$ans = delta + (b-delta) + g-(b-delta)/2$
即$ans = r - g + b - r + g + g - b/2 + r/2 - g/2$
整理得$ans = (r+g+b)/2$
除以二向下取整，那么奇偶的影响就被消除了。可以手推几组感受一下。
# Code

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
int all[4];
int ans, t;
int main()
{
    scanf("%d", &t);
    while (t--)
    {
        ans = 0;
        for (int i = 1; i <= 3; ++i)
            scanf("%d", all + i);
        sort(all + 1, all + 4);
        int delta = all[3] - all[2];
        if (delta >= all[1])
            printf("%d\n", all[1] + all[2]);
        else
            printf("%d\n",(all[1] + all[2] + all[3])>>1);
    }
    return 0;
}
```

