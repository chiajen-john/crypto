#include <iostream>

#include "rsa.h"
#include "type.h"

int main(int argc, char ** argv) {
    
    PRIME p = 5;
    PRIME q = 11;
    INT64 e = 3;

    struct rsa codec = rsa(p, q, e);
    
    INT64 message = 13;
    INT64 cipher = codec.encrypt(message);
    INT64 new_message = codec.decrypt(cipher);

    // printf("p: %lld q: %lld e: %lld d: %lld N: %lld\n", codec.p, codec.q, codec.e, codec.d, codec.N);
    printf("oringinal message: %lld\nciphar: %lld\nnew message: %lld\n", message, cipher, new_message);

    fflush(stdout);
    
    return 0;
}
