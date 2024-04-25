#ifndef RSA_H
#define RSA_H

#include <cassert>
#include "type.h"
#include "nt_math.h"

#define MAX_MESSAGE_LEN 1 << 15


struct rsa {
    PRIME p;
    PRIME q;
    KeyVal e;
    KeyVal N;
    KeyVal d;
    INT64 lmda;

    rsa(PRIME p, PRIME q, KeyVal e) {

        assert(isPrime(p) && isPrime(q));
        assert(isCoprime(e, (p - 1) * (q - 1)));

        this->p = p;
        this->q = q;
        this->e = e;
        this->N = p * q;
        this->lmda = lcm(p-1, q-1);
        this->d = this->keygen();
    }

    INT64 encrypt(INT64 x) {
        assert(x < this->N);
        return mod_exp(x, this->e, this->N);
    }

    INT64 decrypt(INT64 x) {
        return mod_exp(x, this->d, this->N);
    }

    KeyVal keygen() {
        /* Generate private key. */
        return mod_inv(this->e, this->lmda);
    }

    void* string_encrypt(char* message) {
        void* cipher = new INT64[MAX_MESSAGE_LEN];
        int i = 0;
        INT64 code;
        while (message[i] != DELIM) {
            code = this->encrypt(message[i]);
            ((INT64*) cipher)[i++] = code;
        }
        ((INT64*) cipher)[i] = DELIM;
        return cipher;
    }

    char* string_decrypt(void* ciphar) {
        char* decrypted = new char[MAX_MESSAGE_LEN];
        int i = 0;
        INT64 code;
        while (((INT64*) ciphar)[i] != DELIM) {
            code = this->decrypt(((INT64*) ciphar)[i]);
            decrypted[i++] = code;
        }
        decrypted[i] = DELIM;
        return decrypted;
    }
};

#endif  // RSA_H
