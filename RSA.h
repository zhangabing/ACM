/************************************************************************
    > File Name: RSA.h
    > Author: zhangab
    > Mail: 2411035458@qq.com 
    > Created Time: 2018年11月28日 星期三 12时45分38秒
************************************************************************/
#ifndef RSA_H_INCLUDED
#define RSA_H_INCLUDED

#include <bits/stdc++.h>

class RSA {
  public :
    srand(time(0));
    long long n;
    long long phi;
    long long key;
    long long text;

    long  long exgcd(long  long m, long  long n, long  long &x, long  long &y) { // 扩展欧几里得
        if (n == 0) {
            x = 1; y = 0;
            return m;
        }
        long  long a, a1, b, b1, c, d, q, r, t;
        a1 = b = 1;
        a = b1 = 0;
        c = m; d = n;

        q = c/d; r = c%d;
        while (r) {
            c = d;
            d = r;
            t = a1;
            a1 = a;
            a = t - q * a;
            t = b1;
            b1 = b;
            b = t - q * b;

            q = c/d;
            r = c%d;
        }
        x = a; y = b;
        return d;
    }

    long long ksm(long long x, long long n, long long mod) { // 快速幂
        long long a = 1;
        while (n) {
            if (n & 1) a = a * x % mod;
            x = x * x % mod;
            n >>= 1;
        }
        return a;
    }

    long long inv(long long a, long long mod) { // 逆元
        long long x, y, d;
        d = exgcd(a, mod, x, y);
        if (d == 1)
            return (x % mod + mod) % mod;
        return -1;
    }

    bool sqrtJudge(long long p) {
        ;
    }

    bool fematJudge(long  long p) {
        ;
    }

    bool millerJudge(long long p) {
        ;
    }

    long long primeProduce() {
        while (1) {
            long long p;
            for (int i = 0; i < 10; i++) {
                p <<= 7;
                p += rand();
            }
            if (p < 0) p = 0 - p;
            if (!sqrtJudge(p)) continue;
            if (!fematJudge(p)) continue;
            if (millerJudge(p)) return p;
        }
    }
};

#endif // RSA_H_INCLUDED
