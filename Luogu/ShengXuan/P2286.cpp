#include <cstdio>
#include <set>
using namespace std;
const int mod = 1000000;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
set<int> s;
int n,ans;
bool flag;// 0 pet 1 person
void find(int x)
{
    set<int>::iterator right = s.lower_bound(x);
    set<int>::iterator left = right;
    --left;
    if(*left != 1<<31 && x - *left <= *right - x)
    {
        ans = (ans + x - *left) % mod;
        s.erase(left);
    }
    else
    {
        ans = (ans + *right - x) % mod;
        s.erase(right);
    }
}
int main()
{
    s.insert(1<<30);
    s.insert(1<<31);
    read(n);
    int opt, x;
    while (n--)
    {
        read(opt);
        read(x);
        if (s.size() == 2)
            flag = opt;
        if (flag == opt)
            s.insert(x);
        else
            find(x);
    }
    printf("%d", ans);
    return 0;
}