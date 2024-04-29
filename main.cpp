#include <iostream>
#include <numeric>
#include "rsa.h"
#include "type.h"

int main(int argc, char ** argv) {

    // Configure RSA.
    PRIME p = 61;
    PRIME q = 53;
    INT64 e = 17;

    struct rsa codec = rsa(p, q, e);

    // Example 1
    char plaintext1[MAX_MESSAGE_LEN] = "Goodbye blue Monday.";
    STRING cipher = codec.encrypt(plaintext1);
    STRING decoded = codec.decrypt(cipher);

    printf("\nPlaintext:%s\nCiphertext:%s\nDecoded:%s\n", 
            plaintext1, 
            cipher, 
            decoded);

    // Example 2
    INT64 plaintext2[7] = {2, 3, 5, 7, 11, 13, 123};
    cipher = codec.encrypt(plaintext2);
    decoded = codec.decrypt(cipher);

    printf("\nPlaintext:%s\nCiphertext:%s\nDecoded:%s\n", 
            num2string(plaintext2, 7), 
            cipher, 
            num2string((INT64 *) decoded, 7));

    fflush(stdout);
    
    return 0;
}
