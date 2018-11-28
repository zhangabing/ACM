/************************************************************************
    > File Name: RSA.h
    > Author: zhangab
    > Mail: 2411035458@qq.com
    > Created Time: 2018年11月28日 星期三 12时45分38秒
************************************************************************/
#ifndef RSA_H_INCLUDED
#define  RSA_H_INCLUDED
#include <bits/stdc++.h>
using namespace std;

class RSA {
  public :

    // 非递归扩展欧几里得
    long long exgcd(long long m, long long n, long long &x, long long &y) { 
        if (n == 0) {
            x = 1; y = 0;
            return m;
        }
        long long a, a1, b, b1, c, d, q, r, t;
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

    // 扩展欧几里得求逆元
    long long inv(long long a, long long mod) {
        long long x, y, d;
        d = exgcd(a, mod, x, y);
        if (d == 1)
            return (x % mod + mod) % mod;
        return -1;
    }

    // 用long long 计算乘法的时候,有可能溢出,该用加法替换
    long long mul_mod(long long a, long long b, long long mod) {
		long long c = 0;
		while (b) {
			if (b & 1) c = (c + a) % mod;
			a = (a + a) % mod;
			b >>= 1;
		}
		return c;
	}

    // 利用二进制的快速幂
    long long pow_mod(long long x, long long n, long long mod) {
		long long a = 1;
		while (n) {
			if (n & 1) a = mul_mod(x, a, mod);
			x = mul_mod(x, x, mod);
			n >>= 1;
		}
		return a;
    }

    // Miller_Rabin素数测试
    bool Miller_Rabin(long long n) {
        if (n == 2) return true;
        int s = 20, t = 0;
        long long x[65];
        long long u = n - 1;
        while (!(u & 1)) {
			t++;
			u >>= 1;
        }
        while (s--) {
			long long a = rand() % (n - 2) + 2;
			x[0] = pow_mod(a, u, n);
			for (int i = 1; i <= t; i++) {
				x[i] = mul_mod(x[i - 1], x[i - 1], n);
				if (x[i] == 1 && x[i - 1] != 1 && x[i - 1] != n - 1)
					return false;
			}
			if (x[t] != 1)	return false;
        }
        return true;
    }

    // 随机素数生成
    long long primeProduce() {
        srand(time(0));
        long long p = rand() * rand() * rand() * rand();
        p |= 1;
        if (p < 0) p = -p;
        while (!Miller_Rabin(p)) p += 2;
        return p;
    }

    // 初始化赋值p, q, n, phi
    void init() {
        p = primeProduce();
        q = primeProduce();
        while (p * q < 0) {
            if (p > q) swap(p, q);
            q = primeProduce();
        }
        n = p * q;
        phi = n / p * (p - 1) / q * (q - 1);
    }

    vector<long, long> encrypt(string text) {
        long long res;
        vector<long long> entext;
        for (auto i: text) {
            res = pow_mod(i, publicKey, n);
            entext.push_back(res);
        }
        return entext;
    }

    string decrypt(vector text) {
        long long res;
        string detext;
        for (auto i: text) {
            res = pow_mod(i, privateKey, n);
            detext += (char)res;
        }
        return detext;
    }

  private:
    long long n;
    long long p;
    long long q;
    long long phi;
    long long publicKey;
    long long privateKey;
};

#endif // RSA_H_INCLUDED
