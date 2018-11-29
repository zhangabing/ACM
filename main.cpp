#include <bits/stdc++.h>
#include "RSA.h"
using namespace std;

int main()
{
    RSA a;
    a.init();
    puts("\n\n\n\n\n输入文本");
    string Min;
    cin >> Min;
    vector<long long> Mi;
    Mi = a.encrypt(Min, a.getPublicKey());
    puts("\n密文如下:");
    for (auto i: Mi)
        cout << i << endl;

    puts ("输入秘钥: ");
    long long b;
    cin >> b;
    puts ("解得明文:");
    cout << a.decrypt(Mi, b) << endl;

    puts ("标准明文:");
    cout << a.decrypt(Mi, a.getPrivateKey());
    cout << Min << endl;
    return 0;
}
