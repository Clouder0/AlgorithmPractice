# Description
A new delivery of clothing has arrived today to the clothing store. This delivery consists of $a$ ties,$b$ scarves,$c$ vests and $d$ jackets.

The store does not sell single clothing items — instead, it sells suits of two types:

>    a suit of the first type consists of one tie and one jacket;
>   a suit of the second type consists of one scarf, one vest and one jacket. 

Each suit of the first type costs $e$ coins, and each suit of the second type costs $f$ coins.

Calculate the **maximum** possible cost of a set of suits that can be composed from the delivered clothing items. Note that one item cannot be used in more than one suit (though some items may be left unused).

## Input
The first line contains one integer $a(1≤a≤100000)$ — the number of ties.

The second line contains one integer $b (1≤b≤100000)$ — the number of scarves.

The third line contains one integer $c(1≤c≤100000)$ — the number of vests.

The fourth line contains one integer $d(1≤d≤100000)$ — the number of jackets.

The fifth line contains one integer $e(1≤e≤1000)$ — the cost of one suit of the first type.

The sixth line contains one integer $f(1≤f≤1000)$ — the cost of one suit of the second type.
## Output
Print one integer — the maximum total cost of some set of suits that can be composed from the delivered items. 
# 题意
给定四种物品数量，有2种组合方式：
$a$和$d$组合，权值为$e$
$b$和$c$和$d$组合，权值为$f$
# 思路
我们会发现，两种组合重叠部分为$d$，因此我们比较$e$和$f$的大小，随后贪心分配即可。
# 代码
代码中个人习惯，将$d$写成了$b$
~~~cpp
#include <cstdio>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c; r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
inline int min(const int &a,const int &b){return a<b?a:b;}
inline int min(const int &a,const int &b,const int &c){return min(min(a,b),c);}
int a,b,c,d,e,f;
int main()
{
    read(a);
    read(c);
    read(d);
    read(b);
    read(e);
    read(f);
    int can = min(c,d);
    if(e >= f)
    {
        if(b <= a)
        {
            printf("%d",e * b);
            return 0;
        }
        else
        {
            int ans = e * a;
            b -= a;
            can = min(b,can);
            ans += can * f;
            printf("%d",ans);
            return 0;
        }
    }
    else
    {
        if(can >= b)
        {
            printf("%d",b * f);
            return 0;
        }
        else
        {
            int ans = can * f;
            b -= can;
            can = min(a,b);
            ans += can * e;
            printf("%d",ans);
            return 0;
        }
    }
    return 0;
}
~~~