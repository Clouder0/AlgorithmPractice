#include <cstdio>
#include <queue>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
int n;
int p[200010],a[200010];
struct node
{
    int val;
    int cost;
    node(){}
    node(const int &_val,const int &_cost) : val(_val),cost(_cost){}
    bool operator<(const node &b) const
    {
        return this->val < b.val;
    }
    bool operator>(const node &b) const
    {
        return this->val > b.val;
    }
};
priority_queue<node> prefix;
priority_queue<node,vector<node>,greater<node> > surfix;
int main()
{
    read(n);
    for(int i = 1;i<=n;++i)
        read(p[i]);
    for(int i = 1;i<=n;++i)
        read(a[i]);
    long long mincost = 0;
    
    return 0;
}