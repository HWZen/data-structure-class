#include "pch.h"
#include <cmath>
#include <algorithm>
using namespace std;
using namespace rapidjson;

//O(Is_prime)=O(sqrt(N))
bool Is_prime(LL num);
bool Is_prime_plus(LL num);

const LL num1 = 0b11110100001000101111;
const LL num2 = 0b1101101001110001101001111;

int main()
{
    clock_t start, end;
#if 0
    start = clock();
    LL temp = 1;
    LL anser = 1;
    while (((clock() - start) / CLOCKS_PER_SEC) < 20)
    {
        if (Is_prime_plus(temp))
            anser = temp;
        temp++;
    }
    cout << "prime_max: " << anser << endl;
#endif

    start = clock();
    cout << "num1: " << Is_prime(num1) << endl;
    end = clock();
    cout << "num1 time: " << (double)(end - start) / CLOCKS_PER_SEC << endl;

    start = clock();
    cout << "num2: " << Is_prime(num2) << endl;
    end = clock();
    cout << "num2 time: " << (double)(end - start) / CLOCKS_PER_SEC << endl;

    return 0;
}

bool Is_prime(LL num)
{
    LL temp = sqrt(num);
    for (LL i = 2; i <= temp; i++)
    {
        if (num % i == 0)
            return false;
    }
    return true;
}

bool Is_prime_plus(LL num)
{
    if (num == 2 || num == 3)
        return true;
    if (num % 6 != 1 && num % 6 != 5)
        return false;
    LL temp = sqrt(num);
    for (LL i = 5; i <= temp; i += 6)
        if (num % i == 0 || num % (i + 2) == 0)
            return false;

    return true;
}