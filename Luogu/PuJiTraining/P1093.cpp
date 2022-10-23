#include <cstdio>
#include <functional>
#include <algorithm>
using namespace std;
int n;
struct node
{
    int a,sum,id;
    bool operator>(const node &b) const 
    {
        if(this->sum != b.sum)
            return this->sum > b.sum;
        if(this->a != b.a)
            return this->a > b.a;
        return this->id < b.id;
    }
}all[301];
void read(int &r)
{
    static char c;
    r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar())
        ;
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar())
        ;
}
int main()
{
    read(n);
    int b,c;
    for(int i = 1;i<=n;++i)
    {
        read(all[i].a);
        read(b);
        read(c);
        all[i].sum = all[i].a + b + c;
        all[i].id = i;
    }
    sort(all+1,all+1+n,greater<node>());
    for(int i = 1;i<=5;++i)
        printf("%d %d\n",all[i].id,all[i].sum);
    return 0;
}