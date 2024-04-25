#include <iostream>

#include "rsa.h"
#include "type.h"

int main(int argc, char ** argv) {
    
    PRIME p = 61;
    PRIME q = 53;
    INT64 e = 17;

    struct rsa codec = rsa(p, q, e);
    
    char message[MAX_MESSAGE_LEN] = "Goodbye blue Monday.";
    void* cipher = codec.string_encrypt(message);
    char* new_message = codec.string_decrypt(cipher);

    // printf("p: %lld q: %lld e: %lld d: %lld N: %lld\n", codec.p, codec.q, codec.e, codec.d, codec.N);
    printf("\nPlaintext: %s\n\nCiphertext: %s\n\nDecoded: %s\n", message, (char *) cipher, new_message);

    fflush(stdout);
    
    return 0;
}
