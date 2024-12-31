//
// Created by Adi on 2024/6/12.
//

#ifndef ANDROIDNATIVE_MY_AES_H
#define ANDROIDNATIVE_MY_AES_H

char *aes256gcm_encrypt(const void *key, const unsigned char *plaintext);
char *aes256gcm_decrypt(const void *key, const unsigned char *in);

char *aes128ecb_encrypt(char *key, char *plaintext);
char *aes128ecb_decrypt(char *key, char *inEncode);

char *aes256cbc_encrypt(char *key, char *iv, char *plaintext);
char *aes256cbc_decrypt(char *key, char *iv, char *inEncode);
#endif //ANDROIDNATIVE_MY_AES_H
