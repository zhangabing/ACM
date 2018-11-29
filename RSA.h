/***********************************************************************
    > File Name: RSA.h
    > Author: zhangab
    > Mail: 2411035458@qq.com
    > Created Time: 2018��11��28�� ������ 12ʱ45��38��
************************************************************************/
#ifndef RSA_H_INCLUDED
#define  RSA_H_INCLUDED
#include <bits/stdc++.h>
using namespace std;
class RSA {
  public :
    // �ǵݹ���չŷ�����
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
    // ��չŷ���������Ԫ
    long long inv(long long a, long long mod) {
        long long x, y, d;
        d = exgcd(a, mod, x, y);
        if (d == 1)
            return (x % mod + mod) % mod;
        return -1;
    }
    // ��long long ����˷���ʱ��,�п������,���üӷ��滻
    long long mul_mod(long long a, long long b, long long mod) {
		long long c = 0;
		while (b) {
			if (b & 1) c = (c + a) % mod;
			a = (a + a) % mod;
			b >>= 1;
		}
		return c;
	}
    // ���ö����ƵĿ�����
    long long pow_mod(long long x, long long n, long long mod) {
		long long a = 1;
		while (n) {
			if (n & 1) a = mul_mod(x, a, mod);
			x = mul_mod(x, x, mod);
			n >>= 1;
		}
		return a;
    }
    // Miller_Rabin��������
    bool Miller_Rabin(long long n) {
        if (n < 0) n = -n;
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
    long long getPublicKey() {
        return publicKey;
    }
    long long getPrivateKey() {
        return privateKey;
    }
    // �����������
    long long primeProduce(long long mod = 2e18) {
        srand(rand());
        long long p = rand();
        p = p % mod | 1;
        while (!Miller_Rabin(p %= mod)) p += 2;
        return abs(p);
    }
    // ��ʼ����ֵp, q, n, phi, ���������publicKey, privateKey
    void init() {
        p = primeProduce();
        q = primeProduce();
        while (p * q < 0) {
            if (p > q) swap(p, q);
            q = primeProduce();
        }
        n = p * q;
        phi = n / p * (p - 1) / q * (q - 1);
        publicKey = primeProduce(phi);
        privateKey = inv(publicKey, phi);
        printf ("                     n = %lld\n\n", n);
        printf ("                     publicKey = %lld\n\n", publicKey);
        printf ("                     privateKey = %lld\n\n", privateKey);
    }

    // ����,��ÿ���ַ�ת����long long
    vector<long long> encrypt(string text, long long Key, long long n) {
        long long res;
        vector<long long> entext;
        for (auto i: text) {
            res = pow_mod(1ll * i, Key, n);
            entext.push_back(res);
        }
        puts ("               ��������:");
        for (auto i: entext)
			printf ("               %lld\n", i);
        return entext;
    }

    // ����,��һ��long long ������ת��Ϊ�ַ���
    string decrypt(vector<long long> text, long long Key, long long n) {
        long long res;
        string detext;
        for (auto i: text) {
            res = pow_mod(i, Key, n);
            detext += (char)res;
        }
        puts ("               ��������:");
        cout << "               " << detext << endl;
        return detext;
    }
	// ��Ԫ����
	void test() {
		puts("testing...\n");
		n = 2142595640794675597;
		publicKey = 667191463;
		privateKey = 408303107830327927;
		printf ("publicKey = %lld\n", publicKey);
		printf ("privateKey = %lld\n", privateKey);


		string s, t;
		puts ("\n�����ı�\n");
		cin >> s;
		vector<long long> mi;
		puts ("\n����\n");
		mi = encrypt(s, publicKey, n);
		for (auto i: mi)
			cout << i << endl;
		puts ("\n����\n");
		t = decrypt(mi, privateKey, n);
		cout << t << endl;
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
