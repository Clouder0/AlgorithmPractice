#include <cstdio>
#include <list>
#include <cstring>
#include <algorithm>
#include <ctype.h>
using namespace std;
const int bufSize = 1e6;
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
const int maxn = 2e5 + 100;
char s[maxn],t[maxn];
list<char> now;
int len,num;
int main()
{
    read(s + 1),read(t + 1);
    len = strlen(s + 1),num = strlen(t + 1);
    for(int i = 1;i<=len;++i) now.push_back(s[i]);
    int mode = 0;//0 for normal mode,1 for insert mode
    list<char>::iterator cur = now.begin();
    for(int i = 1;i<=num;++i)
    {
        char opt = t[i];
        if(mode == 0)
        {
            if(opt == 'i') mode = 1;
            else if(opt == 'f') 
            {
                char tar = t[++i];
                list<char>::iterator it = cur;
                ++it;
                while(it != now.end() && it != now.end())
                {
                    if(*it == tar) 
                    {
                        cur = it;
                        break;
                    }
                    ++it;
                }
            }
            else if(opt == 'x') cur = now.erase(cur);
            else if(opt == 'h') 
            {
                if(cur == now.begin()) continue;
                --cur;
            }
            else if(opt == 'l')
            {
                if(cur == now.end()) continue;
                ++cur;
            }
        }
        else
        {
            if(opt == 'e') mode = 0;
            else now.insert(cur,opt);
        }
    }
    for(list<char>::iterator it = now.begin();it!=now.end();++it) putchar(*it);
    return 0;
}