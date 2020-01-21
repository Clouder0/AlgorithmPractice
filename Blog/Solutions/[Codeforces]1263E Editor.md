The development of a text editor is a hard problem. You need to implement an extra module for brackets coloring in text.

Your editor consists of a line with infinite length and cursor, which points to the current character. Please note that it points to only one of the characters (and not between a pair of characters). Thus, it points to an index character. The user can move the cursor left or right one position. If the cursor is already at the first (leftmost) position, then it does not move left.

Initially, the cursor is in the first (leftmost) character.

Also, the user can write a letter or brackets (either (, or )) to the position that the cursor is currently pointing at. A new character always overwrites the old value at that position.

Your editor must check, whether the current line is the correct text. Text is correct if the brackets in them form the correct bracket sequence.

Formally, correct text (CT) must satisfy the following rules:

 - any line without brackets is CT (the line can contain whitespaces);
 - If the first character of the string — is (, the last — is ), and all
   the rest form a CT, then the whole line is a CT;
 - two consecutively written CT is also CT.

Examples of correct texts: *hello(codeforces), round, ((i)(write))edi(tor)s, ( me)*. Examples of incorrect texts: *hello)oops(, round), ((me)*.

The user uses special commands to work with your editor. Each command has its symbol, which must be written to execute this command.

The correspondence of commands and characters is as follows:

 - L — move the cursor one character to the left (remains in place if it
   already points to the first character);
 - R — move the cursor one character to the right;
 - any lowercase Latin letter or bracket (( or )) — write the entered
   character to the position where the cursor is now.

For a complete understanding, take a look at the first example and its illustrations in the note below.

You are given a string containing the characters that the user entered. For the brackets coloring module's work, after each command you need to:

 - check if the current text in the editor is a correct text;
 - if it is, print the least number of colors that required, to color
   all brackets.

If two pairs of brackets are nested (the first in the second or vice versa), then these pairs of brackets should be painted in different colors. If two pairs of brackets are not nested, then they can be painted in different or the same colors. For example, for the bracket sequence ()(())()() the least number of colors is $2$, and for the bracket sequence (()(()())())(()) — is $3$.

Write a program that prints the minimal number of colors after processing each command.
# 输入
The first line contains an integer $n (1≤n≤10^6)$ — the number of commands.
The second line contains $s$— a sequence of commands. The string s consists of n characters. It is guaranteed that all characters in a string are valid commands.
# 输出
In a single line print $n$ integers, where the $i$-th number is:

 - $−1$ if the line received after processing the first $i$ commands is
   not valid text,
 - the minimal number of colors in the case of the correct text.
# 题目大意
给$3$种指令，左移光标，右移光标，将当前光标的位置的字符设置为$c$。
每次移动后对现在的文本进行检测，如果是合法的括号序列，则输出序列的最大层数，否则输出$-1$.
# 思路
关键在于如何快速地检验合法并且得到最大层数。
检验合法可以用栈，若栈非空或插右括号而无左括号则不合法。
但问题是有左移操作，因此我们可以开一个数组，令$($权值为$1$，$)$权值为$-1$，那么总权值和为0则保证了左右括号数量匹配。
但还要求每个位置的左括号数量都要大于等于右括号数量。那么再维护一个区间前缀和最小值，如果这个最小值小于0则肯定不合法。
而输出最大层数呢？其实就是区间前缀和最大值。
如果朴素维护，复杂度$O(n)$，那么总复杂度$O(n^2)$明显超时。考虑使用数据结构优化。
区间操作，上线段树！使用线段树维护区间前缀和最大最小值，维护区间和，即可解决问题。
复杂度$O(n\log n)$
其中维护区间前缀和最大最小值代码如下：

```cpp
smax[p] = max(smax[p << 1], sum[p << 1] + smax[p << 1 | 1]);
smin[p] = min(smin[p << 1], sum[p << 1] + smin[p << 1 | 1]);
```
一个区间前缀和最大最小值，要么取左半边区间的值，要么就取右半边的值再加上左半边整个区间权值和。
其他就是单点修改的板子了。
# 代码

```cpp
#include <cstdio>
using namespace std;
int n, pos = 1;
const int maxn = 1000010;
int sum[maxn << 2], smax[maxn << 2], smin[maxn << 2];
inline int max(const int &a, const int &b) { return a > b ? a : b; }
inline int min(const int &a, const int &b) { return a < b ? a : b; }
void push_up(const int &p)
{
    sum[p] = sum[p << 1] + sum[p << 1 | 1];
    smax[p] = max(smax[p << 1], sum[p << 1] + smax[p << 1 | 1]);
    smin[p] = min(smin[p << 1], sum[p << 1] + smin[p << 1 | 1]);
}
int k;
void update(const int &l, const int &r, const int &p)
{
    if (l == r)
    {
        //单点修改
        sum[p] = smax[p] = smin[p] = k;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid)
        update(l, mid, p << 1);
    else
        update(mid + 1, r, p << 1 | 1);
    push_up(p);
}
int main()
{
    scanf("%d", &n);
    getchar();
    char c;
    for (int i = 1; i <= n; ++i)
    {
        c = getchar();
        switch (c)
        {
        case 'L':
            pos = (pos == 1 ? pos : pos - 1);
            break;
        case 'R':
            ++pos;
            break;
        case '(':
            k = 1;
            update(1, n, 1);
            break;
        case ')':
            k = -1;
            update(1, n, 1);
            break;
        default:
            k = 0;
            update(1, n, 1); //修改成非括号字母也要修改权值
        }
        //当前序列合法条件： 权值和为0，最小权值和>=0
        if (sum[1] != 0 || smin[1] < 0)
        {
            printf("-1 ");
            continue;
        }
        printf("%d ", smax[1]);
    }
    return 0;
}
```