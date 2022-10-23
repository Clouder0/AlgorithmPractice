#include <cstdio>
#include <algorithm>
#include <ctype.h>
#include <cstring>
const int bufSize = 1e6;
#define DEBUG
#define int long long
inline char nc()
{
    #ifdef DEBUG
    return getchar();
    #endif
    static char buf[bufSize], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
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
int T, x, y, c1, c2, c3, c4, c5, c6;
int d[10][10], dis[10][10], id[10][10], xx[10] = {0, 1, 0, -1, -1, 0, 1, 1, -1}, yy[10] = {0, 1, 1, 0, -1, -1, 0, -1, 1};
signed main()
{
    read(T);
    id[3][3] = 1, id[2][3] = 2, id[1][2] = 3, id[1][1] = 4, id[2][1] = 5, id[3][2] = 6,id[3][1] = 7,id[1][3] = 8;
    while (T--)
    {
        read(x), read(y), read(c1), read(c2), read(c3), read(c4), read(c5), read(c6);
        std::memset(dis, 0x3f, sizeof(dis));
        std::memset(d,0x3f,sizeof(d));
        d[3][3] = c1, d[2][3] = c2, d[1][2] = c3, d[1][1] = c4, d[2][1] = c5, d[3][2] = c6;
        //dis[0][0] = 0, dis[0][1] = c1, dis[0][2] = c2, dis[0][3] = c3, dis[0][4] = c4, dis[0][5] = c5, dis[0][6] = c6;
        for (int i = 0; i <= 8; ++i) dis[i][i] = 0;
        for (int i = 0; i <= 8; ++i)
        {
            for (int j = 1; j <= 3; ++j)
                for (int k = 1; k <= 3; ++k) 
                {
                    int nx = xx[i] + j, ny = yy[i] + k;
                    if(nx < 0 || ny < 0 || nx > 3 || ny > 3) continue;
                    dis[i][id[nx][ny]] = d[j][k];
                }
        }
        for (int k = 0; k <= 8; ++k)
            for (int i = 0; i <= 8; ++i)
                for (int j = 0; j <= 8; ++j) dis[i][j] = std::min(dis[i][j], dis[i][k] + dis[k][j]);
        long long res = 0;
        if(x < 0 && y < 0)
        {
            int t = std::min(-x, -y);
            res += t * dis[0][id[1][1]];
            x += t, y += t;
        }
        else if(x < 0 && y > 0)
        {
            int t = std::min(-x,y);
            res += t * dis[0][id[1][3]];
            x += t,y -= t;
        }
        else if(x > 0 && y < 0)
        {
            int t = std::min(x, -y);
            res += t * dis[0][id[3][1]];
            x -= t, y += t;
        }
        else if(x > 0 && y > 0)
        {
            int t = std::min(x,y);
            res += t * dis[0][id[3][3]];
            x -= t,y -= t;
        }
        if (x > 0) res += dis[0][id[3][2]] * x;
        else res += dis[0][id[1][2]] * -x;
        if (y > 0) res += dis[0][id[2][3]] * y;
        else res += dis[0][id[2][1]] * -y;
        printf("%lld\n",res);
    }
    return 0;
}