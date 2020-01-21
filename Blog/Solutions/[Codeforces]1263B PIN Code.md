# 题目
A PIN code is a string that consists of exactly $4$ digits. Examples of possible PIN codes: $7013$, $0000$ and $0990$. Please note that the PIN code can begin with any digit, even with $0$.

Polycarp has $n(2≤n≤10)$ bank cards, the PIN code of the $i$-th card is $p_i$.

Polycarp has recently read a recommendation that it is better to set different PIN codes on different cards. Thus he wants to change the minimal number of digits in the PIN codes of his cards so that all $n$ codes would become different.

Formally, in one step, Polycarp picks $i$-th card $(1≤i≤n)$, then in its PIN code $p_i$ selects one position (from $1$ to $4$), and changes the digit in this position to any other. He needs to change the minimum number of digits so that all PIN codes become different.

Polycarp quickly solved this problem. Can you solve it?
# 输入
The first line contains integer $t (1≤t≤100)$ — the number of test cases in the input. Then test cases follow.

The first line of each of $t$test sets contains a single integer $n (2≤n≤10)$ — the number of Polycarp's bank cards. The next $n$ lines contain the PIN codes $p_1,p_2,…,p_n$ — one per line. The length of each of them is $4$. All PIN codes consist of digits only.
# 输出
Print the answers to t test sets. The answer to each set should consist of a $n+1$ lines.

In the first line print $k$ — the least number of changes to make all PIN codes different. In the next $n$ lines output the changed PIN codes in the order corresponding to their appearance in the input. If there are several optimal answers, print any of them.
# 题目大意
$t$组数据，每组给定$n$个可能有重复的四位数，每次变换可以改变一个数字的任意一位，求最少多少次变换后没有相同的数字。
# 思路
一开始是想记录前三位相同的数字可用（没有已有数字填充）的个数，然后再贪心，然后换前2位……
后来发现$n<=10$的致命条件。
于是难度跳崖下降。我们每个数字肯定最多只需要变换一次就能保证不重复（0-9有10个位置）。
开一个map记录当前位置有多少个数，然后找到当前位置数个数$>1$就使$ans += mp[now] - 1$即可统计出变换次数。
那么求变换后序列呢？因为每个数肯定都可以通过改变其中一位来保证不重复，因此直接枚举改变一位，如果改变后的位置无数则变过去就可以了。
复杂度$O(nt)$

# 代码

```cpp
#include <cstdio>
#include <iostream>
#include <string>
#include <map>
using namespace std;
int t, n, ans;
map<string, int> ht;
string all[11];
int main()
{
    cin.tie(0);
    ios::sync_with_stdio(false);
    cin >> t;
    while (t--)
    {
        ans = 0;
        ht.clear();
        cin >> n;
        for (int i = 1; i <= n; ++i)
            cin >> all[i], ++ht[all[i]];
        for (map<string, int>::iterator it = ht.begin(); it != ht.end(); ++it)
            ans += it->second - 1;
        cout << ans << endl;//直接先统计出答案，每组都要且只要进行n-1次变换
        for (int i = 1; i <= n; ++i)
        {
            map<string, int>::iterator it = ht.find(all[i]);
            if (it == ht.end())
                continue;
            if (it->second > 1)
            {
                string s = all[i];
                for (int j = 0; j <= 9; ++j)
                {
                    s[3] = j + '0';
                    if (ht.find(s) == ht.end())
                    {
                        ht[s] = 1;
                        cout << s << endl;
                        --it->second;//这里只进行1次变换，因为每个输入的数据都会遍历到，所以最后一定会减到1
                        break;
                    }
                }
            }
            else
                cout << all[i] << endl;
        }
    }
    return 0;
}
```

