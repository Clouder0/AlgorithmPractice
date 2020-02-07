#include <cstdio>
#include <map>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 2e5 + 10;
int T,n;
char s[maxn];
int xsum[maxn],ysum[maxn];
map<pair<int,int>,int> pos;
int main()
{
    read(T);
    while(T--)
    {
        pos.clear();
        read(n);
        scanf("%s",s+1);
        int al = 0,ar = 9999999,found = 0;
        pos[make_pair(0,0)] = 0;
        for(int i = 1;i<=n;++i)
        {
            xsum[i] = xsum[i-1];
            ysum[i] = ysum[i-1];
            if(s[i] == 'L')
                --xsum[i];
            else if(s[i] == 'R')
                ++xsum[i];
            else if(s[i] == 'U')
                ++ysum[i];
            else
                --ysum[i];
            map<pair<int,int>,int>::iterator it = pos.find(make_pair(xsum[i],ysum[i]));
            if(it != pos.end())
            {
                int l = it->second+1,r = i;
                if(r - l > ar - al)
                    goto end;
                al = l,ar = r;
                found = 1;
                goto end;
            }
            end:
            pos[make_pair(xsum[i],ysum[i])] = i;
        }
        if(found)
            printf("%d %d\n",al,ar);
        else
            puts("-1");
    }
    return 0;
}