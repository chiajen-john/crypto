#ifndef RSA_H
#define RSA_H

#include <cassert>

#include "type.h"
#include "nt_math.h"

struct rsa {
    PRIME p;
    PRIME q;
    KeyVal e;
    KeyVal N;
    KeyVal d;

    rsa(PRIME p, PRIME q, KeyVal e) {
        assert(isPrime(p) && isPrime(q));
        assert(isCoprime(e, (p - 1) * (q - 1)));
        
        this->p = p;
        this->q = q;
        this->e = e;
        this->N = p * q;
        this->d = this->keygen();
    }

    INT64 encrypt(INT64 x) {
        return mod_exp(x, this->e, this->N);
    }

    INT64 decrypt(INT64 x) {
        return mod_exp(x, this->d, this->N);
    }

    KeyVal keygen() {
        /* Generate private key. */
        return mod_inv(this->e, (this->p-1) * (this->q-1));
    }
};

#endif  // RSA_H
