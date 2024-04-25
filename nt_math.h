#ifndef NT_MATH_H
#define NT_MATH_H

#include <cstdio>

#include "type.h"

INT64 ext_euclid(INT64 a, INT64 b, INT64 &x, INT64 &y) {
    /* Extended Euclid algo */
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

INT64 mod_exp(INT64 x, INT64 y, INT64 m) {
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

INT64 mod_inv(INT64 a, INT64 m) {
    /* Compute inverse of a mod b
    x, y: Number holders. Do not initialize.
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

#endif  // NT_MATH_H
