#include <cstdio>
#include <vector>
using namespace std;
template<typename T>
inline T _min(const T &a,const T &b){return a<b?a:b;}
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
int n;
vector<int> b;
int solve(vector<int> a,int pos)
{
    if(a.size() == 0 || pos < 0)
        return 0;
    vector<int> a0,a1;
    for(vector<int>::iterator it = a.begin();it!=a.end();++it)
    {
        if(*it&(1<<pos))
            a1.push_back(*it);
        else
            a0.push_back(*it);
    }
    if(a1.size() == 0)
        return solve(a0,pos-1);
    else if(a0.size() == 0)
        return solve(a1,pos-1);
    else
        return min(solve(a0,pos-1),solve(a1,pos-1)) + (1<<pos);
}
int main()
{
    read(n);
    int t;
    for(int i = 1;i<=n;++i)
        read(t),b.push_back(t);
    printf("%d",solve(b,30));
    return 0;
}