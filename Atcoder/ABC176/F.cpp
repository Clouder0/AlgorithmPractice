#include <cstdio>
#include <vector>
#include <algorithm>
#include <ctype.h>
const int bufSize = 1e6;
using namespace std;
#define DEBUG
inline char nc()
{
    #ifdef DEBUG
    return getchar();
    #endif
    static char buf[bufSize], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
}
inline void read(char *s)
{
    static char c;
    for (; !isalpha(c); c = nc());
    for (; isalpha(c); c = nc()) *s++ = c;
    *s = '\0';
}
template<typename T>
inline T read(T &r)
{
    static char c;
    static int flag;
    flag = 1, r = 0;
    for (c = nc(); !isdigit(c); c = nc()) if (c == '-') flag = -1;
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r *= flag;
}
const int maxn = 2e3 + 100;
int n;
bool vis[maxn];
vector<int> a,b;
int cnt[maxn];
bool cmp(int a,int b)
{
    if(vis[a] != vis[b]) return vis[a] > vis[b];
    return a < b;
}
int main()
{
    read(n);
    for (int i = 1; i <= 3 * n; ++i)  
    {
        int x;
        read(x),a.push_back(x);
    }
    int score = 0;
    while(a.size() > 3)
    {
        b.clear();
        for(int i = 0;i<5;++i) b.push_back(a[i]);
        /*
        printf("b: ");
        for(vector<int>::iterator it = b.begin();it!=b.end();++it) printf("%d ",*it);
        puts("");
        */
        for(vector<int>::iterator it = b.begin();it!=b.end();++it) cnt[*it]++;
        for(vector<int>::iterator it = b.begin();it!=b.end();++it) 
        {
            if(cnt[*it] == 3)
            {
                ++score;
                for (vector<int>::iterator it2 = a.begin(); cnt[*it] && it2 != a.end(); ) 
                {
                    if(*it == *it2) it2 = a.erase(it2);
                    else ++it2;
                }
                goto end;
            }
        }
        sort(a.begin(),a.begin() + 5,cmp);
        for (int i = 0; i < 3; ++i) vis[a[i]] = 1;
        for (int i = 0; i < 3; ++i) a.erase(a.begin());
        end:;
        for(vector<int>::iterator it = b.begin();it!=b.end();++it) cnt[*it] = 0;
        /*
        printf("a: ");
        for(vector<int>::iterator it = a.begin();it!=a.end();++it) printf("%d ",*it);
        puts("");
        */
    }
    
    for(int i = 1;i<3;++i) if(a[i] != a[i-1]) goto fail;
    ++score;
    fail:
    printf("%d\n",score);
    return 0;
}