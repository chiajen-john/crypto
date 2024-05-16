#ifndef NT_MATH_H
#define NT_MATH_H

#include <cstdio>
#include "type.h"

INT64 ext_euclid(INT64 a, INT64 b, INT64 &x, INT64 &y)
{
    /* Extended Euclid algo. */
    if (b == 0) {
        x = 1; y = 0;
        return a;
    }
    INT64 ans = ext_euclid(b, a % b, x, y);
    INT64 temp = y;
    y = (x) - (a/b) * temp;
    x = temp;
    return ans;
}

INT64 lcm(INT64 a, INT64 b)
{
    INT64 x, y;
    return (a * b) / ext_euclid(a, b, x, y);
}

INT64 mod_exp(INT64 x, INT64 y, INT64 m)
{
    /* Compute (x ^ y) mod N.
    x: Base.
    y: Exponent.
    res: Result.
    */
    INT64 res = 1;
    x %= m;
    while (y > 0) {
        if (y & 1) {
            res = (res * x) % m;
        }
        x = (x * x) % m;
        y >>= 1;
    }
    return res;
}

INT64 mod_inv(INT64 a, INT64 m)
{
    /* Compute inverse of a mod b.
    x: Number holders. Do not initialize.
    y: Number holders. Do not initialize.
    */
    INT64 x, y;
    if (ext_euclid(a, m, x, y) == 1) {
        if (x < 0) {
            x += m;
        }
    } else {
        std::perror("Invalid e provided.");
    }
    return x;
}

BOOL isPrime(PRIME x)
{
    /* Sieve of Eratosthenes. */
    if (not (x & 1) && x > 2) return false; 

    int composites[x + 1] = {};
    composites[0] = 1;
    composites[1] = 1;
    for (int i = 1; i * i <= x; i += 2) {
        if (not composites[i]) {
            for (int j = i * i; j <= x; j += i) {
                composites[j] = 1;
            }
        }
    }
    return not (composites[x]);
}

BOOL isCoprime(INT64 x, INT64 y)
{
    return true;
}

#endif  // NT_MATH_H
