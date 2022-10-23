#include <cstdio>
#include <algorithm>
#include <ctype.h>
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
const int maxn = 1e5 + 100;
const int maxm = 1e7 + 100;
int n, m, u, v, q, t, a[maxn];
int q1[maxn], q2[maxm*2], q3[maxm*2], qh1, qt1, qh2, qt2, qh3, qt3;
int Q[maxm*3], qt, qh;
inline int cut(int x, int k)
{
    int w = x + q * (k - 1);
    int l = 1ll * w * u / v, r = w - l;
    q2[++qt2] = l - q * k, q3[++qt3] = r - q * k;
    return w;
}
int main()
{
    read(n), read(m), read(q), read(u), read(v), read(t);
	for (int i = 1; i <= n; ++i) read(a[i]);
	std::sort(a + 1,a + 1 + n);
    qh1 = qh2 = qh3 = 1;
    for (int i = n; i; --i) q1[++qt1] = a[i];
	for (int i = 1; i <= m; ++i) 
	{
        int maxx = -(1 << 30), res = 0;
        if (qt1 >= qh1) maxx = std::max(maxx, q1[qh1]);
        if (qt2 >= qh2) maxx = std::max(maxx, q2[qh2]);
        if (qt3 >= qh3) maxx = std::max(maxx, q3[qh3]);
        if (qt1 >= qh1 && maxx == q1[qh1]) res = cut(q1[qh1++], i);
        else if (qt2 >= qh2 && maxx == q2[qh2]) res = cut(q2[qh2++], i);
        else if (qt3 >= qh3 && maxx == q3[qh3]) res = cut(q3[qh3++], i);
        if (i % t == 0) printf("%d ", res);
    }
	puts("");
	while(qt1 >= qh1 || qt2 >= qh2 || qt3 >= qh3)
	{
       int maxx = -(1 << 30);
       if (qt1 >= qh1) maxx = std::max(maxx, q1[qh1]);
       if (qt2 >= qh2) maxx = std::max(maxx, q2[qh2]);
       if (qt3 >= qh3) maxx = std::max(maxx, q3[qh3]);
       if (qt1 >= qh1 && maxx == q1[qh1]) Q[++qt] = q1[qh1++];
       else if (qt2 >= qh2 && maxx == q2[qh2]) Q[++qt] = q2[qh2++];
       else if (qt3 >= qh3 && maxx == q3[qh3]) Q[++qt] = q3[qh3++];
    }
    for (int i = t; i <= qt; i += t) printf("%d ", Q[i] + m * q);
    return 0;
}