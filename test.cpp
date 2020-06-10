#include <cstdio>
#include <cstring>
#include <algorithm>
#define RG register
#define R RG int
using namespace std;
const int N = 1e5 + 9, SZ = 2.2e6;
char buf[SZ], *pp = buf - 1; //fread必备
int k, a[N], b[N], c[N], p[N], q[N], v[N], cnt[N], ans[N], *e;
inline int in()
{
	while (*++pp < '-')
		;
	R x = *pp & 15;
	while (*++pp > '-')
		x = x * 10 + (*pp & 15);
	return x;
}
void out(R x)
{
	if (x > 9)
		out(x / 10);
	*++pp = x % 10 | '0';
}
inline bool cmp(R x, R y)
{ //直接对数组排序，注意三关键字
	return a[x] < a[y] || (a[x] == a[y] && (b[x] < b[y] || (b[x] == b[y] && c[x] < c[y])));
}
inline void upd(R i, R v)
{ //树状数组修改
	for (; i <= k; i += i & -i)
		e[i] += v;
}
inline int ask(R i)
{ //树状数组查前缀和
	R v = 0;
	for (; i; i -= i & -i)
		v += e[i];
	return v;
}
void cdq(R *p, R n)
{ //处理一个长度为n的子问题
	if (n == 1)
		return;
	R m = n >> 1, i, j, k;
	cdq(p, m);
	cdq(p + m, n - m);	  //递归处理
	memcpy(q, p, n << 2); //归并排序
	for (k = i = 0, j = m; i < m && j < n; ++k)
	{
		R x = q[i], y = q[j];
		if (b[x] <= b[y])
			upd(c[p[k] = x], v[x]), ++i; //左边小，插入
		else
			cnt[y] += ask(c[p[k] = y]), ++j; //右边小，算贡献
	}
	for (; j < n; ++j)
		cnt[q[j]] += ask(c[q[j]]); //注意此时可能没有完成统计
	memcpy(p + k, q + i, (m - i) << 2);
	for (--i; ~i; --i)
		upd(c[q[i]], -v[q[i]]); //必须这样还原树状数组，memset是O(n^2)的
}
int main()
{
	fread(buf, 1, SZ, stdin);
	R n = in(), i, j;
	k = in();
	e = new int[k + 9];
	for (i = 0; i < n; ++i)
		p[i] = i, a[i] = in(), b[i] = in(), c[i] = in();
	sort(p, p + n, cmp);
	for (i = 1, j = 0; i < n; ++i)
	{
		R x = p[i], y = p[j];
		++v[y]; //模仿unique双指针去重，统计v
		if (a[x] ^ a[y] || b[x] ^ b[y] || c[x] ^ c[y])
			p[++j] = x;
	}
	++v[p[j++]];
	cdq(p, j);
	for (i = 0; i < j; ++i)
		ans[cnt[p[i]] + v[p[i]] - 1] += v[p[i]]; //答案算好
	for (pp = buf - 1, i = 0; i < n; ++i)
		out(ans[i]), *++pp = '\n';
	fwrite(buf, 1, pp - buf + 1, stdout);
}
