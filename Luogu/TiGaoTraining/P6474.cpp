#include <cstdio>
#include <algorithm>
#include <queue>
#include <ctype.h>
using namespace std;
#define DEBUG
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
	for (; c != '.' && c !='S' && c !='T' && !isdigit(c); c = nc());
	for (; c == '.' || c =='S' || c =='T' || isdigit(c); c = nc()) *s++ = c;
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
const int maxn = 400, maxc = 16;
int n, m, c1, c2, d;
int dx[8] = {0, 0, 1, 1, 1, -1, -1, -1};
int dy[8] = {1, -1, -1, 0, 1, -1, 0, 1};
int ddx[4] = {0, 0, -1, 1};
int ddy[4] = {-1, 1, 0, 0};
int mp[maxn][maxn], tmp[maxn][maxn];
char s[10];
inline int myabs(int x){return x > 0 ? x : -x;}
inline int dis(int x1, int y1, int x2, int y2) { return myabs(x1 - x2) + myabs(y1 - y2); }
struct node
{
    int x, y, step, va, tp;
	bool operator<(const node &b)const
	{
		if(step != b.step) return step < b.step;
		if(va + tp != b.va + b.tp) return va + tp < b.va + b.tp;
		return va < b.va;
	}
};
inline bool check(int x, int y) { return x > 0 && x <= n && y > 0 && y <= m && mp[x][y] != 2; }
queue<node> q;
bool vis[maxn][maxn][maxc][maxc];
int main()
{
	read(n),read(m),read(c1),read(c2),read(d);
    int sx, sy, tx, ty;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
        {
			read(s + 1);
            if (s[1] == '.') continue;
            else if (s[1] == 'S') sx = i, sy = j;
            else if (s[1] == 'T') tx = i, ty = j;
            else 
			{
                int can = 0;
                for (int p = 1; isdigit(s[p]); ++p) can = can * 10 + s[p] - '0';
				--can;
                mp[i][j] = 2;
                for (int p = i - can; p <= n && p <= i + can; ++p)
                {
                    int left = can - myabs(i - p);
                    if(left < 0) continue;
                    tmp[p][std::max(1, j - left)]++, tmp[p][std::min(m + 1, j + left + 1)]--;
                }
            }
        }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) 
		{
            tmp[i][j] += tmp[i][j - 1];
            if (tmp[i][j] > 0) mp[i][j] = std::max(mp[i][j], 1);
        }
//    for(int i = 1;i<=n;puts(""),++i) for(int j = 1;j<=m;++j) printf("%d ",mp[i][j]);
    q.push((node){sx, sy, 0, 0, 0});
    node ans = (node){0, 0, 1 << 30, 0, 0};
    while (q.size())
    {
		node now = q.front();
		q.pop();
		if(now.va > c1) continue;
		if(now.tp > c2) continue;
        if (now.step + dis(now.x, now.y, tx, ty) > ans.step) goto end;
        for (int i = now.va; i >= 0; --i) for (int j = now.tp; j >= 0; --j) if (vis[now.x][now.y][i][j]) {vis[now.x][now.y][i][j] = 1; goto end;}
        vis[now.x][now.y][now.va][now.tp] = 1;
        if (now.x == tx && now.y == ty)
        {
            ans = std::min(ans, now);
            goto end;
        }
        for (int i = 0; i < 8; ++i)
        {
            int nx = now.x + dx[i], ny = now.y + dy[i];
            if (!check(nx, ny)) continue;
            if (mp[nx][ny] == 0) q.push((node){nx, ny, now.step + 1, now.va, now.tp});
            else if (mp[nx][ny] == 1) q.push((node){nx, ny, now.step + 1, now.va + 1, now.tp});
        }
        for (int i = 0; i < 4; ++i)
        {
            int nx = now.x + ddx[i] * d, ny = now.y + ddy[i] * d;
            if (!check(nx, ny)) continue;
            if (mp[nx][ny] == 0) q.push((node){nx, ny, now.step + 1, now.va, now.tp + 1});
            else if (mp[nx][ny] == 1) q.push((node){nx, ny, now.step + 1, now.va + 1, now.tp + 1});
        }
        end:;
    }
    if (ans.step >= (1 << 30)) puts("-1");
    else printf("%d %d %d\n", ans.step, ans.va, ans.tp);
    return 0;
}