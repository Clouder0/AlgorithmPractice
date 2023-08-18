#include <cstdio>
const double EPS = 1e-6;
double _abs(const double& x) { return x > 0 ? x : -x; }

double a, b, c, d;
double calc(double x)
{
    return a * x * x * x + b * x * x + c * x + d;
}
int main()
{
    scanf("%lf%lf%lf%lf", &a, &b, &c, &d);
    // printf("%.2f %.2f %.2f %.2f\n", a, b, c, d);
    for (double l = -100, r = -99; r <= 100; l += 1, r += 1)
    {
        double lv = calc(l), rv = calc(r);
        if (lv * rv <= EPS)
        {
            // printf("%.2f %.2f\n",l,r);
            if (_abs(lv) <= EPS)
                printf("%.2f ", l);
            else if (_abs(rv) <= EPS)
                continue;
            else
            {
                double ll = l, rr = r, mid = (l + r) / 2, ans = -2;
                while (rr - ll >= 1e-8)
                {
                    mid = (ll + rr) / 2;
                    if (_abs(calc(mid)) <= EPS)
                    {
                        ans = mid;
                        break;
                    }
                    else if (calc(mid) * calc(l) <= EPS)
                        rr = mid;
                    else
                        ll = mid;
                }
                printf("%.2f ", ans);
            }
        }
    }
    return 0;
}