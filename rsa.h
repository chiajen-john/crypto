#ifndef RSA_H
#define RSA_H

#include <cassert>
#include <string>
#include "type.h"
#include "nt_math.h"

#define MAX_MESSAGE_LEN 1 << 15


struct rsa 
{
    PRIME p;
    PRIME q;
    KeyVal e;
    KeyVal N;
    KeyVal d;
    INT64 lmda;

    rsa(PRIME p, PRIME q, KeyVal e) 
    {

        assert(isPrime(p) && isPrime(q));
        assert(isCoprime(e, (p - 1) * (q - 1)));

        this->p = p;
        this->q = q;
        this->e = e;
        this->N = p * q;
        this->lmda = lcm(p-1, q-1);
        this->d = this->keygen();
    }

    INT64 _encrypt(INT64 x) 
    {
        assert(x < this->N);
        return mod_exp(x, this->e, this->N);
    }

    INT64 _decrypt(INT64 x) 
    {
        return mod_exp(x, this->d, this->N);
    }

    KeyVal keygen() 
    {
        /* Generate private key. */
        return mod_inv(this->e, this->lmda);
    }

    STRING encrypt(void* message) 
    {
        INT64* cipher = new INT64[MAX_MESSAGE_LEN];
        int i = 0;
        INT64 code;
        while (((STRING) message)[i] != DELIM) {
            code = this->_encrypt(((STRING) message)[i]);
            cipher[i++] = code;
        }
        cipher[i] = DELIM;
        return (STRING) cipher;
    }

    STRING decrypt(void* cipher) 
    {
        STRING decrypted = new char[MAX_MESSAGE_LEN];
        int i = 0;
        INT64 code;
        while (((INT64*) cipher)[i] != DELIM) {
            code = this->_decrypt(((INT64*) cipher)[i]);
            decrypted[i++] = code;
        }
        decrypted[i] = DELIM;
        return decrypted;
    }
};

STRING num2string(INT64* num, int len)
{
    STRING res = new char[MAX_MESSAGE_LEN];
    int j = 0;
    for (int i = 0; i < len; i++) {
        std::string str = std::to_string(num[i]);
        for (char& c : str) {
            *(res + (j++)) = c;
        }
    }
    return res;
}

#endif  // RSA_H
