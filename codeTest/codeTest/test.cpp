#include<iostream>
#include<algorithm>
#include<cstring>
#include<string>
#pragma GCC optimize(2)
using namespace std;
typedef unsigned long long ULL;
const int N = 2e6 + 10, base = 131;
ULL hr[N], hl[N], p[N];
char str[N];
ULL get(ULL h[], int l, int r)
{
    return h[r] - h[l - 1] * p[r + 1 - l];
}
int main()
{
    int T = 1;
    while (cin >> str + 1, strcmp(str + 1, "END"))
    {
        int n = strlen(str + 1), res = 0;
        for (int i = 2 * n; i >= 0; i -= 2)
        {
            str[i] = str[i / 2];
            str[i - 1] = 'z' + 1;
        }
        n *= 2; p[0] = 1;
        for (int i = 1, j = n; i <= n; i++, j--)
        {
            p[i] = p[i - 1] * base;
            hl[i] = hl[i - 1] * base + str[i];
            hr[i] = hr[i - 1] * base + str[j];
        }

        for (int i = 1; i <= n; i++)
        {
            int l = 0, r = min(n - i, i - 1);
            while (l < r)
            {
                int mid = l + r + 1 >> 1;
                if (get(hl, i - mid, i - 1) == get(hr, n + 1 - (i + mid), n + 1 - (i + 1)))l = mid;
                else r = mid - 1;
            }
            if (str[i - l] <= 'z')res = max(res, l + 1);
            else res = max(res, l);
        }
        printf("Case %d: %d\n", T++, res);
    }
    return 0;
}